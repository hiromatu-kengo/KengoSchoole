#pragma once
#include"Vec2.h"

class Player
{
public:
	Player();
	~Player();

	void Init();
	void End();
	void Update();
	void Draw();

	//グラフィック設定
	void SetIdleHandle(int handle) { m_idleHandle = handle; }
	//位置取得
	Vec2 GetPos()const { return m_pos; }
	//当たり判定
	Vec2 GetColCenter() const;
	float GetColRadius()const;
	//HPの取得
	int GetHp()const { return m_hp; }
	//のこぎりにぶつかった時の処理
	void OnHit();
	//死んでいるかどうか
	bool IsDead() const;
private:
	//グラフィックハンドル
	int m_idleHandle;

	//現在位置
	Vec2 m_pos;
	//移動情報
	Vec2 m_vec;
	double m_angle;
	//地面についているかどうか
	bool m_isLanding;//地面についている場合はtrue

	//サインカーブ生成に使用する角度のデータ
	float m_sinAngle;
	float m_sinSpeed;

	//残りHP
	int m_hp;
	//ダメージを受けない時間
	//0の時はダメージを受ける(カウントダウン)
	int m_noDamageFrame;
};

