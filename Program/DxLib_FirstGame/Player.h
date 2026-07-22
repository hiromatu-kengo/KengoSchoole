#pragma once
class Player
{
public:
	Player();
	~Player();

	void Init();
	void End();
	void Update();
	void Draw();

	//使用するグラフィックハンドルの設定
	void SetIdleGraph(int handle) { m_idleGraph = handle; }
	void SetRunGraph(int handle) { m_idleGraph = handle; }

	//当たり判定実装用
	float GetColCenterX() const;
	float GetColCenterY() const;
	float GetRadius() const;

	//プレイヤーが死んだときの処理
	void OnDead();

private:
	int m_idleGraph;
	int m_runGraph;

	//位置情報
	float m_x;
	float m_y;

	//アニメーション管理用変数
	int m_animFrame;
	//左右反転フラグ
	bool m_isFrip;
	//移動中かどうかのフラグ
	bool m_isMoving;

	//死亡フラグ
	bool m_isDead;
};

