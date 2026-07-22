#define _USE_MATH_DEFINES
#include "DxLib.h"
#include <math.h>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // 定数の定義
    const int WIDTH = 960, HEIGHT = 640; // ウィンドウの幅と高さのピクセル数
    const int GRAY = GetColor(128, 128, 128); // よく使う色を定義

    SetWindowText("三角関数を用いたエフェクト"); // ウィンドウのタイトル
    SetGraphMode(WIDTH, HEIGHT, 32); // ウィンドウの大きさとカラービット数の指定
    ChangeWindowMode(TRUE); // ウィンドウモードで起動
    if (DxLib_Init() == -1) return -1; // ライブラリ初期化 エラーが起きたら終了
    SetBackgroundColor(0, 0, 0); // 背景色の指定
    SetDrawScreen(DX_SCREEN_BACK); // 描画面を裏画面にする

    const int RADIUS = 300; // 円運動の半径
    int degree = 0; // 角度を数える変数

    while (1) // メインループ
    {
        ClearDrawScreen(); // 画面をクリアする

        // 軸と円周を描く
        DrawLine(WIDTH / 2, 0, WIDTH / 2, HEIGHT, GRAY); // y軸
        DrawLine(0, HEIGHT / 2, WIDTH, HEIGHT / 2, GRAY); // x軸
        DrawCircle(WIDTH / 2, HEIGHT / 2, RADIUS, GRAY, FALSE); // 半径RADIUSの円

        degree++; // 角度を1度ずつ増やしていく
        double radian = M_PI * degree / 180; // ラジアンに変換する
        DrawFormatString(0, 0, GRAY, "degree = %d", degree); // 度の値を表示
        DrawFormatString(0, 20, GRAY, "radian = %f", radian); // ラジアンの値を表示
     
        SetDrawBlendMode(DX_BLENDMODE_ADD, 32);//加算によるブレンド
        for (int a = 0;a < 360;a += 45)//180度ずらして2つの物体を動かす
        {
            for (int i = 10;i <= 180;i += 3)//複数の物体の円運動
            {
                int x = WIDTH / 2 + RADIUS * cos(M_PI * (degree + i + a) / 180) * (180-i) / 80;
                int y = HEIGHT / 2 + RADIUS * sin(M_PI * (degree + i + a) / 180) * (180-i) / 240;
                for (int s = 5;s < 50;s += 5)DrawCircle(x, y, s * i / 120, GetColor(24,16,96), TRUE);
            }
        }
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//ブレンドモードを解除
        // 座標計算
        int x = RADIUS * cos(radian); // 数学のx座標
        int y = RADIUS * sin(radian); // 数学のy座標
        int cx = x + WIDTH / 2; // コンピューター画面のx座標
        int cy = y + HEIGHT / 2; // コンピューター画面のy座標
        DrawBox(cx - 10, cy - 10, cx + 10, cy + 10, GetColor(0, 255, 255), TRUE); // 円運動する物体

        ScreenFlip(); // 裏画面の内容を表画面に反映させる
        WaitTimer(16); // 一定時間待つ
        if (ProcessMessage() == -1) break; // Windowsから情報を受け取りエラーが起きたら終了
        if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break; // ESCキーが押されたら終了
    }

    DxLib_End(); // ＤＸライブラリ使用の終了処理
    return 0; // ソフトの終了
}