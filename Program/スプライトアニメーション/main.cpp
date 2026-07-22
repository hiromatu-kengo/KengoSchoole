#include "DxLib.h"
#include"Game.h"
#include<string>

//定数定義
namespace
{
	//使用するグラフィックファイル名
	std::string kFileName = "run.png";
//	std::string kFileName = "enemy.png";


	//アニメーション関連の定数
	constexpr int kAnimNum = 12;//アニメーションのコマ数
//	constexpr int kAnimNum = 10;//アニメーションのコマ数
	constexpr int kSingleAnimFrame = 4;//一コマのフレーム数
	//定数を使用してほかの定数を作ることもある
	constexpr int kAnimTotalFrame = kAnimNum * kSingleAnimFrame;//アニメーション１サイクルの合計フレーム数


//	constexpr int kCharWidth = 32;
//	constexpr int kCharHeight = 32;
//	constexpr int kCharWidth = 80;
//	constexpr int kCharHeight = 64;
}




// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//Windowモードを起動数
	ChangeWindowMode(1);

	//ウインドウサイズを16:9に
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kScreenDepth);

	//ウインドウのタイトル表示の変更
	SetMainWindowText("DxLibTemlate");

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	//stringのメンバー関数c_str()を使って
	//string型のデータからC言語風の文字列データを取得している
	int handle = LoadGraph(kFileName.c_str());
//	int handle = LoadGraph("enemy.png");
	//画像のサイズを取得
	int graphWidth = 0;
	int graphHeight = 0;
	GetGraphSize(handle, &graphWidth,&graphHeight);

	//アニメ１コマのサイズ
	int charWidth = graphWidth / kAnimNum;
	int charHeight = graphHeight;

	//表示するコマ番号0~11
	int charNo = 0;
	int frameCount = 0;

	while (ProcessMessage() == 0)
	{
		//現在のフレーム開始時刻を取得
		LONGLONG start = GetNowHiPerformanceCount();

		//画面をクリア
		ClearDrawScreen();

		//ゲームの処理
		frameCount++;
		charNo = (frameCount % kAnimTotalFrame) / kSingleAnimFrame;

		/*

		if (frameCount >= 4 * 12)
		{
			frameCount = 0;
		}*/
		/*
		if (frameCount >= 4)
		{
			charNo++;
			if (charNo >= 12)
			{
				charNo = 0;
			}
			frameCount = 0;
		}*/

		DrawBox(0, 0, 640, 480, GetColor(0, 0, 255), true);

		//グラフィックをそのまま表示
		DrawGraph(64, 64, handle, true);
		//DrawRectGraphを使って画像の一部のみを表示
		DrawRectGraph
		(
			64, 128,//切り取ったグラフィックをゲーム画面のどこに表示するのかの座標
			charNo * charWidth, 0,//描画するグラフィックの左上座標
			charWidth, charHeight,//力人る幅と高さ
			handle,//どのグラフィックを使用するか
			true//画像の透明度を反映するか
		);


		//画面の書き換えを待つ
		ScreenFlip();

		//画面のリフレッシュレートにかかわらず1/60経過するまで待つ
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			//時間経過まで何もせずに待つ
		}

	}
	DeleteGraph(handle);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
	
}