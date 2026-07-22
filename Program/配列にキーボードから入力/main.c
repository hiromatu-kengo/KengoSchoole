#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	//int hp = 0;
	//scanf_s("%d", &hp);
	//printf("HP : %d\n", hp);

	int playerHp[4] = { 0,0,0,0 };

	printf("各プレイヤーのHPを入力してください\n");
	for (int i = 0;i < 4;i++)
	{
		printf("%d人目のHP >", i + 1);
		scanf_s("%d", &playerHp[i]);
	}

	for (int i = 0;i < 4;i++)
	{
		printf("%d人目 HP : %d \n", i + 1, playerHp[1]);
	}

	return 0;
}