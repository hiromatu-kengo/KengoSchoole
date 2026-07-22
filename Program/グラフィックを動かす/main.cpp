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

	SetDrawScreen(DX_SCREEN_BACK);

	//プレイヤーの表示位置
	int x = 640;
	int y = 360;

	//あらかじめグラフィックをメモリにロードしておく
	//グラフィックに割り当てられたハンドル(管理番号)を覚えておく
	int handle = LoadGraph("prayer.bmp");

	while (ProcessMessage() == 0)
	{
		//現在のフレーム開始時刻を取得
		LONGLONG start = GetNowHiPerformanceCount();

		//画面をクリア
		ClearDrawScreen();
		
		//ゲームの処理

		//x += 2;
		if (x >= 1280)
		{
			x -= 1280;
		}
		int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if (pad & PAD_INPUT_DOWN)
		{
			y += 4;
		}
		if (pad & PAD_INPUT_UP)
		{
			y -= 4;
		}
		if (pad & PAD_INPUT_LEFT)
		{
			x -= 4;
		}
		if (pad & PAD_INPUT_RIGHT)
		{
			x += 4;
		}
		//毎フレームSSＤからグラボへのコピーが発生してしまう→遅い　処理落ちの原因に
	//	LoadGraphScreen(x, y, "prayer.bmp", false);

		//メモリにロードしたグラフィックを表示する
		DrawGraph(x, y, handle, false);

		//文字を表示する
		DrawString(0, 0, "test", GetColor(255, 255, 255));
		//キャラクターの座標を数値で表示する
		DrawFormatString(0, 16, GetColor(255, 255, 255), "座標( %d, %d)", x, y);
		
		//画面の書き換えを待つ
		ScreenFlip();

		//画面のリフレッシュレートにかかわらず1/60経過するまで待つ
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			//時間経過まで何もせずに待つ
		}

	}

	//ゲームが終わったらメモリからグラフィックを削除
	DeleteGraph(handle);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}