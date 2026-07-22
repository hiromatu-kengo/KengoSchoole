#include "SceneMain.h"
#include"DxLib.h"
#include<cmath>

SceneMain::SceneMain() :
	m_frameCount(0),
	m_shotGraphHandle(-1)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	m_shotGraphHandle = LoadGraph("data/arrow.png");

	m_frameCount = 0;
	for (int i = 0;i < kShotNum;i++)
	{
		m_shot[i].SetHandle(m_shotGraphHandle);
		m_shot[i].Init();
	}
}


void SceneMain::End()
{
	for (int i = 0;i < kShotNum;i++)
	{
		m_shot[i].End();
	}


	DeleteGraph(m_shotGraphHandle);
}

void SceneMain::Update()
{
	m_frameCount++;
	for (int i = 0;i < kShotNum;i++)
	{
		m_shot[i].Update();
	}
	if (GetMouseInput() & MOUSE_INPUT_LEFT)
	{
		//各玉の移動方向を設定する
		//[0]真右
		Vec2 right = { 4.0f,0.0f };
		m_shot[0].SetVec(right);
		//[1]真下
		Vec2 down = { 0.0f,4.0f };
		m_shot[1].SetVec(down);
		//[2]右下
		Vec2 rd = { 4.0f,4.0f };
		//ベクトルrdの長さを4にしたい

		//最初にベクトルrdの長さを１にする【正規化】
		rd.Normalize();

		//ベクトルの長さで割る
		//rd.x /= length;
		//rd.y /= length;
		//rdの大きさが１になった

		//目標の長さでかけてやる
		rd.x *= 4.0f;
		rd.y *= 4.0f;

		m_shot[2].SetVec(rd);
	}
}

void SceneMain::Draw()
{
	for (int i = 0;i < kShotNum;i++)
	{
		m_shot[i].Draw();
	}
	DrawString(0, 0, "SceneMain", GetColor(255, 255, 255));
	DrawFormatString(0, 16, GetColor(255, 255, 255), "FRAME:%d", m_frameCount);
}