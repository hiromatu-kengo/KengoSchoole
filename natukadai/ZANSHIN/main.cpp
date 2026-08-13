#include "DxLib.h"
#include "Game.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneResult.h"


// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//Windowモードを起動数
	ChangeWindowMode(1);

	//ウインドウサイズを16:9に
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kScreenDepth);

	//ウインドウのタイトル表示の変更
SetMainWindowText("ZANSHIN");

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	SceneTitle sceneTitle;
	SceneMain sceneMain;
	SceneResult sceneResult;

	// 現在のシーン・ひとつ前のシーンを示す変数を定義
	SceneType currentScene = SceneType::Title;
	SceneType nextScene = SceneType::Title;

	// シーン初期化
	sceneTitle.Init();

	// ゲームの処理

	while (ProcessMessage() == 0)
	{
		//現在のフレーム開始時刻を取得
		LONGLONG start = GetNowHiPerformanceCount();

		//画面をクリア
		ClearDrawScreen();


		switch (currentScene)
		{
		case SceneType::Title:
			nextScene = sceneTitle.Update();
			sceneTitle.Draw();
			break;

		case SceneType::Main:
			nextScene = sceneMain.Update();
			sceneMain.Draw();
			break;

		case SceneType::Result:
			nextScene = sceneResult.Update();
			sceneResult.Draw();
			break;
		}

		if (nextScene != currentScene)
		{
			//シーンの終了処理
			if (currentScene == SceneType::Main)sceneMain.End();

			//シーンの初期化
			currentScene = nextScene;

			if (currentScene == SceneType::Title) sceneTitle.Init();
			if (currentScene == SceneType::Main) sceneMain.Init();		
			if (currentScene == SceneType::Result) sceneResult.Init();
		}

		//画面の書き換えを待つ
		ScreenFlip();

		//escキーを押したらゲームを強制終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		//画面のリフレッシュレートにかかわらず1/60経過するまで待つ
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			//時間経過まで何もせずに待つ
		}

	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}