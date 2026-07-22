#include "Player.h"
#include"DxLib.h"

namespace
{
	constexpr int kStartX = 300;
	constexpr int kStartY = 300;

	constexpr int kRadius = 16;
	constexpr int kSpeed = 4;
}

Player::Player() :
	m_x(0),
	m_y(0)
{
}

Player::~Player()
{
}

void Player::Init()
{
	m_x = kStartX;
	m_y = kStartY;
}

void Player::End()
{
}

void Player::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//コントローラーを使ってプレイヤーを動かす
	if (pad & PAD_INPUT_UP)
	{
		m_y -= kSpeed;
	}
	if (pad & PAD_INPUT_DOWN)
	{
		m_y += kSpeed;
	}
	if (pad & PAD_INPUT_LEFT)
	{
		m_x -= kSpeed;
	}
	if (pad & PAD_INPUT_RIGHT)
	{
		m_x += kSpeed;
	}
}

void Player::Draw()
{
	DrawCircle(m_x, m_y, kRadius, GetColor(255, 255, 255), true);

}

int Player::GetRadius()const
{
	return kRadius;
}
