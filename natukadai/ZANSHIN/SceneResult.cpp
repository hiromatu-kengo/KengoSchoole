#include "SceneResult.h"
#include"DxLib.h"

SceneResult::SceneResult()
{
}

SceneResult::~SceneResult()
{
}

void SceneResult::Init()
{
}

void SceneResult::End()
{
}

SceneType SceneResult::Update()
{
	if (CheckHitKey(KEY_INPUT_R))
	{
		return SceneType::Title;

	}
		return SceneType::Result;
}

void SceneResult::Draw()
{
	DrawString(500, 300, "Result Scene", GetColor(255, 255, 255));
	DrawString(450, 360, "PRESS R KEY TO RETURN TO TITLE", GetColor(0, 255, 255));
}
