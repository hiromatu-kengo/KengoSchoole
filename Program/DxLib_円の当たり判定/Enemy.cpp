#include "Enemy.h"
#include"DxLib.h"
#include"Game.h"

Enemy::Enemy() :
	m_x(0),
	m_y(0),
	m_radius(0)
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	m_x = GetRand(Game::kScreenWidth);
	m_y = GetRand(Game::kScreenHeight);
	m_radius = GetRand(64) + 32;
}

void Enemy::End()
{
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	DrawCircle(m_x, m_y, m_radius, GetColor(233, 15, 148), true);
}

void Enemy::OnCollision()
{
	m_radius -= 2;
	if (m_radius < 0)
	{
		m_radius = 0;
	}
}