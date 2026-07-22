#include "SceneMain.h"
#include"DxLib.h"

SceneMain::SceneMain() :
	m_frameCount(0),
	m_arrowHandle(-1)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	m_frameCount = 0;
	m_arrowHandle = LoadGraph("arrow.png");
}

void SceneMain::End()
{
	DeleteGraph(m_arrowHandle);
}

void SceneMain::Update()
{
	m_frameCount++;
}

void SceneMain::Draw()
{
	//プログラムで角度を指定する際は
	//度数法(Degree)ではなく
	//弧度法(Radian)を使用する

	//180°=π(3.14...)ラジアン
	//1° = π/180 rad
	//n° = n*π/180 rad

	DrawRotaGraph(100, 100,
		//1.0, -90, 度数法なのでミス
		3.0,-90 * DX_PI / 180,
		m_arrowHandle, true);

	constexpr int kNum = 16;
	for (int i = 0;i < kNum; i++)
	{
		double angle = DX_TWO_PI / kNum * i;
		DrawRotaGraph(160+48*i, 64,
			3.0, angle,
			m_arrowHandle, true);
		DrawFormatString(160 - 16 + 48 * i, 64 + 24, GetColor(255, 255, 255), "%.1f", angle);
	}
	

	DrawString(0, 0, "SceneMain", GetColor(255, 255, 255));
	DrawFormatString(0, 16, GetColor(255, 255, 255), "FRAME:%d", m_frameCount);
}