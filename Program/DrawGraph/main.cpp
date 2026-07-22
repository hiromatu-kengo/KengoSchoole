#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	ChangeWindowMode(1);	//windouwモードでプログラムを動かしてください

	//ウインドウサイズを変更する
	SetGraphMode(1280, 720, 32);


	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	DrawPixel(320, 240, GetColor(255, 255, 255));	// 点を打つ

	//自分で用意した画像を表示する
	LoadGraphScreen(0, 0, "test.bmp", 1);
	LoadGraphScreen(640, 650, "player.bmp", 0);//前面に表示したいグラフィックを後で描画する
	LoadGraphScreen(560, 650, "player.bmp", 0);
	LoadGraphScreen(480, 650, "player.bmp", 0);

	int j;

	for (j = 1; j <= 5; j++)
	{
		LoadGraphScreen(j*64, 0, "player.bpm", 0);
	};

	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}