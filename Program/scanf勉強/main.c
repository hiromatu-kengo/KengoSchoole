#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	//入力された文字１文字を受け取るための
	//getchar()関数が存在する
	char c;
	printf("<キーボードから整数を入力>");
	c = getchar();
	printf("入力したもじ%c\n", c);

	//scanf_s関数を使って
	//キーボードから直接数値を入力できる

	int num = 0;

	printf("<キーボードから整数を入力>");

	//第1引数 ： 整数型のデータを入力したい場合は"%d"
	//　　　※　\nを入れない
	//第２引数　:　データを受け取るための変数＋その前に＆
	//　　　　　＆を忘れない
	scanf_s("%d", &num);
	printf("入力した値%d\n", num);

	//浮動小数点数にキーボードから値を入力する
	float value = 0.0f;
	printf("<キーボードから整数を入力>");

	//少数を入力したい場合は第１引数が"%f"
	//第２引数は&値を入れた変数めい
	acanf_s("%f", &value);
	printf("入力した値%f\n",value);

	//文字を１文字 "%c"
	
	/*
	char c;
	printf("<キーボードから整数を入力>");
	acanf_s("%c", &c);
	printf("入力した値%c\n", c);
	*/

	

	return 0;
}