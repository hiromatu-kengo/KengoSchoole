#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	int a = 3;
	int temp = 0;

	switch (a)
	{
	case 4:
		temp += 4;
		//break;	//breakをわざと外していること明示
	case 3:
		temp += 3;
		//break;
	case 2:
		temp += 2;
		//break;
	case 1:
		temp += 1;
		//break;
	default:
		break;
	}

	printf("temp = %d\n", temp);

	return 0;
}