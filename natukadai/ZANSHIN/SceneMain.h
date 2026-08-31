#pragma once
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Bg.h"

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

	int m_enemyIdleHandle;
	int m_enemyRunHandle;
	int m_enemyAttackHandle;

	int m_postureUiHandle[6];
	int m_enemyPostureUiHandle[6];

	Bg m_bg;
	
	Player m_player;
	Enemy m_enemy;

	//1回の振りで1度だけヒットさせるためのフラグ
	bool m_playerHasHit;
};

