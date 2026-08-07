#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include <cstring>

namespace
{
	constexpr int kWidth = 96;	                                        //1コマの幅
	constexpr int kHeight = 96;                         	            //1コマの高さ
    //アニメーションの関連の定義
    constexpr int kIdleAnimNum = 10;	                                //待機アニメーションのコマ数
	constexpr int kRunAnimNum = 16;	                                        //走るアニメーションのコマ数

    constexpr int kSingleAnimFrame = 4;	                                //アニメ1コマに書けるフレーム数

    //アニメーション1ループにかかるフレーム数
	constexpr int kIdleAnimTotalFrame = kIdleAnimNum * kSingleAnimFrame;//待機アニメーションの1ループにかかるフレーム数
	constexpr int kRunAnimTotalFrame = kRunAnimNum * kSingleAnimFrame;  //走るアニメーションの1ループにかかるフレーム数
	constexpr int kMoveSpeed = 10;                                       // 移動速度
	constexpr int kMaxFrames = 10;                                      // 最大フレーム数
	constexpr int kGravity = 2;                                         // 重力加速度
	constexpr int kJumpPower = 40;                                      // ジャンプ初速
	constexpr int kGroundY = Game::kScreenHeight / 2 - kHeight / 2;     // 地面のY座標（仮定）
	constexpr float kStartX = 200;                                      // プレイヤーの初期X座標
	constexpr float kStartY = Game::kScreenHeight / 2 - kHeight / 2;    // プレイヤーの初期Y座標
}

Player::Player() :
    m_frameIndex(0),
    m_animFrame(0),
    m_idleGraph(-1),
	m_runGraph(-1),
    m_graphCount(0),
    m_x(0),
    m_y(0),
    m_width(0),
    m_height(0),
    m_isFlip(false),
    m_isMoving(false)
{
    // initialize handles array to -1
    for (int i = 0; i < 10; ++i) m_playerGHandle[i] = -1;
}

Player::~Player()
{
}

void Player::Init()
{
    m_x = kStartX;
    m_y = kStartY;

    m_animFrame = 0;
}

void Player::End()
{
	DeleteGraph(m_idleGraph);
    DeleteGraph(m_runGraph);
}

void Player::Update()
{
    //アニメーションを進める
    m_animFrame++;
	m_isMoving = false; // 移動中フラグをリセット
	if (CheckHitKey(KEY_INPUT_D))
	{
		m_x += kMoveSpeed; // 右移動
		m_isFlip = false; // 右向き
		m_isMoving = true; // 移動中フラグをセット
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		m_x -= kMoveSpeed; // 左移動
		m_isFlip = true; // 左向き 
		m_isMoving = true; // 移動中フラグをセット
	}

    // ジャンプ開始（地面にいるときスペースでジャンプ）
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        if (m_isOnGround)
        {
            m_vy = -kJumpPower; // 初速（上方向に負）
            m_isOnGround = false;
        }
    }

    // 重力と垂直移動の適用
    if (!m_isOnGround)
    {
        m_vy += kGravity; // 下向きに加速
        m_y += m_vy;
        int groundY = kGroundY;
        if (m_y >= groundY)
        {
            m_y = groundY;
            m_vy = 0;
            m_isOnGround = true;
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
    int animNo = (m_animFrame % tempTotalFrame) / kSingleAnimFrame;
	DrawRectRotaGraph(m_x, m_y,                 //描画位置
		animNo * kWidth, 0,                     //描画元の矩形の左上座標
		kWidth, kHeight,                        //描画元の矩形の幅と高さ
		double(4.0), 0.0,                       //拡大率と回転角度
		tempHanndle, true,                      //描画するグラフィックハンドル
        m_isFlip);	                            //左右反転フラグ
}

void Player::Release()
{
}
