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
	//当たり判定
	int GetRadius()const { return m_radius; }
	int GetCenterX()const { return m_x; }
	int GetCenterY()const { return m_y; }
	//プレイヤーと当たったと胃の処理
	void OnCollision();

private:
	int m_x;
	int m_y;
	int m_radius;
};

