#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

//	char str[] = "G_Gengo";
	
//	char* str = "C_Gengo";
//	printf(str);

	//C言語で文字列の配列を準備する方法
	char* str[] =
	{
		"tanaka",
		"sato",
		"suzuki"
	};
	for (int i = 0;i < 3;i++)
	{
		printf("%s\n", str[i]);
	}

	return 0;
}