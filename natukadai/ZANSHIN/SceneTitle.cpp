#include "SceneTitle.h"
#include"DxLib.h"

SceneTitle::SceneTitle():
	m_bgmHandle(-1),
	m_titleGraph(-1),
	m_isFadingOut(false),
	m_bgmVolume(255),
	m_fadeSpeed(5),
	m_blinkTimer(0)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	m_bgmHandle = LoadSoundMem("sound/bgm_s.mp3");

	m_isFadingOut = false;
	m_bgmVolume = 255; // 音量を初期化

	if (m_bgmHandle != -1)
	{
		// ループ再生を指定
		PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
		ChangeVolumeSoundMem(m_bgmVolume, m_bgmHandle); // 最大音量に設定
	}

	// タイトル画像の読み込み（格納場所に併せてパスを変更してください）
	m_titleGraph = LoadGraph("image/bg/Title.png");
}

void SceneTitle::End()
{
	if (m_bgmHandle != -1)
	{
		StopSoundMem(m_bgmHandle); // 再生停止
		DeleteSoundMem(m_bgmHandle); // メモリ解放
		m_bgmHandle = -1;
	}

	// タイトル画像の破棄
	if (m_titleGraph != -1)
	{
		DeleteGraph(m_titleGraph);
		m_titleGraph = -1;
	}
}

SceneType SceneTitle::Update()
{
	// 点滅用タイマーを毎フレーム加算
	m_blinkTimer++;

	// 入力判定（キーボード[Z] / マウス左クリック / PS5決定ボタン）
	int mouseInput = GetMouseInput();
	int padInput = GetJoypadInputState(DX_INPUT_PAD1);

	// PAD_INPUT_1 (✕ボタン) または PAD_INPUT_2 (〇ボタン) のどちらでも反応するように設定
	bool isDecidePressed = (CheckHitKey(KEY_INPUT_Z) != 0) ||
		((mouseInput & MOUSE_INPUT_LEFT) != 0) ||
		((padInput & PAD_INPUT_1) != 0) ||
		((padInput & PAD_INPUT_2) != 0);

	// ボタン:キーが押されたらフェードアウトを開始する
	if (isDecidePressed && !m_isFadingOut)
	{
		m_isFadingOut = true;
	}

	// フェードアウト処理
	if (m_isFadingOut)
	{
		m_bgmVolume -= m_fadeSpeed; // 音量を減算

		if (m_bgmVolume <= 0)
		{
			m_bgmVolume = 0;
			ChangeVolumeSoundMem(m_bgmVolume, m_bgmHandle);

			End(); // BGMを停止・破棄
			return SceneType::Main; // 音量が0になったらシーン切替
		}

		// 音量を適用
		ChangeVolumeSoundMem(m_bgmVolume, m_bgmHandle);
	}

	return SceneType::Title;
}

void SceneTitle::Draw()
{
	// タイトルロゴ描画
	if (m_titleGraph != -1)
	{
		DrawRotaGraph(Game::kScreenWidth / 2, 420, 0.85, 0.0, m_titleGraph, TRUE);
	}
	else
	{
		DrawString(Game::kScreenWidth / 2 - 150, 420, "ERROR: Title.png NOT FOUND", GetColor(255, 50, 50));
	}

	// フォントサイズを大きく変更
	SetFontSize(36);

	int textY = 820;

	// 文字の後ろに「半透明の黒帯」を描画して視認性と重厚感をアップ
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 140);
	DrawBox(0, textY - 15, Game::kScreenWidth, textY + 55, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (m_isFadingOut)
	{
		// 決定後は素早く点滅させる（LOAD...表記）
		if ((m_blinkTimer / 5) % 2 == 0)
		{
			int textWidth = GetDrawStringWidth("NOW LOADING...", -1);
			DrawString(Game::kScreenWidth / 2 - textWidth / 2, textY, "NOW LOADING...", GetColor(255, 200, 50));
		}
	}
	else
	{
		// sin関数で「ふわっと消えて広がる」ようなアルファ点滅を計算（アルファ値 60〜255）
		int alpha = static_cast<int>(157.5f + 97.5f * std::sin(m_blinkTimer * 0.06f));

		// 文字幅を自動計算して完全に画面中央へ配置
		const char* msg = "[ LEFT CLICK / X Button ] : START";
		int textWidth = GetDrawStringWidth(msg, -1);
		int textX = Game::kScreenWidth / 2 - textWidth / 2;

		// アルファ描画を適用して文字を表示
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawString(textX, textY, msg, GetColor(255, 230, 150));
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// 終わったらフォントサイズを元の標準に戻しておく
	SetFontSize(16);
}
