#pragma once
#include"Shot.h"

class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void End();
	void Update();
	void Draw();
private:
	static const int kShotNum = 3;

private:
	int m_frameCount;

	//グラフィックハンドル
	int m_shotGraphHandle;

	/*
	float m_x;
	float m_y;
	float m_vec;
	float m_vecY;
	*/
	Shot m_shot[kShotNum];

};
