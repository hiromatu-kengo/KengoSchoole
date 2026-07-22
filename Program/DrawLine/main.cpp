#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Windowモードを起動数
	ChangeWindowMode(1);

	//ウインドウサイズを16:9に
	SetGraphMode(1280, 720, 32);

	//ウインドウのタイトル表示の変更
	SetMainWindowText("DxLibTemlate");

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//DrawLine(0, 0, 1280, 720, GetColor(255, 255, 255));
	//DrawLine(1280, 0, 0, 720, GetColor(0, 111, 111));
	/*
	for (int x = 0;x < 4; x++)
	{
		DrawLine(x*310, 0, x*310 , 720, GetColor(255, 0, 0));
	}
	for (int y = 0;y < 4;y++)
	{
		DrawLine(0, y*180, 1280 , y*180, GetColor(255, 0, 0));
	}
	*/
	for (int y = 0;y < 4;y++)
	{
		DrawLine(0, y * 180, (y+1)*310, (y+1) * 720, GetColor(255, 0, 0));
	}
	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}