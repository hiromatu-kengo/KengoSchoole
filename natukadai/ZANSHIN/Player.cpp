#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include <cmath>
#include <cstdlib>

namespace
{
	constexpr int kWidth = 96;	                                            //1コマの幅
	constexpr int kHeight = 96;                         	                //1コマの高さ
	//アニメーションの関連の定義
	constexpr int kIdleAnimNum = 10;	                                    //待機アニメーションのコマ数
	constexpr int kRunAnimNum = 16;	                                        //走るアニメーションのコマ数
	constexpr int kAttackAnimNum = 7;	                                    //攻撃アニメーションのコマ数

	constexpr int kSingleAnimFrame = 4;	                                    //アニメ1コマに書けるフレーム数

	//アニメーション1ループにかかるフレーム数
	constexpr int kIdleAnimTotalFrame = kIdleAnimNum * kSingleAnimFrame;    //待機アニメーションの1ループにかかるフレーム数
	constexpr int kRunAnimTotalFrame = kRunAnimNum * kSingleAnimFrame;      //走るアニメーションの1ループにかかるフレーム数
	constexpr int kAttackAnimTotalFrame = kAttackAnimNum * kSingleAnimFrame; //攻撃アニメーションの1ループにかかるフレーム数

	constexpr int kMoveSpeed = 10;                                          // 移動速度
	constexpr int kMaxFrames = 10;                                          // 最大フレーム数
	constexpr int kGravity = 2;                                             // 重力加速度
	constexpr int kJumpPower = 40;                                          // ジャンプ初速
	constexpr int kGroundY = Game::kScreenHeight / 2 + kHeight / 2;         // 地面のY座標（仮定）
	constexpr float kStartX = Game::kScreenWidth / 4;                                          // プレイヤーの初期X座標
	constexpr float kStartY = Game::kScreenHeight / 2 + kHeight / 2;        // プレイヤーの初期Y座標
	constexpr int kParryMaxFrame = 10;                                      // パリィ状態の最大フレーム数
}

Player::Player() :
	m_frameIndex(0),
	m_animFrame(0),
	m_idleGraph(-1),
	m_runGraph(-1),
	m_attackGraph(-1),
	m_graphCount(0),
	m_x(0),
	m_y(0),
	m_width(0),
	m_height(0),
	m_rightClickFrame(0),
	m_attackFrame(0),
	m_isFlip(false),
	m_isMoving(false),
	m_state(PlayerState::Normal),
	m_attackHitbox{ 0, 0, 0, 0, false }
{
	// initialize handles array to -1
	for (int i = 0; i < 10; ++i) m_playerGHandle[i] = -1;
}

Player::~Player()
{
}

void Player::Init()
{
	m_x = static_cast<int>(kStartX);
	m_y = static_cast<int>(kStartY);
	m_animFrame = 0;

	//シーン切り替えなどにリセット
	m_rightClickFrame = 0;  // 右クリックフレーム数をリセット
	m_attackFrame = 0;      // 攻撃フレーム数をリセット
	m_isLeftClickPrev = false;//リセット
	m_state = PlayerState::Normal;
	m_stunFrame = 0; // リセット処理を追加

	// ステータス初期化
	m_hp = 1000;
	m_maxHp = 1000;
	m_posture = 0;
	m_maxPosture = 100;

	m_shakeFrame = 0;
	m_shakeIntensity = 0;
	m_parryEffectFrame = 0;
	m_hitStopFrame = 0;
	m_slashEffectFrame = 0;

	// SEの読み込み
	m_seAttack = LoadSoundMem("sound/at.mp3");
	m_seGuard = LoadSoundMem("sound/gd.mp3");
	m_seParry = LoadSoundMem("sound/pl.mp3");
	m_seDead = LoadSoundMem("sound/ns.mp3");

	m_deadTimer = 0;
	m_isDeadFinished = false;
}

void Player::End()
{
	DeleteGraph(m_idleGraph);
	DeleteGraph(m_runGraph);
	DeleteGraph(m_attackGraph);

	// SEのメモリ解放
	DeleteSoundMem(m_seAttack);
	DeleteSoundMem(m_seGuard);
	DeleteSoundMem(m_seParry);
	DeleteSoundMem(m_seDead);
}

void Player::OnDamage(int damage, int postureDamage)
{
	// ガード時は体幹ダメージのみ受け流す
	if (m_state == PlayerState::Guard)
	{
		m_posture += postureDamage;
		// ガードの削り手応え演出：軽めの振動とノックバック
		m_shakeFrame = 5;
		m_shakeIntensity = 4;
		m_x += m_isFlip ? 10 : -10; // 後ろへ押し戻される

		PlaySoundMem(m_seGuard, DX_PLAYTYPE_BACK); // ★ガード音
	}
	else
	{
		m_hp -= damage;
		m_posture += postureDamage / 3;
		if (m_hp <= 0)
		{
			m_hp = 0;
			PlaySoundMem(m_seDead, DX_PLAYTYPE_BACK); // ★やられた音
		}

		// 被弾時の強い手応え演出
		m_shakeFrame = 12;
		m_shakeIntensity = 10;
		m_hitStopFrame = 3; // 被弾ヒットストップ
		
		//HPが0以下になった場合、死亡状態に遷移
		if (m_hp <= 0)
		{
			m_hp = 0;
			m_state = PlayerState::Dead; // 死亡状態に遷移
			m_shakeFrame = 25;			 //	死亡時の強い画面揺れ
			m_shakeIntensity = 18;
			m_deadTimer = 0;			 // 死亡演出タイマーをリセット
			PlaySoundMem(m_seDead, DX_PLAYTYPE_BACK); // やられた音
		}
	}

	// 体幹ゲージ上限到達時の姿勢崩れ処理（必要に応じて追加可能）
	if (m_posture >= m_maxPosture)
	{
		m_posture = m_maxPosture;
		m_state = PlayerState::Stun;
		m_stunFrame = 120; // 約2秒間（60FPS想定）行動不能

		// 被弾以上の大きなノックバックと画面揺れ演出
		m_shakeFrame = 20;
		m_shakeIntensity = 15;
	}
}

// パリィ成功時に呼び出す関数
void Player::OnParrySuccess(float hitX, float hitY)
{
	// 1. 激しい画面振動
	m_shakeFrame = 15;
	m_shakeIntensity = 14;

	// 2. 視覚的エフェクト（火花＆光彩リング）の設定
	m_parryEffectFrame = 18;
	m_parryEffectMaxFrame = 18;
	m_parryEffectX = static_cast<int>(hitX);
	m_parryEffectY = static_cast<int>(hitY);

	// 3. ヒットストップ（時間一瞬停止）
	m_hitStopFrame = 4;

	// 4. プレイヤーのノックバック（パリィの反動でわずかに距離が空く）
	m_x += m_isFlip ? 15 : -15;

	PlaySoundMem(m_seParry, DX_PLAYTYPE_BACK); // ★パリィ成功音
}

// 攻撃ヒット時の演出処理
void Player::OnHitSuccess(float hitX, float hitY)
{
	m_shakeFrame = 8;
	m_shakeIntensity = 6;
	m_hitStopFrame = 7; // 刀が手ごたえで引っかかるヒットストップ

	m_slashEffectFrame = 10;
	m_slashEffectX = static_cast<int>(hitX);
	m_slashEffectY = static_cast<int>(hitY);
}

void Player::Update()
{
	// ヒットストップ処理：時間停止中は動きをストップ
	if (m_hitStopFrame > 0)
	{
		m_hitStopFrame--;
		return;
	}

	//アニメーションを進める
	m_animFrame++;
	m_attackHitbox.isActive = false; // 攻撃判定をデフォルトで無効にする

	// パリィの振動・演出時間の減衰
	if (m_shakeFrame > 0)
	{
		m_shakeFrame--;
		int range = m_shakeIntensity * 2 + 1;
		m_shakeOffsetX = (rand() % range) - m_shakeIntensity;
		m_shakeOffsetY = (rand() % range) - m_shakeIntensity;
	}
	else
	{
		m_shakeOffsetX = 0;
		m_shakeOffsetY = 0;
	}

	if (m_parryEffectFrame > 0) m_parryEffectFrame--;
	if (m_slashEffectFrame > 0) m_slashEffectFrame--;

	if (m_state == PlayerState::Dead)
	{
		m_deadTimer++;
		if (m_deadTimer >= 180) // 3秒間の死亡演出後にフラグを立てる
		{
			m_isDeadFinished = true;
		}
		return;
	}

	// 姿勢崩れ（Stun）状態の処理
	if (m_state == PlayerState::Stun)
	{
		m_stunFrame--;
		if (m_stunFrame <= 0)
		{
			m_state = PlayerState::Normal;
			m_posture = 0; // 復帰時に体幹ゲージをリセット
		}
		return; // スタン中は移動・攻撃・ガード入力をすべてスキップ
	}

	// 体幹の自然回復（非戦闘時・非ガード時）
	if (m_state == PlayerState::Normal && m_posture > 0)
	{
		// 4フレームに1ポイントだけ回復（1秒間に15回復：全回復まで約6.6秒）
		if (m_animFrame % 4 == 0)
		{
			m_posture--;
		}
	}

	// --- マウス入力を取得 ---
	int mouseInput = GetMouseInput();
	bool isLeftClickCurrent = (mouseInput & MOUSE_INPUT_LEFT) != 0;

	// 「今押された瞬間」かどうかを判定 (トリガー検出)
	bool isLeftClickTrigger = isLeftClickCurrent && !m_isLeftClickPrev;

	// 前フレームの状態を更新
	m_isLeftClickPrev = isLeftClickCurrent;

	// 攻撃状態の処理
	if (m_state == PlayerState::Attack)
	{
		m_attackFrame++; // 攻撃中は攻撃フレームをカウント

		if (m_attackFrame >= 0 && m_attackFrame < kAttackAnimTotalFrame)
		{
			// 攻撃判定を有効にする
			m_attackHitbox.isActive = true;
			// 攻撃判定のサイズ
			float atkW = 80.0f;
			float atkH = 60.0f;
			// 表示サイズから垂直オフセット（中心より下）を計算。m_height が未設定の場合は推定値を使う
			float displayHeight = (m_height > 0) ? static_cast<float>(m_height) : static_cast<float>(kHeight * 4);
			float displayWidth = (m_width > 0) ? static_cast<float>(m_width) : static_cast<float>(kWidth * 4);
			//攻撃の判定の位置を変えたいなら↓の数値を変える
			float verticalOffset = displayHeight * 0.25f; // 中心より下寄せ
			float horizontalOffset = displayWidth * 0.4; // 前方に配置

			if (m_isFlip)
			{
				m_attackHitbox.x = static_cast<int>(m_x - horizontalOffset);
			}
			else
			{
				m_attackHitbox.x = static_cast<int>(m_x + horizontalOffset);
			}
			m_attackHitbox.y = static_cast<int>(m_y + verticalOffset);
			m_attackHitbox.width = atkW;
			m_attackHitbox.height = atkH;
		}

		if (m_attackFrame >= kAttackAnimTotalFrame)
		{
			m_state = PlayerState::Normal;
			m_attackFrame = 0;
		}
	}
	else// パリィ・ガード・通常状態の処理
	{
		// 左クリックが「押された瞬間」のみ攻撃へ遷移
		if (isLeftClickTrigger && m_state != PlayerState::Attack)
		{
			m_state = PlayerState::Attack;
			m_attackFrame = 0;
			PlaySoundMem(m_seAttack, DX_PLAYTYPE_BACK); // 攻撃音
		}
		else
		{
			if (GetMouseInput() & MOUSE_INPUT_RIGHT)
			{
				m_rightClickFrame++;                // 右クリックが押されている場合、フレーム数をカウント
			}
			else
			{
				m_rightClickFrame = 0;              // 右クリックが離された場合、フレーム数をリセット
			}

			if (m_rightClickFrame > 0 && m_rightClickFrame <= kParryMaxFrame)
			{
				m_state = PlayerState::Parry;       // パリィ状態に遷移

			}
			else if (m_rightClickFrame > kParryMaxFrame)
			{
				m_state = PlayerState::Guard;       // ガード状態に遷移
			}
			else
			{
				m_state = PlayerState::Normal;      // 通常状態に戻す
			}
		}
	}

	m_isMoving = false;                     // 移動中フラグをリセット

	// 左右移動の処理（通常状態のみ）
	if (m_state == PlayerState::Normal)
	{
		if (CheckHitKey(KEY_INPUT_D))
		{
			m_x += kMoveSpeed;                  // 右移動
			m_isFlip = false;                   // 右向き
			m_isMoving = true;                  // 移動中フラグをセット
		}
		if (CheckHitKey(KEY_INPUT_A))
		{
			m_x -= kMoveSpeed;                  // 左移動
			m_isFlip = true;                    // 左向き 
			m_isMoving = true;                  // 移動中フラグをセット
		}
		// ジャンプ開始（地面にいるときスペースでジャンプ）
		if (CheckHitKey(KEY_INPUT_SPACE) && m_isOnGround)
		{
			m_vy = -kJumpPower;             // 初速（上方向に負）
			m_isOnGround = false;
		}
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
}

void Player::Draw()
{

	// カメラシェイク適用位置
	int drawX = m_x + m_shakeOffsetX;
	int drawY = m_y + m_shakeOffsetY;

	int tempTotalFrame = kIdleAnimTotalFrame;
	int tempHanndle = m_idleGraph;
	int currentFrame = m_animFrame;

	if (m_state == PlayerState::Attack)
	{
		tempTotalFrame = kAttackAnimTotalFrame;
		tempHanndle = m_attackGraph;
		currentFrame = m_attackFrame;
	}
	else if (m_isMoving)
	{
		tempTotalFrame = kRunAnimTotalFrame;
		tempHanndle = m_runGraph;
	}
	if (m_state == PlayerState::Dead)
	{
		// 死亡状態の描画（赤黒く点滅）
		if ((m_animFrame / 6) % 2 == 0)
		{
			SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
			DrawCircle(drawX, drawY + 20, 50, GetColor(255, 30, 30), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}

	int animNo = (currentFrame % tempTotalFrame) / kSingleAnimFrame;
	DrawRectRotaGraph(drawX, drawY,
		animNo * kWidth, 0,
		kWidth, kHeight,
		double(4.0), 0.0,
		tempHanndle, true,
		m_isFlip);

	// ガード / パリィ 状態の視覚的フィードバック（位置の低く調整）
	if (m_state == PlayerState::Parry)
	{
		// 【パリィ受付中】：プレイヤーの前方に強い黄色の閃光オーラを表示
		SetDrawBlendMode(DX_BLENDMODE_ADD, 180);
		float offsetX = m_isFlip ? -40.0f : 40.0f;

		// 位置を調整
		int effectY = drawY + 80;

		// 黄金の円形オーラと放射状のライン
		DrawCircle(drawX + static_cast<int>(offsetX), effectY, 45, GetColor(255, 220, 50), TRUE);
		DrawCircle(drawX + static_cast<int>(offsetX), effectY, 55, GetColor(255, 255, 200), FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// 「PARRY READY」文字表示の位置も少し下げる (drawY - 110 -> drawY - 90)
		DrawString(drawX - 40, drawY - 90, "PARRY READY", GetColor(255, 220, 0));
	}
	else if (m_state == PlayerState::Guard)
	{
		// 【ガード中】：体の前方に青い防御シールドの壁を表示
		SetDrawBlendMode(DX_BLENDMODE_ADD, 160);
		int shieldX = drawX + (m_isFlip ? -45 : 45);

		// 位置を低く調整 (drawY - 60 / + 40 -> drawY - 20 / + 60)
		DrawBox(shieldX - 5, drawY - 20, shieldX + 5, drawY + 60, GetColor(100, 180, 255), TRUE);
		DrawCircle(shieldX, drawY + 20, 50, GetColor(150, 220, 255), FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// 「GUARD」文字表示の位置も少し下げる (drawY - 110 -> drawY - 90)
		DrawString(drawX - 25, drawY - 90, "GUARD", GetColor(100, 200, 255));
	}

	if (m_state == PlayerState::Stun)
	{
	// 強化版：スタン（姿勢崩れ）演出
		if (m_state == PlayerState::Stun)
		{
			
			// 頭上をぐるぐる回る星/火花エフェクト（ピヨピヨ演出）
			SetDrawBlendMode(DX_BLENDMODE_ADD, 220);
			int starCenterY = drawY - 90; // 頭上のY座標
			float angleBase = static_cast<float>(m_animFrame) * 0.15f; // 回転速度

			for (int i = 0; i < 3; ++i)
			{
				// 120度ずつずらして3つの星（丸）を回す
				float angle = angleBase + (i * (3.14159265f * 2.0f / 3.0f));
				int starX = drawX + static_cast<int>(cos(angle) * 35.0f); // 横幅35pxで楕円回転
				int starY = starCenterY + static_cast<int>(sin(angle) * 12.0f); // 縦幅12px

				// 黄色と橙のグラデーション発光
				DrawCircle(starX, starY, 6, GetColor(255, 230, 80), TRUE);
				DrawCircle(starX, starY, 10, GetColor(255, 100, 0), FALSE);
			}

			// プレイヤー本体の赤黒明滅＆電気ショックオーラ
			if ((m_animFrame / 3) % 2 == 0)
			{
				// 赤い警告オーラ
				DrawCircle(drawX, drawY + 20, 50, GetColor(255, 30, 30), TRUE);
				// 稲妻のようなクラックライン
				int rx1 = (rand() % 60) - 30;
				int ry1 = (rand() % 80) - 40;
				int rx2 = (rand() % 60) - 30;
				int ry2 = (rand() % 80) - 40;
				DxLib::DrawLine(drawX + rx1, drawY + ry1, drawX + rx2, drawY + ry2, GetColor(255, 255, 100), 2);
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			// 画面中央上部の「体幹崩れ！」巨大警告アラートUI
			int alertY = 120;
			int alertWidth = 320;
			int alertHeight = 40;
			int alertLeft = (Game::kScreenWidth - alertWidth) / 2;

			// 赤黒い帯背景
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
			DrawBox(alertLeft, alertY, alertLeft + alertWidth, alertY + alertHeight, GetColor(150, 0, 0), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			// 黄色い枠線
			DrawBox(alertLeft, alertY, alertLeft + alertWidth, alertY + alertHeight, GetColor(255, 200, 0), FALSE);

			// 点滅する文字
			if ((m_animFrame / 6) % 2 == 0)
			{
				DrawString(alertLeft + 85, alertY + 12, "!! POSTURE BROKEN !!", GetColor(255, 255, 255));
			}
			else
			{
				DrawString(alertLeft + 85, alertY + 12, "!! POSTURE BROKEN !!", GetColor(255, 50, 50));
			}

			// 頭上のデバッグテキストも強調
			DrawString(drawX - 45, drawY - 120, "STUNNED!!", GetColor(255, 50, 50));
		}
	}

	// 強化版パリィエフェクト（閃光・火花・衝撃波リング）
	if (m_parryEffectFrame > 0)
	{
		int progress = m_parryEffectMaxFrame - m_parryEffectFrame;

		// 拡散する白い中心閃光
		DrawCircle(m_parryEffectX, m_parryEffectY, 15 + progress * 2, GetColor(255, 255, 230), TRUE);

		// 拡大する衝撃波リング
		SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
		DrawCircle(m_parryEffectX, m_parryEffectY, 10 + progress * 5, GetColor(255, 180, 50), FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// 飛散する火花（高密度 12 本）
		for (int i = 0; i < 12; ++i)
		{
			double angle = i * (3.14159265 * 2.0 / 12.0);
			int startDist = progress * 3;
			int endDist = 20 + progress * 6;

			int sx = m_parryEffectX + static_cast<int>(cos(angle) * startDist);
			int sy = m_parryEffectY + static_cast<int>(sin(angle) * startDist);
			int ex = m_parryEffectX + static_cast<int>(cos(angle) * endDist);
			int ey = m_parryEffectY + static_cast<int>(sin(angle) * endDist);

			DxLib::DrawLine(sx, sy, ex, ey, GetColor(255, 230, 100), 3);
		}
	}

	// 攻撃ヒットエフェクト（赤黄色い刀傷スラッシュライン）
	if (m_slashEffectFrame > 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 220);
		DxLib::DrawLine(m_slashEffectX - 25, m_slashEffectY - 25, m_slashEffectX + 25, m_slashEffectY + 25, GetColor(255, 50, 50), 5);
		DxLib::DrawLine(m_slashEffectX - 15, m_slashEffectY - 15, m_slashEffectX + 15, m_slashEffectY + 15, GetColor(255, 255, 200), 3);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// UI描画：HPバー & 体幹ゲージ
	int barX = drawX - 40;
	int barY = drawY - 80;

	DxLib::DrawBox(barX, barY, barX + 80, barY + 6, GetColor(50, 50, 50), TRUE);
	int currentHpWidth = static_cast<int>(80.0f * (static_cast<float>(m_hp) / m_maxHp));
	DxLib::DrawBox(barX, barY, barX + currentHpWidth, barY + 6, GetColor(0, 230, 100), TRUE);

	if (m_postureUiGraph[0] != -1)
	{
		// 体幹の溜まり具合（0.0f ～ 1.0f）
		float ratio = static_cast<float>(m_posture) / static_cast<float>(m_maxPosture);

		// 割合に応じて 0 (100%/満タン) ～ 5 (0%/空) のインデックスを選択
		int uiIndex = 5 - static_cast<int>(ratio * 5.0f);
		if (uiIndex < 0) uiIndex = 0;
		if (uiIndex > 5) uiIndex = 5;

		// 画面下部の中央付近に拡大表示（scale: 3.0倍）
		int uiX = Game::kScreenWidth / 1000 - 30;
		int uiY = Game::kScreenHeight - 50; // 画面下部の表示位置

		// 横倍率と縦倍率を個別指定
		double xScale = 35.0; // 横方向の拡大倍率（数値を大きくすると横に伸びます）
		double yScale = 4.0;  // 縦方向の拡大倍率

		// DrawRotaGraph3(x, y, cx, cy, ExtX, ExtY, Angle, GrHandle, TransFlag)
		// cx=0, cy=0 で画像の中心を回転・拡大軸に指定
		DrawRotaGraph3(uiX, uiY, 0, 0, xScale, yScale, 0.0, m_postureUiGraph[uiIndex], TRUE);
	}

	// デバッグ表示
	if (m_state == PlayerState::Parry) DrawString(drawX, drawY - 100, "Parry!", GetColor(255, 255, 0));

	if (m_attackHitbox.isActive)
	{
		int left = static_cast<int>(m_attackHitbox.x - m_attackHitbox.width / 2);
		int top = static_cast<int>(m_attackHitbox.y - m_attackHitbox.height / 2);
		int right = static_cast<int>(m_attackHitbox.x + m_attackHitbox.width / 2);
		int bottom = static_cast<int>(m_attackHitbox.y + m_attackHitbox.height / 2);
		//DxLib::DrawBox(left, top, right, bottom, GetColor(255, 0, 0), FALSE);
	}
}

void Player::Release()
{
}
