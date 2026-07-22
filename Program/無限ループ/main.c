#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	//意図しない無限ループはバグの原因になるが
	//わざと無限ループさせることもある

	int count = 0;
	//条件部分に常に満たす条件を書いて明示的な無限ループであることを示す
	while (1)
	{
		printf("無限ループ\n");

		count++;

		//特定の条件を満たしたらループを抜ける
		if (count >= 65536)break;
	}

	return 0;
}