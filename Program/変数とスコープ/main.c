#include<stdio.h>
#include<windows.h>

//関数の外で宣言されている変数
//[グローバル変数]
int a = 123;

void Func(void)
{
	//関数内部で宣言されている変数を
	//[ローカル変数]
	int b = 12;

	//printf("Func : a = %d\n", a);
	//printf("Func : b = %d\n", b);
}

int main()
{
	SetConsoleOutputCP(65001);		

	int c = 13; //ローカル変数

	//printf("main : a = %d\n", a);
	//printf("main : b = %d\n", b);
	
	Func();

	return 0;
}