#pragma once
#include"Game.h"
class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();
	void Init();
	void End();
	SceneType Update();
	void Draw();

private:
	int m_bgmHandle = -1; // BGM用ハンドル
	int m_titleGraph = -1; // タイトルロゴ用ハンドル

	// フェードアウト用変数
	bool m_isFadingOut = false; // フェード中フラグ
	int m_bgmVolume = 255;      // 現在の音量（255: 最大）
	int m_fadeSpeed = 5;        // 1フレームあたりに下げる音量

	// 点滅演出用のタイマー
	int m_blinkTimer = 0;
};

