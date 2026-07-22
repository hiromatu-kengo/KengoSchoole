#include "Object.h"
#include"DxLib.h"

Object::Object():
	m_x(0.0f),
	m_y(0.0f),
	m_vecX(0.0f),
	m_vecY(0.0f)
{
}

Object::~Object()
{
}

void Object::Init()
{
	m_x = 512.0f;
	m_y = 256.0f;
}

void Object::End()
{
}

void Object::Update()
{
}

void Object::Draw()
{
	DrawCircle(m_x, m_y, 8, GetColor(255, 255, 0), true);
}
#include "Object.h"
#include"DxLib.h"

Object::Object():
	m_x(0.0f),
	m_y(0.0f),
	m_vecX(0.0f),
	m_vecY(0.0f)
{
}

Object::~Object()
{
}

void Object::Init()
{
	m_x = 512.0f;
	m_y = 256.0f;

	//1fあたりの移動速度を設定する
	m_vecX = 4.0f;
	m_vecY = 4.0f;
	//速度は大体5.64
	//これを速度4にしたい

	//計算を簡単にするためにいったん速度を1にする
	//ベクトルの大きさを1にする処理のことを【正規化】と呼ぶ

	//ベクトルを長さで割ることでいったん大きさを1にする(正規化)
	m_vecX = 4.0f / 5.6f;
	m_vecY = 4.0f / 5.64f;

	//長さ1のベクトルを4にするためのベクトルを4倍する
	m_vecX = m_vecX * 4.0f;
	m_vecY = m_vecY * 4.0f;
}

void Object::End()
{
}

void Object::Update()
{
	m_x += m_vecX;
	m_y += m_vecY;
}

void Object::Draw()
{
	DrawCircle(m_x, m_y, 8, GetColor(255, 255, 0), true);
}
