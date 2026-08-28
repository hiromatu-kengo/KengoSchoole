#pragma once
#include "Game.h"

enum class PlayerState
{
	Normal, // 通常
	Parry,	// パリィ
	Guard,	// ガード
	Attack	// 攻撃
};

class Player
{
public:
	Player();
	~Player();
	void Init();
	void End();
	void Update();
	void Draw();
	void Release();

	//使用するグラフィックハンドルの設定
	void SetIdleGraph(int handle) { m_idleGraph = handle; }
	void SetRunGraph(int handle) { m_runGraph = handle; }
	void SetAttackGraph(int handle) { m_attackGraph = handle; }

	int GetX() const { return m_x; }
	int GetY() const { return m_y; }
	PlayerState GetState() const { return m_state; }
	Hitbox GetAttackHitbox() const { return m_attackHitbox; }
	// プレイヤーが攻撃中かどうかを返す
	bool IsAttacking() const { return m_state == PlayerState::Attack; }

	// パリィ中・ガード中の判定も必要に応じて追加できます
	bool IsParrying() const { return m_state == PlayerState::Parry; }
	bool IsGuarding() const { return m_state == PlayerState::Guard; }
private:
	//使用するグラフィックハンドル
	int m_playerGHandle[10];

	int m_animFrame;
	bool m_isFlip; // 左右反転フラグ

	// 配列の有効要素数
	int m_graphCount = 0;
	//表示する番号
	int m_frameIndex = 0;
	//使用するグラフィックハンドル
	int m_idleGraph;
	int m_runGraph;
	int m_attackGraph;
	// 画面上の位置とスプライトサイズ
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	// ジャンプ/物理
	int m_vy = 0; // 垂直速度（px/frame）
	bool m_isOnGround = true;
	bool m_isMoving = false; // 移動中かどうかのフラグ

	int m_rightClickFrame;	// 右クリックのフレーム数
	int m_attackFrame;		// 攻撃のフレーム数

	bool m_isLeftClickPrev = false; // 毎フレームのひっだりクリック状態

	Hitbox m_attackHitbox; // 攻撃判定用のヒットボックス
	
	PlayerState m_state;// プレイヤーの状態
};

