#include "SceneTitle.h"
#include"DxLib.h"

SceneTitle::SceneTitle()
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
}

void SceneTitle::End()
{
}

SceneType SceneTitle::Update()
{
	// Zキーが押されたらMainシーンに遷移する
	if (CheckHitKey(KEY_INPUT_Z))
	{
		return SceneType::Main;
	}
	return SceneType::Title;
}

void SceneTitle::Draw()
{
	DrawString(500, 300, "Title Scene", GetColor(255, 255, 255));
	DrawString(450, 360, "PRESS Z KEY TO START", GetColor(255, 255, 0));
}
