#pragma once
namespace Game
{
	//画面情報
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 720;
	constexpr int kScreenDepth = 32;
}

//攻撃用判定
struct AttackHitbox
{
	int x;			// X座標
	int y;			// Y座標
	int width;		// 幅
	int height;		// 高さ
	bool isActive;	// 有効かどうか
};

struct EnemyHitbox
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
bool IsOverlap(const AttackHitbox& a, const EnemyHitbox& b)
{
	if (!a.isActive)return false; // 攻撃判定がOFFなら不成立

	return(abs(a.x - b.x) < (a.width + b.width) / 2) &&
		(abs(a.y - b.y) < (a.height + b.height) / 2);
}