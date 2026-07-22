#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		
	
	//キーボードから整数値を入力する

	int num = 0;
	printf("整数を入力してください>");
	scanf_s("%d", &num);
	printf("整数 : %d\n", num);

	//キーボードから浮動小数点数を入力する
	float value = 0.0f;
	printf("浮動小数点数を入力してください");
	scanf_s("%f", &value);
	printf("浮動小数点数 : %f\n", value);

	//キーボードから文字列を入力する
	char str[100];//どれくらいの長さが入力されるかわからないので大きめの配列に
	printf("文字列を入力してください >");
	//第１引数　: "%s"
	//第２引数 : 配列名　※前に&を付けない
	//第３引数 : 配列のサイズ
	scanf_s("%s", str,100);
	printf("文字列　: %s\n", str);

	return 0;
}