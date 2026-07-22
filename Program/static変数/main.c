#include<stdio.h>
#include<windows.h>

void Func(int add)
{
	//static 変数
	//static変数はmainが呼ばれるタイムんぐで生成され初期化される
	//関数を抜けてもメモリ以上から削除されない
	//削除されるのはプログラム終了時(main終了時)
	static int count = 0;
	//int count = 0;
	count++;

	int num = 10;
	num += add;
	printf("num = %d\n", num);

	printf("Func関数は%d回呼び出されました\n", count);
}

int main()
{
	SetConsoleOutputCP(65001);

	Func(100);
	Func(200);

	return 0;
}