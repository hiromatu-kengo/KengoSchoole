#include<stdio.h>
#include<windows.h>

//グローバル変数は使わない
//就活作品で使っているとアウト
int a = 1;

void Func(void)
{
	printf("Func : a = %d\n", a); //グローバル変数の中身
}

int main()
{
	SetConsoleOutputCP(65001);	

	int a = 2; //名前は同じだがFuncないのaとは無関係

	//よりスコープの内側の変数が使われる
	printf("main : a = %d\n", a); //ローカルの中身
	Func();

	return 0;
}