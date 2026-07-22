#include"DxLib.h"
/*
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetWindowText("RGB値による色指定");
	SetGraphMode(600, 66, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)return -1;
	SetBackgroundColor(0, 0, 0);
	ClearDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawCircle(300, 220, 200, GetColor(255, 0, 0), TRUE);
	DrawCircle(200, 380, 200, GetColor(0, 255, 0), TRUE);
	DrawCircle(400, 380, 200, GetColor(0, 0, 255), TRUE);
	WaitKey();
	DxLib_End();
	return 0;
}
*/