#include "SceneResult.h"
#include "DxLib.h"

namespace
{
	constexpr int kFadeSpeed = 5; // ピアノ曲に合わせてゆっくりフェード
}

SceneResult::SceneResult() :
	m_bgmHandle(-1),
	m_fadeAlpha(255),
	m_isFadingIn(true),
	m_isFadingOut(false),
	m_timer(0),
	m_particles{}
{
}

SceneResult::~SceneResult()
{
}

void SceneResult::Init()
{
	// 音源ファイルのロード（ファイル名に合わせて変更してください）
	m_bgmHandle = LoadSoundMem("sound/bgm_l.mp3");
	if (m_bgmHandle != -1)
	{
		ChangeVolumeSoundMem(0, m_bgmHandle);
		PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
	}

	m_fadeAlpha = 255;
	m_isFadingIn = true;
	m_isFadingOut = false;
	m_timer = 0;
	// パーティクルの初期化（画面全体にランダム配置）
	for (int i = 0; i < kParticleCount; ++i)
	{
		m_particles[i].x = static_cast<float>(rand() % Game::kScreenWidth);
		m_particles[i].y = static_cast<float>(rand() % Game::kScreenHeight);
		m_particles[i].speedY = 0.3f + (rand() % 100) / 100.0f; // 低速で上昇
		m_particles[i].alpha = static_cast<float>(50 + rand() % 150);
		m_particles[i].size = 2.0f + (rand() % 4);
	}
}

void SceneResult::End()
{
	if (m_bgmHandle != -1)
	{
		StopSoundMem(m_bgmHandle);
		DeleteSoundMem(m_bgmHandle);
		m_bgmHandle = -1;
	}
}

SceneType SceneResult::Update()
{
	m_timer++;

	// パーティクルの位置・アルファ更新
	for (int i = 0; i < kParticleCount; ++i)
	{
		m_particles[i].y -= m_particles[i].speedY;
		// 画面上に消えたら下からリスポーン
		if (m_particles[i].y < -10.0f)
		{
			m_particles[i].y = static_cast<float>(Game::kScreenHeight + 10);
			m_particles[i].x = static_cast<float>(rand() % Game::kScreenWidth);
		}
	}

	// フェードイン処理
	if (m_isFadingIn)
	{
		m_fadeAlpha -= kFadeSpeed;
		if (m_fadeAlpha <= 0)
		{
			m_fadeAlpha = 0;
			m_isFadingIn = false;
		}

		if (m_bgmHandle != -1)
		{
			ChangeVolumeSoundMem(255 - m_fadeAlpha, m_bgmHandle);
		}
	}

	// フェードアウト処理
	if (m_isFadingOut)
	{
		m_fadeAlpha += kFadeSpeed;
		if (m_fadeAlpha >= 255)
		{
			m_fadeAlpha = 255;
			return SceneType::Title; // 暗転完了後にタイトルへ戻る
		}

		if (m_bgmHandle != -1)
		{
			ChangeVolumeSoundMem(255 - m_fadeAlpha, m_bgmHandle);
		}

		return SceneType::Result;
	}

	// 入力判定（キーボード[R] / マウス左クリック / PS5決定ボタン）
	int mouseInput = GetMouseInput();
	int padInput = GetJoypadInputState(DX_INPUT_PAD1);

	// PAD_INPUT_1 (✕ボタン) または PAD_INPUT_2 (〇ボタン) のどちらでも反応するように設定
	bool isDecidePressed = (CheckHitKey(KEY_INPUT_R) != 0) ||
		((mouseInput & MOUSE_INPUT_LEFT) != 0) ||
		((padInput & PAD_INPUT_1) != 0) ||
		((padInput & PAD_INPUT_2) != 0);

	// タイトルに戻る
	if (isDecidePressed)
	{
		if (!m_isFadingOut)
		{
			m_isFadingOut = true;
		}
	}

	return SceneType::Result;
}

void SceneResult::Draw()
{
	// 背景描画
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(10, 12, 22), TRUE);

	// 舞い上がる光の粒子
	SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
	for (int i = 0; i < kParticleCount; ++i)
	{
		int alpha = static_cast<int>(m_particles[i].alpha);
		int size = static_cast<int>(m_particles[i].size);
		int px = static_cast<int>(m_particles[i].x);
		int py = static_cast<int>(m_particles[i].y);

		// 外側のぼやけた光と内側の明るい芯
		DrawCircle(px, py, size + 2, GetColor(150, 100, 30), TRUE);
		DrawCircle(px, py, size, GetColor(255, 220, 120), TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//  UIテキスト描画
	int centerX = Game::kScreenWidth / 2;

	// ステージクリアタイトル
	const char* titleStr = "--- STAGE CLEAR ---";
	int titleW = GetDrawStringWidth(titleStr, static_cast<int>(strlen(titleStr)));
	DrawString(centerX - titleW / 2, 80, titleStr, GetColor(255, 215, 0));

	// 評価＆称賛メッセージ
	if (m_timer > 30)
	{
		// 枠線つきのリザルトプレート
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
		DrawBox(centerX - 350, 140, centerX + 350, 390, GetColor(20, 25, 40), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawBox(centerX - 350, 140, centerX + 350, 390, GetColor(180, 150, 80), FALSE);

		// タイム表示
		SetFontSize(24);
		int minutes = s_clearTimeSeconds / 60;
		int seconds = s_clearTimeSeconds % 60;
		DrawFormatString(centerX - 100, 160, GetColor(220, 220, 220), "CLEAR TIME : %02d:%02d", minutes, seconds);

		// タイムに応じたランク判定＆色設定
		const char* rankStr = "C";
		unsigned int rankColor = GetColor(150, 150, 150); // 通常のグレー

		if (s_clearTimeSeconds <= 30)
		{
			rankStr = "S";
			rankColor = GetColor(255, 60, 90); // 豪華な赤/ピンク
		}
		else if (s_clearTimeSeconds <= 40)
		{
			rankStr = "A";
			rankColor = GetColor(255, 200, 50); // 金/オレンジ
		}
		else if (s_clearTimeSeconds <= 50)
		{
			rankStr = "B";
			rankColor = GetColor(100, 220, 100); // 緑
		}

		// 評価ランク
		SetFontSize(36);
		const char* rankLabel = "RANK : ";
		int rankW = GetDrawStringWidth(rankLabel, static_cast<int>(strlen(rankLabel)));
		DrawString(centerX - rankW - 10, 210, rankLabel, GetColor(200, 200, 200));

		SetFontSize(72);
		DrawString(centerX + 10, 200, "S", GetColor(255, 60, 90)); // 太文字風・大型ランク

		// 褒め言葉
		SetFontSize(28);
		const char* praiseStr = "EXCELLENT SWORDSMANSHIP!";
		int praiseW = GetDrawStringWidth(praiseStr, static_cast<int>(strlen(praiseStr)));
		DrawString(centerX - praiseW / 2, 310, praiseStr, GetColor(230, 230, 250));
	}

	// THANK YOU FOR PLAYING メッセージ
	if (m_timer > 60)
	{
		SetFontSize(36);
		const char* thanksStr = "THANK YOU FOR PLAYING!";
		int thanksW = GetDrawStringWidth(thanksStr, static_cast<int>(strlen(thanksStr)));
		DrawString(centerX - thanksW / 2, 440, thanksStr, GetColor(255, 225, 120));
	}

	// 点滅する操作ガイド（Rキー / ESCキー）
	if (m_timer > 90)
	{
		if ((m_timer / 30) % 2 == 0)
		{
			SetFontSize(22);
			const char* guideR = "[ LEFT CLICK / X Button ] : RETURN TO TITLE";
			const char* guideESC = "[ ESC ] : QUIT GAME";

			int rW = GetDrawStringWidth(guideR, static_cast<int>(strlen(guideR)));
			int escW = GetDrawStringWidth(guideESC, static_cast<int>(strlen(guideESC)));

			DrawString(centerX - rW / 2, 530, guideR, GetColor(120, 220, 255));
			//DrawString(centerX - escW / 2, 570, guideESC, GetColor(180, 180, 200));
		}
	}

	SetFontSize(16);

	// 暗転フェード用オーバーレイ
	if (m_fadeAlpha > 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
		DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}