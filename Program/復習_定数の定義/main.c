#include<stdio.h>
#include<windows.h>

#define TBL_SIZE 5

int main()
{
	SetConsoleOutputCP(65001);		

	int tbl[TBL_SIZE];
	for (int i = 0;i < TBL_SIZE;i++)
	{
		tbl[i] = i * 10;
	}

	for (int i = 0; i < TBL_SIZE;i++)
	{
		printf("tbl[%d] - %d\n", i, tbl[i]);
	}

	return 0;
}