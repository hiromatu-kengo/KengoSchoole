#pragma once
#include"Vec2.h"

class LifeIcon
{
public:
	LifeIcon();
	~LifeIcon();

	void Init();
	void End();
	void Update();
	void Draw();

	//グラフィック設定
	void SetGraphHandle(int handle) { m_graphHandle = handle; }

	//位置の設定
	void SetPos(Vec2 pos) { m_pos = pos; }

	//アクティブかどうかを設定
	void SetActive(bool isActive) { m_isActive = isActive; }

	void SetVisible(bool isVisible) { m_isVisible = isVisible; }

private:
	//グラフィックハンドル
	int m_graphHandle;
	//アニメーション情報
	int m_animFrame;
	//表示位置
	Vec2 m_pos;
	//スケール
	double m_scale;
	//アクティブ
	bool m_isActive;
	//表示するかどうか
	bool m_isVisible;
};

