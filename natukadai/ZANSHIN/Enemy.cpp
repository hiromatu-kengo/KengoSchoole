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
	constexpr float kStartX = Game::kScreenWidth / 2 + Game::kScreenWidth / 4;                                         // 敵の初期X座標
	constexpr float kStartY = Game::kScreenHeight / 2 + kHeight;			// 敵の初期Y座標
	constexpr int kParryMaxFrame = 10;                                      // パリィ状態の最大フレーム数

	//AI設定値
	constexpr float kAttackRange = 150.0f;									//攻撃に移る距離
	constexpr int kAttackWaitTime = 60;										//攻撃後の隙
	constexpr int kMaxPostureValue = 100;									//最大体幹値
	constexpr int kSignTime = 30;											//攻撃前の溜め時間（30フレーム＝0.5秒）

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

void Enemy::Update(float playerX, float playerY, float playerWidth, bool isPlayerAttacking)
{
	if (m_isDead)return;

	// ヒットストップ中は敵の動きやアニメーションを静止させる
	if (m_hitStopFrame > 0)
	{
		m_hitStopFrame--;
		return;
	}

	//アニメーションを進める
	m_animFrame++;
	m_stateFrame++;
	m_isMoving = false; // 移動中かどうかのフラグをリセット
	m_attackHitbox.isActive = false; //攻撃判定を初期化

	//プレイヤーとの距離計算
	float distanceX = playerX - m_x;
	float absDistanceX = std::abs(distanceX);

	// ノックバック（ダメージを受けた時の押し出し）の適用
	if (std::abs(m_knockbackVx) > 0.1f)
	{
		m_x += m_knockbackVx;
		m_knockbackVx *= 0.8f; // 摩擦で減衰
	}
	else
	{
		m_knockbackVx = 0.0f;
		// プレイヤーとの通常押し戻し処理（体当たり貫通を防止）
		float minDistance = (m_hitbox.width / 2.0f) + (playerWidth / 2.0f);
		if (absDistanceX < minDistance)
		{
			float pushOffset = minDistance - absDistanceX;
			if (distanceX > 0) m_x -= pushOffset;
			else               m_x += pushOffset;
		}
	}

	// エフェクトフレーム減衰
	if (m_damageEffectFrame > 0) m_damageEffectFrame--;

	// 向きの更新（移動・待機・溜め中）
	if (m_state == EnemyState::Idle || m_state == EnemyState::Run || m_state == EnemyState::AttackSign)
	{
		m_isFlip = (distanceX < 0);
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

	case EnemyState::AttackSign:
		//0.5秒間「攻撃くるぞ！」という溜め時間を作ってから振り下ろす
		if (m_stateFrame >= kSignTime)
		{
			m_state = EnemyState::Attack;
			m_stateFrame = 0;
		}
		break;

	case EnemyState::Attack:
		//アニメーションの特定フレームで判定発生
		if (m_stateFrame >= 20 && m_stateFrame <= 26)
		{
			m_attackHitbox.isActive = true;
			m_attackHitbox.width = 100.0f;
			m_attackHitbox.height = 100.0f;
			// 向きに合わせて攻撃判定を前に出す
			float direction = m_isFlip ? -1.0f : 1.0f;
			m_attackHitbox.x = m_x + (100.0f * direction);
			m_attackHitbox.y = m_y - 20.0f;
		}
		else
		{
			m_attackHitbox.isActive = false;
		}

		//１回分の攻撃っモーション終了
		if (m_stateFrame >= kAttackAnimTotalFrame)
		{
			m_attackHitbox.isActive = false;
			m_comboCount++;
			if (m_comboCount < m_maxCombo && absDistanceX <= kAttackRange + 30.0f)
			{
				// 連撃：次の攻撃も溜めから開始
				m_state = EnemyState::AttackSign;
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
		m_vy += kGravity;
		m_y += m_vy;
		if (m_y >= kGroundY)
		{
			m_y = static_cast<float>(kGroundY);
			m_vy = 0;
			m_isOnGround = true;
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

	// 斬撃がヒットした時の重厚感（ヒットストップ 8フレーム ＋ 斬撃エフェクト発動）
	m_hitStopFrame = 3;
	m_damageEffectFrame = 12;

	// 被弾時ののけ反りノックバック（プレイヤーの位置と反対方向に少し吹き飛ぶ）
	m_knockbackVx = m_isFlip ? 6.0f : -6.0f;

	// スタン（体幹崩れ）中に攻撃を受けた場合：忍殺（トドメ）処理
	if (m_state == EnemyState::Stun)
	{
		m_stock--;
		m_posture = 0;

		if (m_stock <= 0)
		{
			m_isDead = true;
			m_state = EnemyState::Dead;
			m_hitbox.isActive = false;
			m_attackHitbox.isActive = false;
		}
		else
		{
			m_state = EnemyState::Idle;
			m_stateFrame = 0;
		}
		return;
	}

	m_hp -= damage;
	m_posture += postureDamage;//体幹ゲージ増加

	// 体幹オーバーチェック
	if (m_posture >= m_maxPosture)
	{
		m_posture = m_maxPosture;
		m_state = EnemyState::Stun;
		m_stateFrame = 0;
	}
}

//パリィされた時の処理
void Enemy::OnParried()
{
	// 弾かれた時も少しヒットストップをかけて手応えを出す
	m_hitStopFrame = 6;
	//パリィされたら強制的に大きな体幹ダメージ＋硬直
	m_posture += 30;
	m_attackHitbox.isActive = false; // 弾かれたら即座に判定消滅
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
	else if (m_state == EnemyState::Attack || m_state == EnemyState::AttackSign)
	{
		tempTotalFrame = kAttackAnimTotalFrame;
		tempHandle = m_attackGraph;
		if (m_state == EnemyState::Attack)
		{
			currentFrame = m_stateFrame;
		}
	}

	//現在のフレーム数から表示したいコマ番号を計算で求める
	int animNo = (currentFrame % tempTotalFrame) / kSingleAnimFrame;
	DrawRectRotaGraph(m_x, m_y,                 //描画位置
		animNo * kWidth, 0,                     //描画元の矩形の左上座標
		kWidth, kHeight,                        //描画元の矩形の幅と高さ
		double(kScale), 0.0,                    //拡大率と回転角度
		tempHandle, true,                      //描画するグラフィックハンドル
		m_isFlip);	                            //左右反転フラグ

	// 敵が斬られた瞬間のスラッシュエフェクト（閃光）
	if (m_damageEffectFrame > 0)
	{
		int p = 12 - m_damageEffectFrame;
		SetDrawBlendMode(DX_BLENDMODE_ADD, 220);
		DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y) - 30, 15 + p * 3, GetColor(255, 200, 50), FALSE);
		DrawLine(static_cast<int>(m_x) - 30, static_cast<int>(m_y) - 50, static_cast<int>(m_x) + 30, static_cast<int>(m_y), GetColor(255, 255, 255), 4);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// 攻撃前兆エフェクト（赤色の警告閃光＆円形リング）
	if (m_state == EnemyState::AttackSign)
	{
		int signY = static_cast<int>(m_y) - 100;
		int signX = static_cast<int>(m_x);

		// 加算合成で危険信号の赤オーラを発光させる
		SetDrawBlendMode(DX_BLENDMODE_ADD, 180);

		// 時間経過（m_stateFrame）に合わせて円が広がる予兆エフェクト
		int ringRadius = 10 + (m_stateFrame * 2); // 段階的に拡大
		DrawCircle(signX, signY, ringRadius, GetColor(255, 30, 30), FALSE); // 拡散リング
		DrawCircle(signX, signY, 20, GetColor(255, 80, 0), TRUE);           // 中心発光

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// 『危険！』の赤文字を表示
		DrawString(signX - 16, signY - 8, "DANGER!", GetColor(255, 255, 255));

		// 武器の位置へ向けて赤い予兆ラインを引く（攻撃の軌道を可視化）
		float attackDir = m_isFlip ? -1.0f : 1.0f;
		int lineStartX = signX;
		int lineEndX = static_cast<int>(m_x + (80.0f * attackDir));
		DrawLine(lineStartX, signY, lineEndX, signY + 40, GetColor(255, 50, 50), 3);
	}

	// 攻撃判定描画
	if (m_attackHitbox.isActive)
	{
		int left = static_cast<int>(m_attackHitbox.x - m_attackHitbox.width / 2);
		int top = static_cast<int>(m_attackHitbox.y - m_attackHitbox.height / 2);
		int right = static_cast<int>(m_attackHitbox.x + m_attackHitbox.width / 2);
		int bottom = static_cast<int>(m_attackHitbox.y + m_attackHitbox.height / 2);

		DrawBox(left, top, right, bottom, GetColor(255, 255, 0), FALSE);
	}

	// デバッグ描画：状態テキスト表示
	const char* stateStr = "Idle";
	if (m_state == EnemyState::Run) stateStr = "Run";
	if (m_state == EnemyState::AttackSign) stateStr = "SIGN!";
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
