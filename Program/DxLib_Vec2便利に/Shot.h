#pragma once
#include"Vec2.h"

class Shot
{
public:
	Shot();
	~Shot();

	void Init();
	void End();
	void Update();
	void Draw();
	//グラフィックハンドル
	void SetHandle(int handle) { m_graphHandle = handle; }

	void SetVec(Vec2 vec) { m_vec = vec; }
private:
	//グラフィックハンドル
	int m_graphHandle;
	//位置情報
	Vec2 m_pos;
	//移動量
	Vec2 m_vec;
};

