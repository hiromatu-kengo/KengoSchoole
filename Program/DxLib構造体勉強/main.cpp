#include "DxLib.h"
//定数の定義
#define SCREEN_WIDTH 1280 //画面の横幅
#define SCREEN_HEIGHT 720 //画面の縦幅
#define COLOR_DEPTH 32

#define SPEED 20 //キャラクターの移動速度

//構造体の作成
struct Pos
{
	int x;
	int y;
};

struct Player
{
	Pos pos;
	int handle;
};

void DrawPlayer(Player drawplayer)
{
	//キャラクターを表示する処理
	DrawGraph(drawplayer.pos.x, drawplayer.pos.y, drawplayer.handle, false);
}

void UpdatePlayer(Player* pPlayer)
{
	//キャラクターを動かす処理
	pPlayer->pos.x += SPEED;
	//x座標が1280以上になったら
	if (pPlayer->pos.x >= SCREEN_WIDTH)
	{
		//x座標を0にする
		pPlayer->pos.x = 0;
	}
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Windowモードを起動数
	ChangeWindowMode(1);

	//ウインドウサイズを16:9に
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_DEPTH);

	//ウインドウのタイトル表示の変更
	SetMainWindowText("DxLibTemlate");

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	//ゲームが始まる前にグラフィックをメモリにロードする
	//ロードしたグラフィックを使うときはDxLibが割り当てたハンドル(管理番号)
	//を指定して処理を行う
//	int handle = LoadGraph("a.bmp");
	Player pl[5];
	
	for (int i = 0;i < 5;i++)
	{
		pl[i].handle = LoadGraph("a.bmp");



		//キャラクターの座標

	//	int x = SCREEN_WIDTH /2;
	//	int y = SCREEN_HEIGHT /2;

		// i番目のx座標をバラバラにする（例: 100, 200, 300... とズラしてみる）
		pl[i].pos.x = (i + 1) * 150;

		// y座標も適当にバラバラにする
		pl[i].pos.y = 200 + (i * 50);
	}


	while (ProcessMessage() == 0)
	{
		//現在のフレーム開始時刻を取得
		LONGLONG start = GetNowHiPerformanceCount();

		//画面をクリア
		ClearDrawScreen();
	

		for (int i = 0;i < 5;i++)
		{
			UpdatePlayer(&pl[i]);
			DrawPlayer(pl[i]);
		}



		//ゲームの処理
		
		
		
		//画面の書き換えを待つ
		ScreenFlip();

		//画面のリフレッシュレートにかかわらず1/60経過するまで待つ
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			//時間経過まで何もせずに待つ
		}

	}
	for (int i=0;i < 5;i++)
	{
		//メモリに置いたグラフィックをメモリから削除
		DeleteGraph(pl[i].handle);
	}
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}