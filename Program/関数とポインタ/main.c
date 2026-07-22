#include<stdio.h>
#include<windows.h>

/*
//値渡し
void functionDouble(int x)
{
	x = x * 2;
	return;
}
*/

//ポインタ渡しに変更
//変数の中の数字ではなく、変数のアドレスを引数として受け取る
void fnctionDouble(int* ptx)
{
	*ptx = *ptx * 2;
	return;
}

int main()
{
	SetConsoleOutputCP(65001);		
	int a = 3;
	printf("変数aの値は%dです\n", a);

	printf("functionDouble関数により、変数aを2倍します\n");

	//functionDouble(a);
	functionDouble(&a);

	printf("変数aの値は%dです\n", a);


	return 0;
}