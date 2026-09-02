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
	int m_enemyDeathHandle; // 敵の死亡アニメーション画像ハンドル

	int m_postureUiHandle[6];
	int m_enemyPostureUiHandle[6];

	// BGM用ハンドル
	int m_bgmHandle;

	int m_fadeAlpha;      // フェード用の不透明度 (0: 透明 ~ 255: 真っ黒)
	bool m_isFadingIn;    // フェードイン中かフラグ
	bool m_isFadingOut;   // フェードアウト中かフラグ
	SceneType m_nextScene;// フェードアウト後に遷移する次のシーン

	Bg m_bg;
	
	Player m_player;
	Enemy m_enemy;

	//1回の振りで1度だけヒットさせるためのフラグ
	bool m_playerHasHit;

	int m_clearTimer = 0; // クリア演出用タイマー
};

