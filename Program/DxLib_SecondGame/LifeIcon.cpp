#include "LifeIcon.h"
#include"DxLib.h"

namespace
{
	//画像のサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	//表示スケール
	constexpr double kScaleMax = 2.0;
	constexpr int kScaleFrame = 16;//スケーリング

	//アニメーション
	constexpr int kAnimNum = 17;
	constexpr int kSingleAnimFrame = 2; // frames per sprite
	constexpr int kTotalAnimFrame = kAnimNum * kSingleAnimFrame;
}

LifeIcon::LifeIcon():
	m_graphHandle(-1),
	m_animFrame(0),
	m_scale(0.0),
	m_isActive(true),
	m_isVisible(true)
{
}

LifeIcon::~LifeIcon()
{
}

void LifeIcon::Init()
{
	m_isActive = true;
	m_isVisible = true;
}

void LifeIcon::End()
{
}

void LifeIcon::Update()
{
	m_animFrame++;

	if (m_isActive)
	{
		//だんだん大きくなる
		m_scale += kScaleMax / kScaleFrame;
		if (m_scale >= kScaleMax)m_scale = kScaleMax;
	}
	else
	{
		//だんだん小さくなる
		m_scale -= kScaleMax / kScaleFrame;
		if (m_scale < 0.0)
		{
			m_scale = 0.0;
			m_isVisible = false;//完全に非表示
		}
	}
}

void LifeIcon::Draw()
{
	//表示するかチェック
	//m_isVisibleがfalseなら何もせずに終了
	if (!m_isVisible) return;//早期リターン

	//何コマ目を表示するか計算で求める
	int animNo = (m_animFrame % kTotalAnimFrame) / kSingleAnimFrame;



	//DrawRectGraph(m_pos.x, m_pos.y, animNo * kWidth, 0, kWidth, kHeight, m_graphHandle, true);
	DrawRectRotaGraph(m_pos.x, m_pos.y, animNo * kWidth, 0, kWidth, kHeight, 2.0, 0.0, m_graphHandle, true);
}
