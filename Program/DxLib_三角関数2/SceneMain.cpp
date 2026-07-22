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
		/*
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
		float sqLen = (rd.x * rd.x) + (rd.y * rd.y);
		float length = sqrtf(sqLen);

		//ベクトルの長さで割る
		rd.x /= length;
		rd.y /= length;
		//rdの大きさが１になった

		//目標の長さでかけてやる
		rd.x *= 4.0f;
		rd.y *= 4.0f;

		m_shot[2].SetVec(rd);
		*/
		for (int i = 0;i < kShotNum;i++)
		{
			float angle = (DX_TWO_PI_F / kShotNum) * i;
			/*
			Vec2 vec;
			vec.x = cosf(angle) * 4.0f;
			vec.y = sinf(angle) * 4.0f;
			*/
			m_shot[i].Shoot(angle, 4.0f);
		}
		/*
		{
			//マウスの座標を取得
			int mouseX = GetMouseX();
			int mouseY = GetMouseY();
			//各玉の移動方向を設定する
			Vec2 vec;
			vec.x = (float)mouseX - m_shot[i].GetPos().x;
			vec.y = (float)mouseY - m_shot[i].GetPos().y;
			//ベクトルvecの長さを4にしたい
			//最初にベクトルvecの長さを１にする【正規化】
			float sqLen = (vec.x * vec.x) + (vec.y * vec.y);
			float length = sqrtf(sqLen);
			//ベクトルの長さで割る
			vec.x /= length;
			vec.y /= length;
			//vecの大きさが１になった
			//目標の長さでかけてやる
			vec.x *= 4.0f;
			vec.y *= 4.0f;
			m_shot[i].SetVec(vec);
		}
		*/
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