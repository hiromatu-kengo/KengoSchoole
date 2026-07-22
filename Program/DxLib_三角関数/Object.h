#pragma once
class Object
{
public:
	Object();
	~Object();

	void Init();
	void End();
	void Update();
	void Draw();

private:
	float m_x;
	float m_y;

	float m_vecX;
	float m_vecY;


};

