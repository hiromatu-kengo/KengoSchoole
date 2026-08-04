#include "Player.h"
#include "DxLib.h"
#include "Game.h"

Player::Player() :
	m_idleGraph(-1),
	m_x(0),
	m_y(0),
	m_width(0),
	m_height(0)
{
}

Player::~Player()
{
}

void Player::Init()
{
	// グラフィックが有効ならサイズを取得して左半分の中央に配置
	if (m_idleGraph >= 0)
	{
		GetGraphSize(m_idleGraph, &m_width, &m_height);
	}
	else
	{
		m_width = 0;
		m_height = 0;
	}

	// 左半分の中央を基準に中央寄せ
	m_x = (Game::kScreenWidth / 4) - (m_width / 2);
	m_y = (Game::kScreenHeight / 2) - (m_height / 2);
}

void Player::Update()
{
}

void Player::Draw()
{
	if (m_idleGraph >= 0)
	{
		DrawGraph(m_x, m_y, m_idleGraph, TRUE);
	}
}

void Player::Release()
{
}
