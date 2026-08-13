#pragma once
#include "Game.h"
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
	int m_playerAttackHandle;


	Player m_player;

};

