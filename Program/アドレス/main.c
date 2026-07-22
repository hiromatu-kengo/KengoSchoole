#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	/*
	int num = 3;
	//printf("num = %d\n", num);
	//変数のアドレスを取得したい場合、
	//変数名の前に&をつける

	//printfのなかに%pと書いてその部分をアドレスに置き換える
	printf("変数numのアドレスは0x%pです\n", &num);
	*/

	int a;
	printf("変数aのアドレスは%pデス\n", &a);

	a = 3;
	printf("変数aの値は%dで、アドレスは%pデス\n",a, &a);

	a = 5;
	printf("変数aの値は%dで、アドレスは%pデス\n",a, &a);


	return 0;
}