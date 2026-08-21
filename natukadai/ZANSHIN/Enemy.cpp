#include "Enemy.h"
#include "DxLib.h"
#include "Game.h"
#include <cmath>

namespace
{
	constexpr int kWidth = 128;	                                            //1コマの幅
	constexpr int kHeight = 128;                         	                //1コマの高さ
	//アニメーションの関連の定義
	constexpr int kIdleAnimNum = 6;	                                    //待機アニメーションのコマ数
	constexpr int kRunAnimNum = 8;	                                        //走るアニメーションのコマ数
	constexpr int kAttackAnimNum = 24;	                                    //攻撃アニメーションのコマ数

	constexpr int kSingleAnimFrame = 4;	                                    //アニメ1コマに書けるフレーム数

	//アニメーション1ループにかかるフレーム数
	constexpr int kIdleAnimTotalFrame = kIdleAnimNum * kSingleAnimFrame;    //待機アニメーションの1ループにかかるフレーム数
	constexpr int kRunAnimTotalFrame = kRunAnimNum * kSingleAnimFrame;      //走るアニメーションの1ループにかかるフレーム数
	constexpr int kAttackAnimTotalFrame = kAttackAnimNum * kSingleAnimFrame; //攻撃アニメーションの1ループにかかるフレーム数

	constexpr int kMoveSpeed = 10;                                          // 移動速度
	constexpr int kMaxFrames = 10;                                          // 最大フレーム数
	constexpr int kGravity = 2;                                             // 重力加速度
	constexpr int kJumpPower = 40;                                          // ジャンプ初速
	constexpr int kGroundY = Game::kScreenHeight / 2 + kHeight / 2 - 30;		    // 地面のY座標（仮定）
	constexpr float kStartX = 1000;                                         // 敵の初期X座標
	constexpr float kStartY = Game::kScreenHeight / 2 + kHeight / 2 - 30;		// 敵の初期Y座標
	constexpr int kParryMaxFrame = 10;                                      // パリィ状態の最大フレーム数
}

Enemy::Enemy():
	m_animFrame(0),
	m_isFlip(true),
	m_graphCount(0),
	m_frameIndex(0),
	m_idleGraph(-1),
	m_runGraph(-1),
	m_attackGraph(-1),
	m_x(0),
	m_y(0),
	m_width(0),
	m_height(0),
	m_vy(0),
	m_isOnGround(true),
	m_isMoving(false)
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	m_x = kStartX;
	m_y = kStartY;
	m_width = kWidth;
	m_height = kHeight;
}

void Enemy::End()
{
	DeleteGraph(m_idleGraph);
	DeleteGraph(m_runGraph);
	DeleteGraph(m_attackGraph);
}

void Enemy::Update()
{
	//アニメーションを進める
	m_animFrame++;

	m_isMoving = false; // 移動中かどうかのフラグをリセット

	// 重力と垂直移動の適用
	if (!m_isOnGround)
	{
		m_vy += kGravity;                   // 下向きに加速
		m_y += m_vy;                        // 垂直位置を更新
		int groundY = kGroundY;             // 地面のY座標を定義
		if (m_y >= groundY)                 // 地面に到達した場合
		{
			m_y = groundY;                  // 地面の位置に修正
			m_vy = 0;                       // 垂直速度をリセット
			m_isOnGround = true;            // 地面にいる状態に戻す
		}
	}
}

void Enemy::Draw()
{
	//移動中かどうかでアニメーションを変更する
	int tempTotalFrame = kIdleAnimTotalFrame;
	int tempHanndle = m_idleGraph;
	int currentFrame = m_animFrame;//現在のフレーム数を取得

	//現在のフレーム数から表示したいコマ番号を計算で求める
	int animNo = (currentFrame % tempTotalFrame) / kSingleAnimFrame;
	DrawRectRotaGraph(m_x, m_y,                 //描画位置
		animNo * kWidth, 0,                     //描画元の矩形の左上座標
		kWidth, kHeight,                        //描画元の矩形の幅と高さ
		double(3.0), 0.0,                       //拡大率と回転角度
		tempHanndle, true,                      //描画するグラフィックハンドル
		m_isFlip);	                            //左右反転フラグ
}
