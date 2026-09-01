#include "SceneMain.h"
#include"DxLib.h"
#include "Windows.h"
#include "Game.h"

namespace
{
	constexpr int kScreenX = Game::kScreenWidth / 4;
	constexpr int kScreenY = Game::kScreenHeight / 2;
	// プレイヤーのアニメーションフレーム数
	constexpr int kPlayerFrameCount = 10;
	constexpr int kFadeSpeed = 8;
}

SceneMain::SceneMain() :
	m_playerIdleHandle(-1),
	m_playerRunHandle(-1),
	m_playerAttackHandle(-1),
	m_enemyIdleHandle(-1),
	m_enemyRunHandle(-1),
	m_enemyAttackHandle(-1),
	m_postureUiHandle(-1),
	m_bgmHandle(-1),
	m_bg(),
	m_player(),
	m_enemy(),
	m_playerHasHit(false),
	m_fadeAlpha(255),
	m_isFadingIn(true),
	m_isFadingOut(false),
	m_nextScene(SceneType::Main)
{
	for (int i = 0; i < 6; ++i)
	{
		m_postureUiHandle[i] = -1;
		m_enemyPostureUiHandle[i] = -1;
	}
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	// 画像を縦6分割で読み込み（幅・高さは画像の解像度に合わせて自動取得、または指定）
	// 画像全体サイズに併せて 1コマあたりのサイズを指定してください（例：幅64px, 高さ12pxの場合）
	int imgW = 0, imgH = 0;
	int tempGraph = LoadGraph("image/UI/ph.png"); // 一旦読み込んでサイズ取得
	GetGraphSize(tempGraph, &imgW, &imgH);
	DeleteGraph(tempGraph);

	int singleH = imgH / 6; // 6段分割
	LoadDivGraph("image/ui/ph.png", 6, 1, 6, imgW, singleH, m_postureUiHandle);

	int enemyImgW = 0, enemyImgH = 0;
	int tempEnemyGraph = LoadGraph("image/UI/eh.png");
	GetGraphSize(tempEnemyGraph, &enemyImgW, &enemyImgH);
	DeleteGraph(tempEnemyGraph);

	int singleEnemyH = enemyImgH / 6; // 6段分割
	LoadDivGraph("image/UI/eh.png", 6, 1, 6, enemyImgW, singleEnemyH, m_enemyPostureUiHandle);

	//シーン内で使用するリソースのロード
	// 戻り値を使わず配列の中身をチェックする
	m_playerIdleHandle = LoadGraph("image/player/idle.png");
	m_playerRunHandle = LoadGraph("image/player/run.png");
	m_playerAttackHandle = LoadGraph("image/player/ATTACK 1.png");

	m_enemyIdleHandle = LoadGraph("image/enemy/Idle.png");
	m_enemyRunHandle = LoadGraph("image/enemy/Walk.png");
	m_enemyAttackHandle = LoadGraph("image/enemy/Atk.png");
	m_enemyDeathHandle = LoadGraph("image/enemy/Death.png"); // Death.pngの読み込み

	m_bgmHandle = LoadSoundMem("sound/bgm_b.mp3");
	if (m_bgmHandle != -1)
	{
		ChangeVolumeSoundMem(0, m_bgmHandle);
		PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP); // バックグラウンドでループ再生
	}

	m_bg.Init();

	// 読み込んだ配列を Player に渡す（内部配列へコピー）
	m_player.SetIdleGraph(m_playerIdleHandle);
	m_player.SetRunGraph(m_playerRunHandle);
	m_player.SetAttackGraph(m_playerAttackHandle);

	// Playerにハンドルを渡す
	m_player.SetPostureUIHandle(m_postureUiHandle);

	m_enemy.SetIdleGraph(m_enemyIdleHandle);
	m_enemy.SetRunGraph(m_enemyRunHandle);
	m_enemy.SetAttackGraph(m_enemyAttackHandle);
	m_enemy.SetDeathGraph(m_enemyDeathHandle); // Enemyへ渡す
	m_enemy.SetPostureUIHandle(m_enemyPostureUiHandle);

	// 初期配置を設定
	m_player.Init();
	m_enemy.Init();
	m_playerHasHit = false;

	m_fadeAlpha = 255;
	m_isFadingIn = true;
	m_isFadingOut = false;
	m_nextScene = SceneType::Main;
}

void SceneMain::End()
{
	if (m_bgmHandle != -1)
	{
		StopSoundMem(m_bgmHandle);
		DeleteSoundMem(m_bgmHandle);
		m_bgmHandle = -1;
	}

	DeleteGraph(m_playerIdleHandle);
	DeleteGraph(m_playerRunHandle);
	DeleteGraph(m_playerAttackHandle);
	for (int i = 0; i < 6; ++i){DeleteGraph(m_postureUiHandle[i]);}

	DeleteGraph(m_enemyIdleHandle);
	DeleteGraph(m_enemyRunHandle);
	DeleteGraph(m_enemyAttackHandle);
	DeleteGraph(m_enemyDeathHandle); // 破棄処理
	for (int i = 0; i < 6; ++i){DeleteGraph(m_enemyPostureUiHandle[i]);}
	m_bg.End();
}

SceneType SceneMain::Update()
{
	// フェードイン処理（暗転解除）
	if (m_isFadingIn)
	{
		m_fadeAlpha -= kFadeSpeed;
		if (m_fadeAlpha <= 0)
		{
			m_fadeAlpha = 0;
			m_isFadingIn = false;
		}
		// 画面の透明度に合わせて音量を上げる (255 - alpha)
		if (m_bgmHandle != -1)
		{
			ChangeVolumeSoundMem(255 - m_fadeAlpha, m_bgmHandle);
		}
	}

	// フェードアウト処理（暗転してシーン切り替え）
	if (m_isFadingOut)
	{
		m_fadeAlpha += kFadeSpeed;
		if (m_fadeAlpha >= 255)
		{
			m_fadeAlpha = 255;
			return m_nextScene; // 画面が真っ黒になったら新しいシーンへ遷移
		}
		// 画面の暗さに合わせて音量を下げる (255 - alpha)
		if (m_bgmHandle != -1)
		{
			ChangeVolumeSoundMem(255 - m_fadeAlpha, m_bgmHandle);
		}
		return SceneType::Main; // フェードアウト中もメインシーンを維持
	}

	// プレイヤー更新
	m_player.Update();

	if (m_player.IsDeadFinished())
	{
		if (!m_isFadingOut)
		{
			m_isFadingOut = true;
			m_nextScene = SceneType::Title;// プレイヤー死亡時はタイトル画面へ遷移
		}
	}

	// 敵撃破時：そのままシーン遷移せずフェードアウトを開始する
	if (m_enemy.IsDeadFinished())
	{
		if (!m_isFadingOut)
		{
			m_isFadingOut = true;
			m_nextScene = SceneType::Result;
		}
	}

	// プレイヤーがヒットストップ中（時が止まっている状態）は敵の動作更新を止める
	if (!m_player.IsHitStopped())
	{
		m_enemy.Update(m_player.GetX(), m_player.GetY(), 80.0f, m_player.IsAttacking());
	}

	// 敵撃破判定 -> リザルト画面へ遷移
	if (m_enemy.IsDeadFinished())
	{
		return SceneType::Result;
	}

	// プレイヤーの攻撃 -> 敵へのヒット判定（ヒットストップ演出付き）
	if (!m_enemy.IsDead() && !m_playerHasHit && IsOverlap(m_player.GetAttackHitbox(), m_enemy.GetHitbox()))
	{
		float hitX = static_cast<float>(m_enemy.GetX());
		float hitY = static_cast<float>(m_enemy.GetY() - 20.0f);

		// ヒットストップ＆斬撃エフェクト呼び出し
		m_player.OnHitSuccess(hitX, hitY);
		m_enemy.OnDamage(10, 20);
		m_playerHasHit = true;
	}

	if (!m_player.IsAttacking())
	{
		m_playerHasHit = false;
	}

	// 敵の攻撃 -> プレイヤーへのヒット判定（パリィ・ガード・被弾）
	Hitbox enemyAtkBox = m_enemy.GetAttackHitbox();

	if (enemyAtkBox.isActive)
	{
		Hitbox playerBox;
		playerBox.x = m_player.GetX();
		playerBox.y = m_player.GetY();
		playerBox.width = 40.0f;
		playerBox.height = 80.0f;
		playerBox.isActive = true;

		if (IsOverlap(enemyAtkBox, playerBox))
		{
			// A. パリィ成功！
			if (m_player.IsParrying())
			{
				float hitX = (m_player.GetX() + enemyAtkBox.x) / 2.0f;
				float hitY = (m_player.GetY() + enemyAtkBox.y) / 2.0f;

				// パリィ時の画面揺れ＋ヒットストップ＋光彩エフェクト発動
				m_player.OnParrySuccess(hitX, hitY);
				m_enemy.OnParried();
			}
			// B. ガード成功
			else if (m_player.IsGuarding())
			{
				m_player.OnDamage(0, 15);
			}
			// C. 被弾（ノーガード）
			else
			{
				m_player.OnDamage(20, 30);
			}

			// 多段ヒット防止のため判定クリア
			m_enemy.ClearAttackHitbox();
		}
	}

	if (CheckHitKey(KEY_INPUT_X))
	{
		if (!m_isFadingOut)
		{
			m_isFadingOut = true;
			m_nextScene = SceneType::Result;
		}
	}

	return SceneType::Main;//通常時は自分のシーンを維持
}

void SceneMain::Draw()
{
	m_bg.Draw();
	m_player.Draw();
	m_enemy.Draw();

	// フェード用の黒い四角形を全画面にかぶせて描画
	if (m_fadeAlpha > 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
		DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void SceneMain::Release()
{
}
