#pragma once
namespace Game
{
	//画面情報
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 720;
	constexpr int kScreenDepth = 32;
}

struct AttackHitbox
{
	int x;			// X座標
	int y;			// Y座標
	int width;		// 幅
	int height;		// 高さ
	bool isActive;	// 有効かどうか
};

enum class SceneType
{
	Title,
	Main,
	Result
};