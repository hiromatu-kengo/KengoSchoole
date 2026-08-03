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
}

void SceneMain::Update()
{
}

void SceneMain::Draw()
{
}

void SceneMain::Release()
{
}
