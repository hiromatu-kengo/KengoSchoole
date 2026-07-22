#include "DxLib.h"
#include"Game.h"


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

	//ゲームが始まる前に使用するフォントのデータを作成する
	int handle = CreateFontToHandle("HG行書体",64,-1,-1);
	
	while (ProcessMessage() == 0)
	{
		//現在のフレーム開始時刻を取得
		LONGLONG start = GetNowHiPerformanceCount();

		//画面をクリア
		ClearDrawScreen();
		
		//ゲームの処理
		
		//ChangeFont();


		DrawString(16, 16, "フォント変更", GetColor(255, 255, 255));

		DrawStringToHandle(16, 64, "変更後", GetColor(0, 255, 255), handle);

		DrawFormatStringToHandle(16, 144,GetColor(255, 255, 0), handle, "FPS:%.1f", GetFPS());

		//画面の書き換えを待つ
		ScreenFlip();

		//画面のリフレッシュレートにかかわらず1/60経過するまで待つ
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			//時間経過まで何もせずに待つ
		}

	}

	DeleteFontToHandle(handle);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}