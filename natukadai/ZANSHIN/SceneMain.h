#pragma once
#include "Player.h"

class SceneMain
{
public:
	SceneMain();
	~SceneMain();
	void Init();
	void End();
	SceneType Update();
	void Draw();
	void Release();

private:
	//シーンで使用するリソースハンドル
	int m_playerIdleHandle;
	int m_playerRunHandle;


	Player m_player;

};

