#include "DxLib.h"
#include"Game.h"
#include"player.h"


/*
//Playerクラスのポインタを受け取って、舞フレーム回転させる処理
void UpdatePlayer(Player* pPlayer)
{
	//　クラスも構造体と同様、メンバーにアクセスするときは->を使用する
	pPlayer->angle += 0.1;
}

//Playerクラスの情報を受け取ってPlayerを表示する関数
void DrawPlayer(Player player)
{
	DrawRotaGraph
	(640, 360,//中心座標
		4.0,//拡大率
		player.angle,//回転
		player.handle,//表示するグラフィックのハンドル
		false//透明度の反映
	);
}
*/

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

	//Playerクラスの実態(インスタンス)の生成
	Player player;
	
	//プレイヤーの初期化
	player.Init();

	while (ProcessMessage() == 0)
	{
		//現在のフレーム開始時刻を取得
		LONGLONG start = GetNowHiPerformanceCount();

		//画面をクリア
		ClearDrawScreen();
		
		//ゲームの処理
		//UpdatePlayer(&player);
		//DrawPlayer(player);//クラスを値渡ししてPlayerを表示
		player.Update();
		player.Draw();

		//画面の書き換えを待つ
		ScreenFlip();

		//画面のリフレッシュレートにかかわらず1/60経過するまで待つ
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			//時間経過まで何もせずに待つ
		}

	}
	//プログラム終了時に使用したメモリを開放する
	player.End();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}