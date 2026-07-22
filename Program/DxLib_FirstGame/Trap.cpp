#include "Trap.h"
#include"DxLib.h"
#include<cmath>
#include"Game.h"

namespace
{
	//移動開始までの待ち時間
	constexpr int kStartWaitFrame = 180;

	//初期位置
	constexpr float kStartX = 440;
	constexpr float kStartY = Game::kScreenDepth / 2;

	//のこぎりの回転速度
	constexpr double kRotSpeed = -10.8;

	//のこぎりの移動速度
	constexpr float kSpeed = 0.5f;

	//当たり判定の半径
	constexpr float kColRadius = 16.0f;
}

Trap::Trap() :
	m_graphHandle(-1),
	m_waitFrame(0),
	m_x(0),
	m_y(0),
	m_vecX(0),
	m_vecY(0),
	m_angle(0.0)
{
}

Trap::~Trap()
{
}

void Trap::Init()
{
	//開始待ちフレーム数を設定
	m_waitFrame = kStartWaitFrame;

	m_x = kStartX;
	m_y = kStartY;

	//進行方向を決定

	//ランダムな角度を生成する
	float angle = (DX_TWO_PI_F / 65536) * GetRand(65536 - 1);
	m_vecX = cosf(angle) * kSpeed;
	m_vecY = sinf(angle) * kSpeed;

	m_angle = 0.0;
}

void Trap::End()
{
}

void Trap::Update()
{
	//開始待ち状態でも行う処理
	m_angle -= kRotSpeed;

	//待ち時間カウントダウン
	m_waitFrame--;
	if (m_waitFrame > 0) return;

	//以降は待ち時間の間は処理しない

	m_x += m_vecX;
	m_y += m_vecY;

	//画面橋で反射
	if (m_x < 0.0f)
	{
		m_x = 0.0f;
		m_vecX *= -1.0f;
	}
	if (m_x > Game::kScreenWidth)
	{
		m_x = Game::kScreenWidth;
		m_vecX *= -1.0f;
	}
	if (m_y < 0.0f)
	{
		m_y = 0.0f;
		m_vecY *= -1.0f;
	}
	if (m_y > Game::kScreenHeight)
	{
		m_y = Game::kScreenHeight;
		m_vecY *= -1.0f;
	}

}

void Trap::Draw()
{
	//	DrawGraph(m_x, m_y, m_graphHandle, true);
	DrawRotaGraph(m_x, m_y, 1.0, m_angle, m_graphHandle, true);
#ifdef _DEBUG
	//当たり判定のデバッグ表示
	DrawCircle(GetColCenterX(), GetColCenterY(), GetRadius(), GetColor(0, 0, 255), false);
#endif
}

float Trap::GetColCenterX() const
{
	return m_x;
}

float Trap::GetColCenterY() const
{
	return m_y;
}

float Trap::GetRadius() const
{
	return kColRadius;
}
