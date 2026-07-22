#include "player.h"
#include"DxLib.h"
#include"Game.h"

namespace
{
	//初期位置
	constexpr int kStartX = 640;
	constexpr int kStartY = 640;

	constexpr double kRotSpeed = 1.0;
	constexpr int kSpeed = 4;
	constexpr double kScale = 4.0;
}

void Player::Init()
{
	//グラフィックをメモリにロードする
	handle = LoadGraph("player.bmp");
	//回転情報
	angle = 0.0;
	x = kStartX;
	y = kStartY;
}
void Player::End()
{
	DeleteGraph(handle);
}

void Player::Update()
{
	if (x >= Game::kScreenWidth)
	{
		x = 0;
		y = Game::kScreenHeight;
	}
	x += 160;
	y += -80;
	angle += kRotSpeed;
}
void Player::Draw()
{
	DrawRotaGraph
	(x, y,//中心座標
		4.0,//拡大率
		angle,//回転
		handle,//表示するグラフィックのハンドル
		false//透明度の反映
	);
}