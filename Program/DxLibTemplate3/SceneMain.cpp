#include "SceneMain.h"
#include"DxLib.h"
#include"Game.h"

SceneMain::SceneMain() :
	m_frameCount(0),
	m_alpha(0),
	m_alphaAcc(0),
	m_fadeAlpha(0),
	m_fadeAcc(0)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	m_frameCount = 0;
	m_alpha = 0;
	m_alphaAcc = 4;

	//フェードの初期化
	//最初は完全に不透明な資格が表示されている状態から始まる
	m_fadeAlpha = 255;
	m_fadeAcc = -8;
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
	m_frameCount++;

	m_fadeAlpha += m_fadeAcc;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
		m_fadeAcc = 0;
	}
	if (m_fadeAlpha > 255)
	{
		m_fadeAlpha = 255;
	}

	//上キーを押したらフェードアウト
	if (m_fadeAcc == 0)
	{
		if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)
		{
			m_fadeAcc = 8;
		}
	}

	//透明度を変化させる
	m_alpha += m_alphaAcc;
	if (m_alpha >= 255)
	{
		m_alpha = 255;
		m_alphaAcc = -4;
	}
	if (m_alpha <= 0)
	{
		m_alpha = 0;
		m_alphaAcc = 4;
	}
}

void SceneMain::Draw()
{
	DrawBox(0, 0, 320, 600, GetColor(128, 128, 0), true);

	//青の箱を半透明で表示する

	//第2引数が透明度
	//0：完全に透明　~ 255：完全に不透明

	//以降描画する物体すべてに適応される
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	DrawBox(160, 160, 480, 320, GetColor(0, 0, 255), true);

	//半透明で表示したい物体の表示が終わったら元の設定に戻しておく
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//半透明表示終わり


	DrawString(0, 0, "SceneMain", GetColor(255, 255, 255));
	DrawFormatString(0, 16, GetColor(255, 255, 255), "FRAME:%d", m_frameCount);
	
	//フェードに使用する画面全体を覆う黒の四角
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);//半透明表示終わり
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);//半透明表示終わり
}