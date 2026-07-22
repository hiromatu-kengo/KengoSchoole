#include<stdio.h>
#include<windows.h>

void dispNum(int num)
{
	printf("disp = %d\n", num);
}

int main()
{
	SetConsoleOutputCP(65001);		

	int num = 123;
	dispNum(num);

	return 0;
}