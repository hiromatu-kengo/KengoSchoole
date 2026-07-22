#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//ここから
	//xが100yが100
	DrawPixel(100, 100, GetColor(255, 255, 255));
	//xが320yが240
	DrawPixel(320, 240, GetColor(255, 255, 255));	// 点を打つ

	DrawLine(100, 100, 320, 240, GetColor(255, 255, 255));

	DrawLine(0, 480, 640, 0, GetColor(255, 255, 255));


	//ここまで

	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}