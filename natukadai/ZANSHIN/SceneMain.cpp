#include "SceneMain.h"
#include"DxLib.h"
#include "Windows.h"
#include "Game.h"

namespace
{
	constexpr int kScreenX = Game::kScreenWidth / 4;
	constexpr int kScreenY = Game::kScreenHeight / 2;
	// プレイヤーのアニメーションフレーム数
	constexpr int kPlayerFrameCount = 10;
}

SceneMain::SceneMain() :
	m_playerIdleHandle(-1),
	m_playerRunHandle(-1),
	m_playerAttackHandle(-1),
	m_enemyIdleHandle(-1),
	m_enemyRunHandle(-1),
	m_enemyAttackHandle(-1),
	m_bg(),
	m_player(),
	m_enemy(),
	m_playerHasHit(false)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	//シーン内で使用するリソースのロード
	// 戻り値を使わず配列の中身をチェックする
	m_playerIdleHandle = LoadGraph("image/player/idle.png");
	m_playerRunHandle = LoadGraph("image/player/run.png");
	m_playerAttackHandle = LoadGraph("image/player/ATTACK 1.png");

	m_enemyIdleHandle = LoadGraph("image/enemy/Idle.png");
	m_enemyRunHandle = LoadGraph("image/enemy/Walk.png");
	m_enemyAttackHandle = LoadGraph("image/enemy/Atk.png");

	m_bg.Init();

	// 読み込んだ配列を Player に渡す（内部配列へコピー）
	m_player.SetIdleGraph(m_playerIdleHandle);
	m_player.SetRunGraph(m_playerRunHandle);
	m_player.SetAttackGraph(m_playerAttackHandle);

	m_enemy.SetIdleGraph(m_enemyIdleHandle);
	m_enemy.SetRunGraph(m_enemyRunHandle);
	m_enemy.SetAttackGraph(m_enemyAttackHandle);

	// 初期配置を設定
	m_player.Init();
	m_enemy.Init();
	m_playerHasHit = false;

	// 画像読み込みチェック（デバッグ用）
}

void SceneMain::End()
{
	DeleteGraph(m_playerIdleHandle);
	DeleteGraph(m_playerRunHandle);
	DeleteGraph(m_playerAttackHandle);

	DeleteGraph(m_enemyIdleHandle);
	DeleteGraph(m_enemyRunHandle);
	DeleteGraph(m_enemyAttackHandle);
	m_bg.End();
}

SceneType SceneMain::Update()
{
	// プレイヤー更新
	m_player.Update();
	// ★ プレイヤーがヒットストップ中（時が止まっている状態）は敵の動作更新を止める
	if (!m_player.IsHitStopped())
	{
		m_enemy.Update(m_player.GetX(), m_player.GetY(), 80.0f, m_player.IsAttacking());
	}

	// =========================================================
	// 1. プレイヤーの攻撃 -> 敵へのヒット判定（ヒットストップ演出付き）
	// =========================================================
	if (!m_playerHasHit && IsOverlap(m_player.GetAttackHitbox(), m_enemy.GetHitbox()))
	{
		float hitX = static_cast<float>(m_enemy.GetX());
		float hitY = static_cast<float>(m_enemy.GetY() - 20.0f);

		// ★ ヒットストップ＆斬撃エフェクト呼び出し
		m_player.OnHitSuccess(hitX, hitY);

		m_enemy.OnDamage(10, 20);
		m_playerHasHit = true;
	}

	if (!m_player.IsAttacking())
	{
		m_playerHasHit = false;
	}

	// =========================================================
	// 2. 敵の攻撃 -> プレイヤーへのヒット判定（パリィ・ガード・被弾）
	// =========================================================
	Hitbox enemyAtkBox = m_enemy.GetAttackHitbox();

	if (enemyAtkBox.isActive)
	{
		Hitbox playerBox;
		playerBox.x = m_player.GetX();
		playerBox.y = m_player.GetY();
		playerBox.width = 40.0f;
		playerBox.height = 80.0f;
		playerBox.isActive = true;

		if (IsOverlap(enemyAtkBox, playerBox))
		{
			// A. パリィ成功！
			if (m_player.IsParrying())
			{
				float hitX = (m_player.GetX() + enemyAtkBox.x) / 2.0f;
				float hitY = (m_player.GetY() + enemyAtkBox.y) / 2.0f;

				// ★ パリィ時の画面揺れ＋ヒットストップ＋光彩エフェクト発動
				m_player.OnParrySuccess(hitX, hitY);
				m_enemy.OnParried();
			}
			// B. ガード成功
			else if (m_player.IsGuarding())
			{
				m_player.OnDamage(0, 15);
			}
			// C. 被弾（ノーガード）
			else
			{
				m_player.OnDamage(20, 30);
			}

			// 多段ヒット防止のため判定クリア
			m_enemy.ClearAttackHitbox();
		}
	}

	if (CheckHitKey(KEY_INPUT_X))// Xキーでリザルトシーンに遷移(仮)
	{
		return SceneType::Result;
	}
	return SceneType::Main;//通常時は自分のシーンを維持
}

void SceneMain::Draw()
{
	m_bg.Draw();
	m_player.Draw();
	m_enemy.Draw();


}

void SceneMain::Release()
{
}
