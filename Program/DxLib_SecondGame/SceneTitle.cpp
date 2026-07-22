#include "SceneTitle.h"
#include"DxLib.h"
#include"Game.h"
#include<cmath>

namespace
{
	constexpr int kFadeFrame = 30;
	
	constexpr int kKeyInputWaitFrame = 60;
}

SceneTitle::SceneTitle() :
	m_frameCount(0),
	m_logoHandle(-1),
	m_fontHandle(-1),
	m_sinAngle(0.0f),
	m_fadeFrame(0),
	m_fadeSpeed(0),
	m_isEnd(false)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	m_logoHandle = LoadGraph("data/image/title.png");
	//フォントの作成
	// 第3,4引数は太さ・タイプ。-1 を渡してデフォルトにする
	m_fontHandle = CreateFontToHandle("ShowCard Gothic", 48, -1, -1);

	m_fadeFrame = kFadeFrame;
	m_fadeSpeed = -1;
	m_frameCount = 0;
	m_isEnd = false;
}

void SceneTitle::End()
{
	//メモリからグラフィックを削除
	DeleteGraph(m_logoHandle);
	// フォントは DeleteFontToHandle で解放する
	DeleteFontToHandle(m_fontHandle);
}

void SceneTitle::Update()
{
	m_frameCount++;

	m_fadeFrame += m_fadeSpeed;
	if (m_fadeFrame < 0) m_fadeFrame = 0;
	if (m_fadeFrame > kFadeFrame)
	{
		m_fadeFrame = kFadeFrame;
		m_isEnd = true;
	}

	if (m_frameCount >= kKeyInputWaitFrame)
	{
		// フェード用の角度を進める
		m_sinAngle += 0.05f;
		int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if (pad & PAD_INPUT_1)
		{
			//フェードアウトを開始
			m_fadeSpeed = +1;

			//フェードアウトが終わったらシーンを終了するよう変更

			//	printfDx("ゲーム開始!\n");
				//タイトル画面を終了してゲームへ
			//m_isEnd = true;
		}
	}

	
}

void SceneTitle::Draw()
{
	// 背景は黒にして文字が見えるようにする
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(255, 255, 255), true);

		DrawGraph(50, 60, m_logoHandle, true);

	//30フレームごとに表示非表示を切り替える
	//int tempFrame = m_frameCount % 60;//0~59
	//if (tempFrame < 30)
	//{
	//	//ボタンを押してください表示
	//	int width = GetDrawStringWidthToHandle("PRESS ANY BUTTON!", strlen("PRESS ANY BUTTON!"), m_fontHandle);
	//	DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, 340, "PRESS ANY BUTTON!", GetColor(255, 255, 255), m_fontHandle);
	//}

	//sinカーブを使って透明度を変化させる
	float sinRate = sinf(m_sinAngle);//-1.0~1.0
	sinRate /= 2.0f;//-0.5~0.5
	sinRate += 0.5f;
	int alpha = static_cast<int>(255 * sinRate);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	if(m_frameCount >= kKeyInputWaitFrame)//キー入力できない間は表示しない
	{
		//ボタンを押してください表示
		int width = GetDrawStringWidthToHandle("PRESS ANY BUTTON!", strlen("PRESS ANY BUTTON!"), m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, 340, "PRESS ANY BUTTON!", GetColor(0, 191, 255), m_fontHandle);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フェード
	float frameRate = static_cast<float>(m_fadeFrame) / static_cast<float>(kFadeFrame);//浮動小数の計算にするためキャスト
	//0.0~1.0の割合を0~255の値に変換する
	alpha = static_cast<int>(255 * frameRate);
	//半透明ので表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(0, 0, 0), true);
	//半透明を終了
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString(0, 0, "SceneTitle", GetColor(255, 255, 255));
	DrawFormatString(0, 16, GetColor(255, 255, 255), "FRAME:%d", m_frameCount);
}
