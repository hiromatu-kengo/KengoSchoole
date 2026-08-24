#pragma once
#include"DxLib.h"
#include"Game.h"

enum class EnemyState
{
	Idle,		//待機
	Run,		//移動
	Attack,		//攻撃中
	Guard,		//攻撃後の隙（硬直）
	Guard,		//ガード中
	Stun,		//タイ燗崩れ
	Dead		//死亡
};

class Enemy
{
public:
	Enemy();
	~Enemy();
	void Init();
	void End();
	void Update(float playerX,float playerY,bool isPlayerAttacking);//プレイヤー情報を受け取る
	void Draw();

	//被ダメージ処理 体幹ダメージ
	void OnDamage(int damage,int postureDamage);
	void OnParried();

	//敵の被弾判定を取得する
	EnemyHitbox GetHitbox() const { return m_hitbox; }
	AttackHitbox GetAttackHitbox() const { return m_attackHitbox; }

	//使用するグラフィックハンドルの設定
	void SetIdleGraph(int handle) { m_idleGraph = handle; }
	void SetRunGraph(int handle) { m_runGraph = handle; }
	void SetAttackGraph(int handle) { m_attackGraph = handle; }
private:
	//アニメーション・グラフィック
	int m_animFrame;
	bool m_isFlip; // 左右反転フラグ
	int m_idleGraph;
	int m_runGraph;
	int m_attackGraph;

	//座標・移動
	float m_x;
	float m_y;
	int m_width;
	int m_height;
	float m_vy;
	bool m_isOnGround;

	//ステータス・パラメータ
	int m_hp;		// HP
	int m_posture;	// 現在の体感値
	int m_maxPosture;//最大体感値
	int m_stock;	// 残機
	bool m_isDead;

	//state管理・タイマー
	EnemyState m_state;
	int m_stateFrame;	// 各stateでの経過フレーム
	int m_comboCount;	// 連続攻撃の回数カウント
	int m_maxCombo;		// 今回の連撃で繰り返す回数（１～３回など）

	// 配列の有効要素数
	int m_graphCount = 0;
	//表示する番号
	int m_frameIndex = 0;

	// ジャンプ/物理
	int m_vy = 0; // 垂直速度（px/frame）
	bool m_isOnGround = true;
	bool m_isMoving = false; // 移動中かどうかのフラグ

	//当たり判定
	EnemyHitbox m_hitbox;			//被弾判定
	AttackHitbox m_attackHitbox;	//攻撃判定
};