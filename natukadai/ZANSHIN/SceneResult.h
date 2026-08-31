#pragma once
#include "Game.h"

// 背景を舞う光の粒子構造体
struct ResultParticle
{
	float x, y;
	float speedY;
	float alpha;
	float size;
};

class SceneResult
{
public:
	SceneResult();
	~SceneResult();
	void Init();
	void End();
	SceneType Update();
	void Draw();

private:
	int m_bgmHandle;      // BGMハンドル
	int m_fadeAlpha;      // フェード用アルファ値
	bool m_isFadingIn;    // フェードイン中か
	bool m_isFadingOut;   // フェードアウト中か
	int m_timer;          // 演出用のタイマーカウント

	// 豪華な光のパーティクル（30個）
	static constexpr int kParticleCount = 30;
	ResultParticle m_particles[kParticleCount];
};

