#pragma once
class Trap
{
public:
	Trap();
	~Trap();

	void Init();
	void End();
	void Update();
	void Draw();

	//使用するグラフィックの設定
	void SetHandle(int handle) { m_graphHandle = handle; }
	//当たり判定実装用
	float GetColCenterX() const;
	float GetColCenterY() const;
	float GetRadius() const;

private:
	int m_graphHandle;

	//開始待ち
	int m_waitFrame;

	//現在の座標
	float m_x;
	float m_y;

	//移動ベクトル
	float m_vecX;
	float m_vecY;

	//回転角度
	double m_angle;

};

