#pragma once
#include"DxLib.h"
#include"Game.h"
#include"Player.h"

enum class EnemyState
{
	Idle,		//待機
	Run,		//移動
	AttackSign, //攻撃の前兆（溜め動作）
	Attack,		//攻撃中
	AttackWait,		//攻撃後の隙（硬直）
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
	void Update(float playerX, float playerY, float playerWidth, bool isPlayerAttacking);//プレイヤー情報を受け取る
	void Draw();

	
	

	//使用するグラフィックハンドルの設定
	void SetIdleGraph(int handle) { m_idleGraph = handle; }
	void SetRunGraph(int handle) { m_runGraph = handle; }
	void SetAttackGraph(int handle) { m_attackGraph = handle; }
	void SetDeathGraph(int handle) { m_deathGraph = handle; } // 死亡アニメーション画像設定
	void SetPostureUIHandle(const int handles[6])
	{
		for (int i = 0; i < 6; ++i)
		{
			m_postureUiHandle[i] = handles[i];
		}
	}

	//敵の被弾判定を取得する
	Hitbox GetHitbox() const { return m_hitbox; }
	Hitbox GetAttackHitbox() const { return m_attackHitbox; }

	// 死亡アニメーション＋暗転演出まで完了したか取得
	bool IsDeadFinished() const { return m_isDeadFinished; }
	bool IsDead() const { return m_isDead; }

	// 位置座標のゲッター
	float GetX() const { return m_x; }
	float GetY() const { return m_y; }

	// 弾かれた（パリィされた）時の処理
	void OnParried();
	// ダメージと体幹（忍耐）ダメージを受ける処理
	void OnDamage(int damage, int postureDamage);
	// 攻撃判定クリア用（多段ヒット防止）
	void ClearAttackHitbox() { m_attackHitbox.isActive = false; }
	// 忍殺可能な状態かを取得
	bool IsExecutionTarget() const { return m_state == EnemyState::Stun && !m_isDead; }

private:
	//アニメーション・グラフィック
	int m_animFrame;
	bool m_isFlip; // 左右反転フラグ
	int m_idleGraph;
	int m_runGraph;
	int m_attackGraph;
	int m_deathGraph; // 死亡用画像ハンドル

	//座標・移動
	float m_x;
	float m_y;
	int m_width;
	int m_height;
	float m_vy;
	bool m_isOnGround = true;

	//ステータス・パラメータ
	int m_hp;		// HP
	int m_posture;	// 現在の体感値
	int m_maxPosture;//最大体感値
	int m_stock;	// 残機
	bool m_isDead;
	bool m_isDeadFinished; // 死亡演出全完了フラグ
	int m_postureUiHandle[6]; // 体幹UI画像ハンドルを追加

	//state管理・タイマー
	EnemyState m_state;
	int m_stateFrame;	// 各stateでの経過フレーム
	int m_comboCount;	// 連続攻撃の回数カウント
	int m_maxCombo;		// 今回の連撃で繰り返す回数（１～３回など）

	// 配列の有効要素数
	int m_graphCount = 0;
	//表示する番号
	int m_frameIndex = 0;

	bool m_isMoving = false; // 移動中かどうかのフラグ

	// 被弾時の演出用パラメータ
	int m_hitStopFrame = 0;       // ヒットストップ中フレーム
	int m_damageEffectFrame = 0;  // 斬撃エフェクトの表示フレーム
	float m_knockbackVx = 0.0f;   // ノックバックの横方向移動速度

	// 画面フェード用アルファ値
	int m_fadeAlpha = 0;

	int m_seAttack = -1; // 攻撃
	int m_seGuard = -1; // ガード
	int m_seParry = -1; // パリィ
	int m_seNinsatsu = -1; // 忍殺受け

	//当たり判定
	Hitbox m_hitbox;			//被弾判定
	Hitbox m_attackHitbox;	//攻撃判定
};