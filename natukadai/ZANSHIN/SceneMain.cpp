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
}

SceneType SceneMain::Update()
{
	// プレイヤー更新
	m_player.Update();
	m_enemy.Update(m_player.GetX(),m_player.GetY(),m_player.IsAttacking());

	// 攻撃中でなければヒット済みフラグを解除
	if (!m_player.IsAttacking())
	{
		m_playerHasHit = false;
	}

	// ヒット判定（1回の攻撃で1回のみダメージ処理）
	if (!m_playerHasHit && IsOverlap(m_player.GetAttackHitbox(), m_enemy.GetHitbox()))
	{
		m_enemy.OnDamage(10, 20); // HPダメージ:10, 体幹ダメージ:20
		m_playerHasHit = true;
	}
	if (CheckHitKey(KEY_INPUT_X))// Xキーでリザルトシーンに遷移(仮)
	{
		return SceneType::Result;
	}
	return SceneType::Main;//通常時は自分のシーンを維持
}

void SceneMain::Draw()
{
	m_player.Draw();
	m_enemy.Draw();

}

void SceneMain::Release()
{
}
