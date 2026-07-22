#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	printf("test\n\n");
	printf("日本語表示されるかテスト\n");
	return 0;
}