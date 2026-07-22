#pragma once
#include"Vec2.h"
#include"Player.h"
#include"Enemy.h"
#include"LifeIcon.h"
#include"Bg.h"

class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void End();
	void Update();
	void Draw();
	//シーン終了フラグの取得
	bool IsEnd() const { return m_isEnd; }

private:
	static constexpr int kLifeMax = 3;

private:
	//シーン終了フラグ trueならタイトルに移行する
	bool m_isEnd;

	int m_frameCount;

	//グラフィックハンドル
	int m_playerHandle;
	int m_enemyGraphHandle;
	int m_lifeGraphHandle;
	int m_bgGraphHandle;

	//フォントハンドル
	int m_gameoverFontHandle;
	int m_fadeFrame;
	int m_fadeSpeed;

	//演出用変数
	float m_sinAngle;

	//ゲーム開始前ウェイト
	int m_waitFrame;

	//現在のスコア
	int m_score;
	int m_dispScore;//カウントアップの演出用に見せるスコア

	Player m_player;
	Enemy m_enemy;
	LifeIcon m_life[kLifeMax];
	Bg m_bg;
};
