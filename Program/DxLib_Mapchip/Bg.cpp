#include"Bg.h"
#include"DxLib.h"
#include"Game.h"

namespace
{
	//	constexpr int kChipSize = 32;
		//マップチップの配置情報を二次元配列でもつ
	/*
	constexpr int kChipSetting[20] =
	{
		2,2,20,2,2,2,20,2,2,2,
		2,2,2,2,2,2,2,2,2,22,
	};
	*/

	constexpr int kChipSize = 32;

	constexpr int kGraphChipNumX = 6;
	//画面に配置するチップの数
	constexpr int kChipNumX = Game::kScreenWidth / kChipSize;
	constexpr int kChipNumY = Game::kScreenHeight / kChipSize;

	constexpr int kChipSetting[kChipNumY][kChipNumX] =
	{
	{ 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20 },
	{ 20, 36, 36, 2, 2, 2, 38, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 20 },
	{ 20, 36, 36, 2, 2, 2, 38, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 20 },
	{ 20, 36, 36, 2, 2, 2, 38, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 20 },
	{ 20, 36, 36, 2, 2, 2, 38, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 20 },
	{ 20, 36, 36, 2, 2, 2, 38, 2, 2, 2, 2, 2, 2, 2, 2, 10, 11, 2, 2, 20 },
	{ 20, 36, 36, 2, 2, 2, 38, 2, 2, 2, 2, 2, 2, 2, 2, 16, 17, 2, 2, 20 },
	{ 20, 36, 36, 2, 2, 2, 38, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 20 },
	{ 20, 36, 36, 2, 2, 2, 38, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 20 },
	{ 20, 36, 36, 2, 2, 2, 38, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 20 },
	{ 20, 36, 36, 2, 2, 2, 38, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 20 },
	{ 20, 36, 36, 2, 2, 2, 38, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 20 },
	{ 20, 36, 36, 2, 2, 2, 38, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 20 },
	{ 20, 36, 36, 2, 2, 2, 38, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 20 },
	{ 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20 },
	};
}

//Bgクラスの関数実装
Bg::Bg() :
	m_handle(-1)
{
}
Bg::~Bg()
{
}
void Bg::Init()
{
	//使用するグラフィックをメモリにロード
	m_handle = LoadGraph("mapchip.png");
}
void Bg::End()
{
	DeleteGraph(m_handle);
}
void Bg::Update()
{

}
void Bg::Draw()
{
	//	DrawGraph(0, 0, m_handle, true);

	//通し番号で指定されているチップを
	//左から何番目、上から何番目、という2のデータに変換したい

	//chipNoからindexXとindexYを計算で求めたい


	//横に20
	//縦に15

	for (int y = 0;y < kChipNumY;y++)
	{
		for (int x = 0;x < kChipNumX;x++)
		{
			int chipNo = kChipSetting[y][x];
			int indexX = chipNo % kGraphChipNumX;
			int indexY = chipNo / kGraphChipNumX;
			DrawRectGraph(kChipSize * x, kChipSize * y,//画面上の位置
				kChipSize * indexX, kChipSize * indexY, kChipSize, kChipSize,//切り取り位置の指定
				m_handle, true);
		}
	}

}