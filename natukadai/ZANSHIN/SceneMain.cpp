#include "SceneMain.h"
#include"DxLib.h"

SceneMain::SceneMain():
	m_playerIdleHandle(-1)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{//シーン内で使用するリソースのロード
	m_playerIdleHandle = LoadGraph("image/player/IDLE.png");

	m_player.SetIdleGraph(m_playerIdleHandle);
}

void SceneMain::End()
{
	//シーンで使用したリソースをメモリから削除
	DeleteGraph(m_playerIdleHandle);
}

void SceneMain::Update()
{
}

void SceneMain::Draw()
{
	m_player.Draw();

}

void SceneMain::Release()
{
}
