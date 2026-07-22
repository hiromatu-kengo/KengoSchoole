#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);

	char str[] = "C_Gengo";

	printf(str);

	//printfを使って数値を表示する
	//%d　整数
	//%f 浮動小数点数
	//%c １文字

	//↑と同じようにな感覚で文字列に置き換えることもできる
	//%s 文字列
	printf("文字列は{%s}デス\n", str);

	return 0;
}