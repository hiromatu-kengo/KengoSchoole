#include "Player.h"
#include "DxLib.h"
#include "Game.h"


//定数定義
namespace
{
	//グラフィックの切り取りサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	//アニメーションの関連の定義
	constexpr int kIdleAnimNum = 11;	//待機アニメーションのコマ数
	constexpr int kRunAnimNum = 12;		//移動アニメーションのコマ数

	constexpr int kSingleAnimFrame = 4;	//アニメ1コマに書けるフレーム数

	//アニメーション1ループにかかるフレーム数
	constexpr int kIdleAnimTotalFrame = kIdleAnimNum * kSingleAnimFrame;
	constexpr int kRunAnimTotalFrame = kRunAnimNum * kSingleAnimFrame;

	//プレイヤーの初期位置
	constexpr float kStartX = Game::kScreenWidth / 2 - kWidth / 2;
	constexpr float kStartY = Game::kScreenHeight / 2 - kHeight / 2;

	//プレイヤーの速度
	constexpr float kSpeed = 4.0f;

	//当たり判定の半径
	constexpr float kColRadius = 12.0f;

}
Player::Player() :
	m_idleGraph(-1),
	m_runGraph(-1),
	m_x(0.0f),
	m_y(0.0f),
	m_animFrame(0),
	m_isFrip(false),
	m_isMoving(false),
	m_isDead(false)
{
}

Player::~Player()
{
}

void Player::Init()
{
	//リソースのロードはSceneに任せる
	//グラフィックのロード
//	m_idleGraph = LoadGraph("image/idle.png");
//	m_runGraph = LoadGraph("image/run.png");

	//プレイヤーの初期位置を設定
	constexpr float kStartX = 200;
	constexpr float kStartY = Game::kScreenHeight / 2 - kHeight / 2;
	m_x = kStartX;
	m_y = kStartY;

	m_animFrame = 0;
	//プレイヤーの速度
	constexpr float kSpeed = 6.0f;
	//当たり判定の半径
	constexpr float kColRadius = 12.0f;
	m_isDead = false;

}

void Player::End()
{
	//グラフィックをメモリから開放
	DeleteGraph(m_idleGraph);
	DeleteGraph(m_runGraph);

}

void Player::Update()
{
	//アニメーションを進める
	m_animFrame++;

	//いったん動いていない扱いにする
	m_isMoving = false;

	if (!m_isDead)
	{
		//コントローラーでキャラクターを移動させる
		int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if (pad & PAD_INPUT_UP)
		{
			m_y -= kSpeed;
			m_isMoving = true;
		}
		if (pad & PAD_INPUT_DOWN)
		{
			m_y += kSpeed;
			m_isMoving = true;
		}
		if (pad & PAD_INPUT_LEFT)
		{
			m_x -= kSpeed;
			m_isMoving = true;
			m_isFrip = true;
		}
		if (pad & PAD_INPUT_RIGHT)
		{
			m_x += kSpeed;
			m_isMoving = true;
			m_isFrip = false;
		}

		//画面外に出られないようにする
		if (m_y < 0.0f)
		{
			m_y = 0.0f;
		}
		if (m_x < 0.0f)
		{
			m_x = 0.0f;
		}
		if (m_y > Game::kScreenHeight - kHeight)
		{
			m_y = Game::kScreenHeight - kHeight;
		}
		if (m_x > Game::kScreenWidth - kWidth)
		{
			m_x = Game::kScreenWidth - kWidth;
		}
	}
}
void Player::Draw()
{
	//移動中かどうかでアニメーションを変更する
	int tempTotalFrame = kIdleAnimTotalFrame;
	int tempHanndle = m_idleGraph;
	if (m_isMoving)
	{
		tempTotalFrame = kRunAnimTotalFrame;
		tempHanndle = m_runGraph;
	}

	//現在のフレーム数から表示したいコマ番号を計算で求める
	int animNo = (m_animFrame % kIdleAnimTotalFrame) / kSingleAnimFrame;

	if (m_isDead)
	{
		SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
	}
	DrawRectGraph(m_x, m_y,
		animNo * kWidth, 0, kWidth, kHeight,
		m_idleGraph, true,
		m_isFrip);	//左右反転フラグ
#ifdef _DEBUG
	//当たり判定のデバッグ表示
	DrawCircle(GetColCenterX(), GetColCenterY(), GetRadius(), GetColor(255, 0, 0), false);
#endif
}

float Player::GetColCenterX() const
{
	return m_x + kWidth / 2;
}

float Player::GetColCenterY() const
{
	return m_y + kHeight / 2;
}

float Player::GetRadius() const
{
	return kColRadius;
}

void Player::OnDead()
{
	m_isDead = true;
}
