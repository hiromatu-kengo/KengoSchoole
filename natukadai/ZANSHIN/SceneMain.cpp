#include "SceneMain.h"
#include"DxLib.h"
#include <Windows.h>
#include "Game.h"

namespace
{
	constexpr int kScreenX = Game::kScreenWidth / 4;
	constexpr int kScreenY = Game::kScreenHeight / 2;
	// プレイヤーのアニメーションフレーム数
	constexpr int kPlayerFrameCount = 10;
}

SceneMain::SceneMain():
	m_playerIdleHandle(-1),
	m_playerRunHandle(-1),
	m_player()
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

	// 読み込んだ配列を Player に渡す（内部配列へコピー）
	m_player.SetIdleGraph(m_playerIdleHandle);
	m_player.SetRunGraph(m_playerRunHandle);
	// プレイヤーの初期配置を設定
	m_player.Init();

	// 画像読み込みチェック（デバッグ用）
}

void SceneMain::End()
{
	DeleteGraph(m_playerIdleHandle);
	DeleteGraph(m_playerRunHandle);
}

SceneType SceneMain::Update()
{
	// プレイヤー更新
	m_player.Update();
	
	if (CheckHitKey(KEY_INPUT_R))// Rキーでリザルトシーンに遷移(仮)
	{
		return SceneType::Result;
	}
	return SceneType::Main;//通常時は自分のシーンを維持
}

void SceneMain::Draw()
{
	m_player.Draw();

}

void SceneMain::Release()
{
}
