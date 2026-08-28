#include "Bg.h"
#include "DxLib.h"
#include <cstdio>

namespace
{
	constexpr int kScale = 4;

	// 地面（表層）サイズ
	constexpr int kEarthTileWidth = 48;
	constexpr int kEarthTileHeight = 24;
	constexpr int kDrawWidth = kEarthTileWidth * kScale;   // 192px
	constexpr int kDrawHeight = kEarthTileHeight * kScale; // 96px

	// 土（地下）サイズ
	constexpr int kEarth2TileWidth = 48;
	constexpr int kEarth2TileHeight = 12;
	constexpr int kDraw2Width = kEarth2TileWidth * kScale;   // 192px
	constexpr int kDraw2Height = kEarth2TileHeight * kScale; // 48px

	// 表面地面のY座標
	constexpr int kEarthY = Game::kScreenHeight / 1.5;
}

Bg::Bg() :
	m_bgHandles{},
	m_earthHandle(-1),
	m_earth2Handle(-1),
	m_toriiHandle(-1),
	m_bambooHandle(-1)
{
}

Bg::~Bg()
{
}

void Bg::Init()
{
	char bgPath[64];
	for (int i = 0; i < 4; ++i)
	{
		sprintf_s(bgPath, "image/bg/%d.png", i + 1);
		m_bgHandles[i] = LoadGraph(bgPath);
	}

	m_earthHandle = LoadGraph("image/bg/earth.png");
	m_earth2Handle = LoadGraph("image/bg/earth2.png");
	m_toriiHandle = LoadGraph("image/bg/torii.png");
	m_bambooHandle = LoadGraph("image/bg/bamboo.png");
}

void Bg::End()
{
	for (int handle : m_bgHandles) DeleteGraph(handle);
	DeleteGraph(m_earthHandle);
	DeleteGraph(m_earth2Handle);
	DeleteGraph(m_toriiHandle);
	DeleteGraph(m_bambooHandle);
}

void Bg::Update()
{
}

void Bg::Draw()
{
	// 1. 遠景・背景（左右2画面分 × 4層）
	const int bgXPositions[] = {
		Game::kScreenWidth / 2 + Game::kScreenWidth / 4,
		Game::kScreenWidth / 4
	};

	for (int posX : bgXPositions)
	{
		for (int i = 3; i >= 0; --i)
		{
			DrawRectRotaGraph(posX, Game::kScreenHeight / 2.7, 0, 0, 320, 180, double(kScale), 0.0, m_bgHandles[i], true, false);
		}
	}

	// 2. 地面と土
	DrawGround();

	// 3. 竹・鳥居のオブジェクト
	DrawRectRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 3, 0, 0, 132, 120, double(kScale * 1.2), 0.0, m_bambooHandle, true, false);
	DrawRectRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2, 0, 0, 79, 70, double(kScale), 0.0, m_toriiHandle, true, false);
}

void Bg::DrawGround()
{
	// 表層（earth.png）
	for (int x = kDrawWidth / 2; x < Game::kScreenWidth + kDrawWidth; x += kDrawWidth)
	{
		DrawRectRotaGraph(x, kEarthY, 0, 0, kEarthTileWidth, kEarthTileHeight, double(kScale), 0.0, m_earthHandle, true, false);
	}

	// 地下（earth2.png）
	int startY = kEarthY + (kDrawHeight / 2) + (kDraw2Height / 2);
	for (int y = startY; y < Game::kScreenHeight + kDraw2Height; y += kDraw2Height)
	{
		for (int x = kDraw2Width / 2; x < Game::kScreenWidth + kDraw2Width; x += kDraw2Width)
		{
			DrawRectRotaGraph(x, y, 0, 0, kEarth2TileWidth, kEarth2TileHeight, double(kScale), 0.0, m_earth2Handle, true, false);
		}
	}
}