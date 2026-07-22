#include<stdio.h>
#include<windows.h>

void funcSwap(int* ptx, int* pty)
{
	int tmp;
	tmp = *ptx;
	*ptx = *pty;
	*pty = tmp;
	return;
}

int main()
{
	SetConsoleOutputCP(65001);		

	int a = 3;
	int b = 5;

	//変数の値を入れ替えたいとき

	/*
	うまくいかない
	a = b;
	b = a;
	*/
	int temp = a;//いったんaの値をtempに避難させる
	a = b;//aがbになる
	b = temp;//避難させておいたaのtempを使用する

	printf("変数aの値は%dです\n", a);
	printf("変数bの値は%dです\n", b);

	printf("functionSwap関数により、変数aと変数bの当たりを入れ替えます\n");

	funcSwap(&a, &b);
	printf("変数aの値は%dです\n", a);
	printf("変数bの値は%dです\n", b);
	

	return 0;
}