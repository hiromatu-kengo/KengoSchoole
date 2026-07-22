#include "DxLib.h"
//#define CIRCLE_NUM 128//C言語風の定数定義　C++敵にはあまりよくない

//C++風定数定義

//無名namespace内で定義したオブジェクトはそのソースコード内でのみ使用可能
//ほかのソースコードで同じ名前を定義したいけど名前が被る、といった事態を防ぐ
namespace
{
	//const int kCicleNum = 64;//constを使って変更できない値を作る
	constexpr int kCicleNum = 64;//定数の定義はconstexprで行う
}
//名前の名前空間
//なめ空間の名前が違えばそれぞれの中に同じ名前のオブジェクトを定義できる
namespace Test//Testという名前を持つ名前空間
{
	constexpr int kTest = 128;
}

struct Pos
{
	int x;
	int y;
};
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
	Pos circle[kCicleNum];
	for (int i = 0;i < kCicleNum;i++)
	{
		circle[i].x = GetRand(1280);
	//	circle[i].y = GetRand(720);
		circle[i].y = Test::kTest;
	}

	SetDrawScreen(DX_SCREEN_BACK);
	
	while (ProcessMessage() == 0)
	{
		//現在のフレーム開始時刻を取得
		LONGLONG start = GetNowHiPerformanceCount();

		//画面をクリア
		ClearDrawScreen();
		
		//ゲームの処理
		for (int i = 0;i < kCicleNum;i++)
		{
			DrawCircle(circle[i].x, circle[i].y, 2, GetColor(255, 255, 255));
		}
		
		//画面の書き換えを待つ
		ScreenFlip();

		//画面のリフレッシュレートにかかわらず1/60経過するまで待つ
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			//時間経過まで何もせずに待つ
		}

	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}