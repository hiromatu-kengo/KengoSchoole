#pragma once

class Enemy
{
public:
	Enemy();
	~Enemy();
	void Init();
	void End();
	void Update();
	void Draw();

	//使用するグラフィックハンドルの設定
	void SetIdleGraph(int handle) { m_idleGraph = handle; }
	void SetRunGraph(int handle) { m_runGraph = handle; }
	void SetAttackGraph(int handle) { m_attackGraph = handle; }
private:
	
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
};