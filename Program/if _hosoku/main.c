#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	int a = -1;

	//条件を満たしたら、if(条件)のあとの1行のみ実行される

	//処理が１行なら{}は使わなくても大丈夫？
	//答えはno慣れるまでは{}を使う
	
	//教科書
	if (a < 0)
		printf("aの値は負の値です\n");
	//printf("a葉の負の値？") //実行される？されない？


	//授業
	if (a < 0)
	{
		//{}の中身を1行扱いして複数処理を実行する
		printf("aの値は負の数です\n");
	}

	printf("aの値は%dです\n", a);

	return 0;
}