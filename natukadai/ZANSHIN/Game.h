#pragma once
#include <cmath>
namespace Game
{
	//画面情報
	constexpr int kScreenWidth =1920;
	constexpr int kScreenHeight = 1080;
	constexpr int kScreenDepth = 32;
}

struct Hitbox
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
// Hitbox 型同士の判定関数
inline bool IsOverlap(const Hitbox& a, const Hitbox& b)
{
	if (!a.isActive || !b.isActive) return false;

	return (std::abs(a.x - b.x) < (a.width + b.width) / 2.0f) &&
		(std::abs(a.y - b.y) < (a.height + b.height) / 2.0f);
}