#pragma once
#include "Vec2.h"

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
	int m_frameCount;

	Vec2 m_center;

};
