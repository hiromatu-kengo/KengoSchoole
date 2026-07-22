#include "Bg.h"
#include "DxLib.h"
#include "Game.h"
Bg::Bg()
{
}

Bg::~Bg()
{
}

void Bg::Init()
{
}

void Bg::End()
{
}

void Bg::Update()
{
}

void Bg::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(111, 141, 66), true);
}
