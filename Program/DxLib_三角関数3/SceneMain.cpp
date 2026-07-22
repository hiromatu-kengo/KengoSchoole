#include "SceneMain.h"
#include"DxLib.h"
#include"Game.h"

SceneMain::SceneMain() :
	m_frameCount(0)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	m_frameCount = 0;

	m_center.x = Game::kScreenWidth / 2;
	m_center.y = Game::kScreenHeight / 2;
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
	m_frameCount++;
}

void SceneMain::Draw()
{
	DrawCircle(m_center.x, m_center.y, 8, GetColor(255, 0, 0), true);

	DrawString(0, 0, "SceneMain", GetColor(255, 255, 255));
	DrawFormatString(0, 16, GetColor(255, 255, 255), "FRAME:%d", m_frameCount);
}