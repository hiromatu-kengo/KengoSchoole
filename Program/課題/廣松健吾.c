#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	int num = 4649;

	//numが3の倍数なら"3の倍数!\n"と表示するプロブラム
	//条件分岐のところのみ書き換えればOK
	//ほかの部分を書き換えてもよし
	if (num / 3 == 0)
	{
		printf("3の倍数!\n");
	}


	return 0;
}