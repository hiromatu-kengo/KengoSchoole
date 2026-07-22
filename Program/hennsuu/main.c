#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		
	//変数
	int playerHp;

	//変数への値の代入

	playerHp = 200;

	//printfを使って変数の中身を表示

	printf("HP%d\n", playerHp);

	//代入を複数回行った場合、値は上書きされる
	playerHp = 300;
	printf("HP%d\n", playerHp);

	//新しく変数testを作成
	int test;

	//変数にほかの辺の値を代入する
	//右辺の変数の中身が左辺の変数に代入される
	test = playerHp;

	printf("TEST:%d\n", test);

	//intがたの変数に小数点以下を含む数値を代入するとどうなるか
	test = 100.5;
	printf("TEST:%d\n", test);
	//testの中には100が入っている
	//int型は整数を入れるための変数
	//整数を入れるための変数に小数点以下を含む数値を代入しようとすると
	//小数点以下は切り捨てられる

	return 0;
}