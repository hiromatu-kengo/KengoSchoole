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
	//当たり判定
	int GetRadius()const;
	int GetCenterX()const { return m_x; }
	int GetCenterY()const { return m_y; }

private:
	//位置情報
	int m_x;
	int m_y;
};

