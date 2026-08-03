#pragma once
#include "Player.h"

class SceneMain
{
public:
	SceneMain();
	~SceneMain();
	void Init();
	void Update();
	void Draw();
	void Release();

private:
	//シーンで使用するリソースハンドル
	int m_playerIdleHandle;


	Player player_;

};

