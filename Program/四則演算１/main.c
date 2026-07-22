#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		
	//プログラムで足し算、引き算を行う
	printf("1 + 2 = %d\n", 1 + 2);
	printf("3 - 1 = %d\n", 3 - 1);

	//printf(" %d\n", 1 + 2);
	//printf(" %d\n", 3 - 1);

	printf("数値を直接指定して表示できる %d\n", 1024);

	return 0;
}