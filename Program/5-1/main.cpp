#include "DxLib.h"
#include<math.h>
#include<stdlib.h>

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Windowモードを起動数
	ChangeWindowMode(1);

	//ウインドウサイズを16:9に
	

	//ウインドウのタイトル表示の変更
	SetMainWindowText("ヒットチェック");

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	const int WIDTH = 960, HEIGHT = 640;

	const int WHITE = GetColor(255, 255, 255);

    const int RED = GetColor(255, 0, 0);
	
	SetGraphMode(WIDTH, HEIGHT, 32);

	ChangeWindowMode(TRUE);
	
    if (DxLib_Init() == -1) return -1; // ライブラリ初期化 エラーが起きたら終了
    SetBackgroundColor(0, 0, 0); // 背景色の指定
    SetDrawScreen(DX_SCREEN_BACK); // 描画面を裏画面にする

    int timer = 0; // 経過時間を数える変数
    enum{TITLE,PLAY,MENU,CLEAR,OVER};//各シーンを定める定数
    int scene = TITLE;

   /*  int imagBG = LoadGraph("image/bg.png");
    int imagDog[4] =
    {
        LoadGraph("image/dog0.png"),
        LoadGraph("image/dog1.png"),
        LoadGraph("image/dog2.png"),
        LoadGraph("image/dog3.png")
    };
    int dogX = 0, dogY = 400;

    int bgm = LoadSoundMem("sound/battle.mp3");
    int se = LoadSoundMem("sound/recover.mp3");
    ChangeVolumeSoundMem(128, bgm);
    PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);*/
   /* int x1 = 0, y1 = 0, w1 = 120 , h1 = 80;//マウスで動かせる円の座標と半径
    int x2 = WIDTH / 2, y2 = HEIGHT / 2, w2 = 160, h2 = 240;*/

    while (1) // メインループ
    {
        ClearDrawScreen(); // 画面をクリアする
        timer++; // 時間のカウント
        SetFontSize(16);
        DrawFormatString(0, 0, WHITE, "%d", timer);
		/*
		
        // カーソルキーの入力
        if (CheckHitKey(KEY_INPUT_UP))    DrawString(0, 20, "上キー", WHITE);
        if (CheckHitKey(KEY_INPUT_DOWN))  DrawString(0, 40, "下キー", WHITE);
        if (CheckHitKey(KEY_INPUT_LEFT))  DrawString(0, 60, "左キー", WHITE);
        if (CheckHitKey(KEY_INPUT_RIGHT)) DrawString(0, 80, "右キー", WHITE);

        // マウスの座標を出力、マウスボタンの入力
        int mouseX, mouseY; // ポインタの座標を代入する変数
        GetMousePoint(&mouseX, &mouseY);
        DrawFormatString(400, 0, WHITE, "(%d, %d)", mouseX, mouseY);
        if (GetMouseInput() & MOUSE_INPUT_LEFT)  DrawString(400, 20, "左ボタン", WHITE);
        if (GetMouseInput() & MOUSE_INPUT_RIGHT) DrawString(400, 40, "右ボタン", WHITE);
        */
        /* DrawLine(0, 0, WIDTH, HEIGHT,GetColor(255, 0, 0));
        DrawBox(0, HEIGHT - 400, 200, HEIGHT - 100, GetColor(0, 255, 0), TRUE); // 矩形(長方形)
        DrawBox(WIDTH - 200, 100, WIDTH - 100, 200, GetColor(0, 0, 255), TRUE); // 矩形(正方形)
        DrawCircle(400, 200, 100, GetColor(0, 255, 255), TRUE); // 円
        DrawOval(400, 400, 200, 100, GetColor(255, 0, 255), FALSE); // 楕円
        DrawTriangle(600, 0, 500, 300, 700, 300, GetColor(255, 192, 0), TRUE); // 三角形
        DrawPixel(400, 200, GetColor(0, 0, 0)); // 点*/
        /*DrawGraph(0, 0, imagBG, FALSE);//背景の表示
        dogX = dogX + 10;
        if (dogX > WIDTH)dogX = -200;
        DrawGraph(dogX, dogY, imagDog[(timer / 5) % 4], TRUE);

        DrawString(0, 20, "Sキーを押すとBMGを停止します", WHITE);
        DrawString(0, 40, "スペースキーを押すと効果音を出力します", WHITE);
        if (CheckHitKey(KEY_INPUT_S))StopSoundMem(bgm);
        if (CheckHitKey(KEY_INPUT_SPACE))PlaySoundMem(se, DX_PLAYTYPE_BACK);*/
        /*int d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
        DrawFormatString(0, 0, WHITE, "中心距離 %d", d);
        if (d <= r1 + r2)
        {
            col1 = GetColor(255, 255, 0);
            col2 = GetColor(0, 255, 255);
        }
        DrawCircle(x1, y1, r1, col1, TRUE);
        DrawCircle(x2, y2, r2, col2, TRUE);*/
        /* GetMousePoint(&x1, &y1);
        int col1 = GetColor(255, 0, 0);
        int col2 = GetColor(0, 0, 255);
        int dx = abs((x1 - x2));
        int dy = abs((y1 - y2));
        if (dx <= (w1 + w2) / 2 && dy <= (h1 + h2) / 2)
        {
            col1 = GetColor(255, 255, 0);
            col2 = GetColor(0, 255, 255);
        }
        DrawBox(x1 - w1 / 2, y1 - h1 / 2, x1 + w1 / 2, y1 + h1 / 2, col1, TRUE);
        DrawBox(x2 - w2 / 2, y2 - h2 / 2, x2 + w2 / 2, y2 + h2 / 2, col2, TRUE);*/
        switch (scene) // 画面遷移を行うswitch文
        {
        case TITLE: // タイトル画面の処理
            SetFontSize(50);
            DrawString(100, 50, "タイトル画面", WHITE);
            SetFontSize(20);
            DrawString(100, 200, "Sキーを押すとゲーム開始", WHITE);
            if (CheckHitKey(KEY_INPUT_S) == 1) scene = PLAY;
            break;

        case PLAY: // ゲームをプレイする処理
            SetFontSize(50);
            DrawString(100, 50, "ゲームプレイ画面", WHITE);
            SetFontSize(20);
            DrawString(100, 200, "Mキーでメニュー画面へ", WHITE);
            SetFontSize(20);
            DrawString(100, 300, "Oキーでゲームオーバー", RED);
            if (CheckHitKey(KEY_INPUT_M) == 1) scene = MENU;
            if (CheckHitKey(KEY_INPUT_O) == 1)
            {
                scene = OVER;
                timer = 0;
            }
            break;

        case MENU: // メニュー画面の処理
            SetFontSize(50);
            DrawString(100, 50, "メニュー画面", WHITE);
            SetFontSize(20);
            DrawString(100, 200, "Rキーでゲームに戻る", WHITE);
            if (CheckHitKey(KEY_INPUT_R) == 1) scene = PLAY;
            break;

        case CLEAR: // ゲームクリアの処理
            // このプログラムでは未記入
            break;

        case OVER: // ゲームオーバーの処理
            SetFontSize(50);
            DrawString(100, 50, "GAME OVER", RED);
            if (timer > 30 * 5) scene = TITLE;
            break;
        }

        ScreenFlip(); // 裏画面の内容を表画面に反映させる
        WaitTimer(33); // 一定時間待つ
        if (ProcessMessage() == -1) break; // Windowsから情報を受け取りエラーが起きたら終了
        if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break; // ESCキーが押されたら終了
        


    }
    
    DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}