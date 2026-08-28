#pragma once
#include"Game.h"

class Bg
{
public:
	Bg();
	~Bg();
	void Init();
	void End();
	void Update();
	void Draw();

private:
	int m_bgHandles[4];
	int m_earthHandle;
	int m_earth2Handle;
	int m_toriiHandle;
	int m_bambooHandle;

	// 地面描画用プライベート関数
	void DrawGround();
};

