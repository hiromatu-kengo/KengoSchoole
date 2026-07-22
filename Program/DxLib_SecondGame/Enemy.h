#pragma once
#include"Vec2.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void End();
	void Update();
	void Draw();

	//グラフィックハンドルの設定
	void SetGraphHandle(int handle) { m_graphHandle = handle; }

	//位置情報の取得
	Vec2 GetPos()const { return m_pos; }
	Vec2 GetLastPos()const { return m_lastPos; }
	//当たり判定
	Vec2 GetColCenter() const;
	float GetColRadius()const;
	//登場回数を取得
	int GetAppearCount()const { return m_appearCount; }
private:
	//のこぎりを予期化に設定する
	void Setup();
	

private:
	int m_graphHandle;

	//登場待ちフレーム数
	int m_waitFrame;

	//フェードの管理 (カウントダウン)
	int m_fadeFrame;
	// フェードアウト中か
	bool m_isFadingOut;
	//位置
	Vec2 m_pos;
	Vec2 m_lastPos;//
	Vec2 m_vec;

	//回転角度
	double m_angle;
	double m_rotSpeed;//回転速度
	//表示反転
	bool m_isFlip;

	//登場回数
	int m_appearCount;
};