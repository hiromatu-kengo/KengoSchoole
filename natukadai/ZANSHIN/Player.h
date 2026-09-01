#pragma once
#include "Game.h"

enum class PlayerState
{
	Normal, // 通常
	Parry,	// パリィ
	Guard,	// ガード
	Attack,	// 攻撃
	Stun,	// 姿勢崩れ
	Dead	// 死亡
};

class Player
{
public:
	Player();
	~Player();
	void Init();
	void End();
	void Update();
	void Draw();
	void Release();

	//使用するグラフィックハンドルの設定
	void SetIdleGraph(int handle) { m_idleGraph = handle; }
	void SetRunGraph(int handle) { m_runGraph = handle; }
	void SetAttackGraph(int handle) { m_attackGraph = handle; }
	void SetPostureUIHandle(const int handles[6])
	{
		for (int i = 0; i < 6; ++i)m_postureUiGraph[i] = handles[i];
	}

	int GetX() const { return m_x; }
	int GetY() const { return m_y; }
	PlayerState GetState() const { return m_state; }
	Hitbox GetAttackHitbox() const { return m_attackHitbox; }
	// プレイヤーが攻撃中かどうかを返す
	bool IsAttacking() const { return m_state == PlayerState::Attack; }

	// パリィ中・ガード中の判定も必要に応じて追加できます
	bool IsParrying() const { return m_state == PlayerState::Parry; }
	bool IsGuarding() const { return m_state == PlayerState::Guard; }
	// ダメージ＆体幹獲得処理
	void OnDamage(int damage, int postureDamage);

	// パリィ成功時に敵クラス等から呼び出す処理
	void OnParrySuccess(float hitX, float hitY);
	// 攻撃を当てた時のヒットストップ発動関数
	void OnHitSuccess(float hitX, float hitY);

	// ステータスゲッター
	int GetHp() const { return m_hp; }
	int GetMaxHp() const { return m_maxHp; }
	int GetPosture() const { return m_posture; }
	int GetMaxPosture() const { return m_maxPosture; }

	// ヒットストップ中か判定
	bool IsHitStopped() const { return m_hitStopFrame > 0; }

	bool IsDeadFinished() const { return m_isDeadFinished; }
private:
	//使用するグラフィックハンドル
	int m_playerGHandle[10];
	int m_postureUiGraph[6] = { -1, -1, -1, -1, -1, -1 };

	int m_animFrame;
	bool m_isFlip; // 左右反転フラグ

	// 配列の有効要素数
	int m_graphCount = 0;
	//表示する番号
	int m_frameIndex = 0;
	//使用するグラフィックハンドル
	int m_idleGraph;
	int m_runGraph;
	int m_attackGraph;
	// 画面上の位置とスプライトサイズ
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	// ジャンプ/物理
	int m_vy = 0; // 垂直速度（px/frame）
	bool m_isOnGround = true;
	bool m_isMoving = false; // 移動中かどうかのフラグ

	int m_rightClickFrame;	// 右クリックのフレーム数
	int m_attackFrame;		// 攻撃のフレーム数

	bool m_isLeftClickPrev = false; // 毎フレームのひっだりクリック状態

	int m_seAttack = -1; // 攻撃
	int m_seGuard = -1; // ガード
	int m_seParry = -1; // パリィ
	int m_seDead = -1; // 被撃破

	Hitbox m_attackHitbox; // 攻撃判定用のヒットボックス
	
	PlayerState m_state;// プレイヤーの状態

	// 追加：HP & 忍耐（体幹）ゲージ
	int m_hp = 100;
	int m_maxHp = 100;
	int m_posture = 0;
	int m_maxPosture = 100;
	int m_stunFrame = 0; // スタン残り時間

	// 演出関連パラメータ
	int m_shakeFrame = 0;
	int m_shakeIntensity = 0;
	int m_shakeOffsetX = 0;
	int m_shakeOffsetY = 0;

	int m_parryEffectFrame = 0;
	int m_parryEffectMaxFrame = 15;
	int m_parryEffectX = 0;
	int m_parryEffectY = 0;

	// ヒットストップ関連
	int m_hitStopFrame = 0;

	// 斬撃ヒットエフェクト
	int m_slashEffectFrame = 0;
	int m_slashEffectX = 0;
	int m_slashEffectY = 0;

	// 死亡演出関連
	int m_deadTimer = 0;			// 死亡後のタイマー
	bool m_isDeadFinished = false;	// 死亡後の演出が完了したかどうかのフラグ
};

