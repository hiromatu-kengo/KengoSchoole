#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	//５人パーティーのHPを管理
	int playerHp[5];

	playerHp[0] = 10;
	playerHp[1] = 20;
	playerHp[2] = 30;
	playerHp[3] = 40;
	playerHp[4] = 50;

	printf("0 : %d\n", playerHp[0]);
	printf("1 : %d\n", playerHp[1]);
	printf("2 : %d\n", playerHp[2]);
	printf("3 : %d\n", playerHp[3]);
	printf("4 : %d\n", playerHp[4]);
	printf("\n");

	//添字を変数にすることができる
	int damagePlayer = 2;  //ダメージを受けるプレイヤーの番号

	playerHp[damagePlayer] -= 10;

	//for文を使ってまとめて処理
	for (int i = 0; i < 5; i++)
	{
		printf("%d : %d\n", i, playerHp[i]);
	}

	//全体ダメージ
	printf("\n");
	printf("全員１０ダメージをうけた\n");
	for (int i = 0; i < 5;i++)
	{
		playerHp[i] -= 10;
	}
	for (int i = 0;i < 5;i++)
	{
		printf("%d : %d\n", i, playerHp[i]);
	}
		
	return 0;
}