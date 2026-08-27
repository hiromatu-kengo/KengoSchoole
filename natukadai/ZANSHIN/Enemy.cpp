#include "Enemy.h"
#include "DxLib.h"
#include "Game.h"
#include <cmath>

namespace
{
	constexpr int kWidth = 128;	                                            //1コマの幅
	constexpr int kHeight = 128;                         	                //1コマの高さ
	constexpr int kScale = 3;

	//アニメーションの関連の定義
	constexpr int kIdleAnimNum = 6;	                                    //待機アニメーションのコマ数
	constexpr int kRunAnimNum = 8;	                                        //走るアニメーションのコマ数
	constexpr int kAttackAnimNum = 24;	                                    //攻撃アニメーションのコマ数
	constexpr int kSingleAnimFrame = 4;	                                    //アニメ1コマに書けるフレーム数

	//アニメーション1ループにかかるフレーム数
	constexpr int kIdleAnimTotalFrame = kIdleAnimNum * kSingleAnimFrame;    //待機アニメーションの1ループにかかるフレーム数
	constexpr int kRunAnimTotalFrame = kRunAnimNum * kSingleAnimFrame;      //走るアニメーションの1ループにかかるフレーム数
	constexpr int kAttackAnimTotalFrame = kAttackAnimNum * kSingleAnimFrame; //攻撃アニメーションの1ループにかかるフレーム数

	constexpr int kMoveSpeed = 4;                                          // 移動速度
	constexpr int kMaxFrames = 10;                                          // 最大フレーム数
	constexpr int kGravity = 2;                                             // 重力加速度
	constexpr int kJumpPower = 40;                                          // ジャンプ初速
	constexpr int kGroundY = Game::kScreenHeight / 2 + kHeight;				// 地面のY座標（仮定）
	constexpr float kStartX = 1000;                                         // 敵の初期X座標
	constexpr float kStartY = Game::kScreenHeight / 2 + kHeight;			// 敵の初期Y座標
	constexpr int kParryMaxFrame = 10;                                      // パリィ状態の最大フレーム数

	//AI設定値
	constexpr float kAttackRange = 150.0f;									//攻撃に移る距離
	constexpr int kAttackWaitTime = 60;										//攻撃後の隙
	constexpr int kMaxPostureValue = 100;									//最大体幹値


}

Enemy::Enemy() :
	m_animFrame(0),
	m_isFlip(true),
	m_graphCount(0),
	m_frameIndex(0),
	m_idleGraph(-1),
	m_runGraph(-1),
	m_attackGraph(-1),
	m_x(0),
	m_y(0),
	m_width(0),
	m_height(0),
	m_vy(0),
	m_isOnGround(true),
	m_isMoving(false),
	m_hp(100),
	m_posture(0),
	m_maxPosture(kMaxPostureValue),
	m_stock(2),
	m_isDead(false),
	m_state(EnemyState::Idle),
	m_stateFrame(0),
	m_comboCount(0),
	m_maxCombo(1)
{
	m_hitbox = { 0,0,0,0,false };
	m_attackHitbox = { 0,0,0,0,false };
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	m_x = kStartX;
	m_y = kStartY;
	// 表示サイズはスプライト1コマのサイズにスケールを掛けた値
	m_width = kWidth * kScale;
	m_height = kHeight * kScale;
	m_hp = 100;
	m_isDead = false;

	m_state = EnemyState::Idle;
	m_stateFrame = 0;

	//ヒットボックスの初期化（敵の表示サイズに合わせる）
	m_hitbox.width = 80.0f;
	m_hitbox.height = 120.0f;
	m_hitbox.isActive = true;
}

void Enemy::End()
{
	DeleteGraph(m_idleGraph);
	DeleteGraph(m_runGraph);
	DeleteGraph(m_attackGraph);
}

void Enemy::Update(float playerX, float playerY, bool isPlayerAttacking)
{
	if (m_isDead)return;

	//アニメーションを進める
	m_animFrame++;
	m_stateFrame++;
	m_isMoving = false; // 移動中かどうかのフラグをリセット
	m_attackHitbox.isActive = false; //攻撃判定を初期化

	//プレイヤーとの距離計算
	float distanceX = playerX - m_x;
	float absDistanceX = std::abs(distanceX);

	//プレイヤーの方向を向く（移動待機中のみ）
	if (m_state == EnemyState::Idle || m_state == EnemyState::Run)
	{
		m_isFlip = (distanceX < 0);//プレイヤーが右にいれば右向き
	}

	//＊AIステートマシン
	switch (m_state)
	{
	case EnemyState::Idle:
		//一定時間待機していた雷銅に遷移
		if (m_stateFrame > 30)
		{
			m_state = EnemyState::Run;
			m_stateFrame = 0;
		}
		break;

	case EnemyState::Run:
		//プレイヤーへの接近
		if (distanceX > 0)m_x += kMoveSpeed;
		else              m_x -= kMoveSpeed;

		// 攻撃間合いに入ったら攻撃開始
		if (absDistanceX <= kAttackRange)
		{
			m_state = EnemyState::Attack;
			m_stateFrame = 0;
			m_comboCount = 0;
			m_maxCombo = 2 + (rand() % 2);//2回～３回のランダム連撃
		}
		break;

	case EnemyState::Attack:
		//不利アロ氏アニメーションの特定フレームで判定発生
		if (m_stateFrame >= 10 && m_stateFrame <= 16)
		{
			m_attackHitbox.isActive = true;
			m_attackHitbox.width = 80.0f;
			m_attackHitbox.height = 60.0f;
			float direction = (playerX > m_x) ? 1.0f : -1.0f;
			m_attackHitbox.x = m_x + (60.0f * direction);
			m_attackHitbox.y = m_y - 10.0f;
		}

		//１回分の攻撃っモーション終了
		if (m_stateFrame >= kAttackAnimTotalFrame)
		{
			m_comboCount++;
			if (m_comboCount < m_maxCombo && absDistanceX <= kAttackRange + 30.0f)
			{
				//連撃継続：もう一度攻撃ステートをリセットして実行
				m_stateFrame = 0;
			}
			else
			{
				//連撃終了：攻撃後の硬直(AttackWait）へ
				m_state = EnemyState::AttackWait;
				m_stateFrame = 0;
			}
		}
		break;

	case EnemyState::AttackWait:
		//攻撃後の隙（攻撃硬直）
		if (m_stateFrame >= kAttackWaitTime)
		{
			m_state = EnemyState::Idle;
			m_stateFrame = 0;
		}
		break;

	case EnemyState::Guard:
		//ガード中（0.5行間ガード姿勢を維持して復帰）
		if (m_stateFrame >= 30)
		{
			m_state = EnemyState::Idle;
			m_stateFrame = 0;
		}
		break;

	case EnemyState::Stun:
		//体幹崩れ（隙状態）
		if (m_stateFrame >= 120)//2秒間行動不能
		{
			m_posture = 0;
			m_state = EnemyState::Idle;
			m_stateFrame = 0;
		}
		break;
	}

	// 重力と垂直移動の適用
	if (!m_isOnGround)
	{
		m_vy += kGravity;                   // 下向きに加速
		m_y += m_vy;                        // 垂直位置を更新
		int groundY = kGroundY;             // 地面のY座標を定義
		if (m_y >= groundY)                 // 地面に到達した場合
		{
			m_y = groundY;                  // 地面の位置に修正
			m_vy = 0;                       // 垂直速度をリセット
			m_isOnGround = true;            // 地面にいる状態に戻す
		}
	}

	//毎フレーム敵の位置に合わせてヒットボックスの位置を更新
	m_hitbox.x = m_x;
	m_hitbox.y = m_y - 10.0f;
}

//ダメージ＆体幹ダメージ処理
void Enemy::OnDamage(int damage, int postureDamage)
{
	if (m_isDead)return;

	//ガード判定
	if (m_state == EnemyState::Idle || m_state == EnemyState::Run)
	{
		m_state = EnemyState::Guard;
		m_stateFrame = 0;
		m_posture += postureDamage / 5;//ガードして体幹ゲージを削る
		return;
	}

	m_hp -= damage;
	m_posture += postureDamage;//体幹ゲージ増加

	//体幹オーバーチェック
	if (m_posture >= m_maxPosture)
	{
		m_posture = m_maxPosture;

		//体幹上限達成時：体幹崩れへ
		m_state = EnemyState::Stun;
		m_stateFrame = 0;

		//体幹崩れ中さらに攻撃を受けると残機を失う
		if (m_state == EnemyState::Stun && damage > 0)
		{
			m_stock--;
			m_posture = 0;
			if (m_stock <= 0)
			{
				m_isDead = true;
				m_hitbox.isActive = false; // 死亡時は判定を消す
			}
		}
		else
		{
			m_state = EnemyState::Stun;
			m_stateFrame = 0;
		}
	}
}

//パリィされた時の処理
void Enemy::OnParried()
{
	//パリィされたら強制的に大きな体幹ダメージ＋硬直
	m_posture += 30;
	m_state = EnemyState::AttackWait;//攻撃強制中断
	m_stateFrame = -30;//通常より長い隙をつくる

	if (m_posture >= m_maxPosture)
	{
		m_posture = m_maxPosture;
		m_state = EnemyState::Stun;
		m_stateFrame = 0;
	}
}

void Enemy::Draw()
{
	if (m_isDead)return;//死亡時は描画しない

	//移動中かどうかでアニメーションを変更する
	int tempTotalFrame = kIdleAnimTotalFrame;
	int tempHandle = m_idleGraph;
	int currentFrame = m_animFrame;//現在のフレーム数を取得

	if (m_state == EnemyState::Run)
	{
		tempTotalFrame = kRunAnimTotalFrame;
		tempHandle = m_runGraph;
	}
	else if (m_state == EnemyState::Attack)
	{
		tempTotalFrame = kAttackAnimTotalFrame;
		tempHandle = m_attackGraph;
	}

	//現在のフレーム数から表示したいコマ番号を計算で求める
	int animNo = (currentFrame % tempTotalFrame) / kSingleAnimFrame;
	DrawRectRotaGraph(m_x, m_y,                 //描画位置
		animNo * kWidth, 0,                     //描画元の矩形の左上座標
		kWidth, kHeight,                        //描画元の矩形の幅と高さ
		double(kScale), 0.0,                    //拡大率と回転角度
		tempHandle, true,                      //描画するグラフィックハンドル
		m_isFlip);	                            //左右反転フラグ

	// デバッグ描画：状態テキスト表示
	const char* stateStr = "Idle";
	if (m_state == EnemyState::Run) stateStr = "Run";
	if (m_state == EnemyState::Attack) stateStr = "Attack";
	if (m_state == EnemyState::AttackWait) stateStr = "AttackWait";
	if (m_state == EnemyState::Guard) stateStr = "Guard";
	if (m_state == EnemyState::Stun) stateStr = "STUN!";
	DrawString((int)m_x - 20, (int)m_y - 100, stateStr, GetColor(255, 255, 0));

	// デバッグ描画：残機と体幹ゲージ
	DrawFormatString((int)m_x - 30, (int)m_y - 80, GetColor(255, 255, 255), "Stock: %d", m_stock);

	// 体幹ゲージ（赤色バー）
	int barWidth = 80;
	int currentBarWidth = (int)((float)m_posture / m_maxPosture * barWidth);
	DrawBox((int)m_x - 40, (int)m_y - 65, (int)m_x + 40, (int)m_y - 55, GetColor(100, 100, 100), TRUE);
	DrawBox((int)m_x - 40, (int)m_y - 65, (int)m_x - 40 + currentBarWidth, (int)m_y - 55, GetColor(255, 50, 50), TRUE);

	//デバッグ描画：敵の暗い判定を赤枠で表示
	if (m_hitbox.isActive)
	{
		int left = (int)(m_hitbox.x - m_hitbox.width / 2);
		int top = (int)(m_hitbox.y - m_hitbox.height / 2);
		int right = (int)(m_hitbox.x + m_hitbox.width / 2);
		int bottom = (int)(m_hitbox.y + m_hitbox.height / 2);

		DrawBox(left, top, right, bottom, GetColor(255, 0, 0), FALSE);
	}
}
