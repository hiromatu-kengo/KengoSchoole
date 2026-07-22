#include "SceneMain.h"
#include"DxLib.h"
#include"Game.h"
#include<numbers>

SceneMain::SceneMain() :
	m_frameCount(0),
	m_sawHandle(-1),
	m_sawAngle(0.0),
	m_playerHandle(-1),
	m_playerAngle(0.0)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	m_frameCount = 0;
	m_sawHandle = LoadGraph("saw.png");
	m_sawAngle = 0.0;
	m_playerHandle = LoadGraph("idle.png");
	m_playerAngle = 0.0;
}

void SceneMain::End()
{
	DeleteGraph(m_sawHandle);
	DeleteGraph(m_playerHandle);
}

void SceneMain::Update()
{
	m_frameCount++;
	m_sawAngle += 10.95;
	//m_playerAngle = -3.14 / 2;
	int angle = 270;
	//m_playerAngle = (DX_PI / 180) * angle;
	m_playerAngle = (std::numbers::pi / 180) * angle;

	//円周率はDxライブラリが定義してくれているのでそれを使う
	// 180°=πラジアン
	//DX_PI double型
	//DX_PI_F float型
	//DX_TWO_PI 2*π 360°= 2πラジアンなのでそこそこ使う
	//DX_TWO_PI_F DX_TWO_PIのfloat版
	//nmbersの中でも円周率が定義されている
	//使うときは#include<numbers>が必要
	//std::numbers::pi  double型
	//std::numbers::pi_v<float> float型
}

void SceneMain::Draw()
{
	//DrawGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2, m_sawHandle, true);

	//中央の座標を指定するので面中央の座を指定するといい感じに中央に表示される
	DrawRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2,
		1.0, m_sawAngle, m_sawHandle, true);

	//DrawGraph(480, 240, m_playerHandle, true);
	//DrawRectGraph(480, 240, 0, 0, 32, 32, m_playerHandle, true);

	DrawRectRotaGraph(480, 240, 0, 0, 32, 32, 1.0, m_playerAngle, m_playerHandle, true);

	//回転角度を指定するときは【度数法】ではなく【弧度法】を使用する
	DrawFormatString(480, 260, GetColor(255, 255, 255), "%.2f°", m_playerAngle);

	DrawString(0, 0, "SceneMain", GetColor(255, 255, 255));
	DrawFormatString(0, 16, GetColor(255, 255, 255), "FRAME:%d", m_frameCount);
}