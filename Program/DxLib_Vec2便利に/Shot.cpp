#include "Shot.h"
#include"DxLib.h"

Shot::Shot() :
	m_graphHandle(-1),
	m_pos(0.0f, 0.0f),
	m_vec(0.0f, 0.0f)
{
}

Shot::~Shot()
{
}

void Shot::Init()
{
	//初期位置
	m_pos.x = 64.0f;
	m_pos.y = 64.0f;

	//移動方向
	m_vec.x = 4.0f;
	m_vec.y = 0.0f;
}

void Shot::End()
{
}

void Shot::Update()
{
	m_pos.x += m_vec.x;
	m_pos.y += m_vec.y;
}

void Shot::Draw()
{
	//	DrawGraph(m_pos.x, m_pos.y, m_graphHandle, true);

	DrawRotaGraph(m_pos.x, m_pos.y,
		3.0, 0.0,
		m_graphHandle, true);
}
