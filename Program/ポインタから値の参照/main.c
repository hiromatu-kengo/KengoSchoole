#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	int a;
	int* ptA;

	a = 3;
	ptA = &a;

	printf("変数aのアドレスは%pです\n",&a);
	printf("ポインタptAの値は%pです\n", ptA);

	printf("変数aの値は%dです\n", a);

	//文法:
	//*ポインタ　*ptA
	//でそのポインタが参照してい変数の中身を取得する
	print("ptAに格納されている値は%dです\n", *ptA);

	//&だったっけ？ *だったっけ？
	//となるのは仕方ない　慣れよう

	return 0;
}