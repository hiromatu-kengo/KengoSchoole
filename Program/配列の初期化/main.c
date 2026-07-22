#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	/*
	int playerHp[4];  // 65,43,22,104

	playerHp[0] = 65;
	playerHp[1] = 43;
	playerHp[2] = 22;
	playerHp[3] = 104;
	*/

	int hp = 123; //これがやりたい

	int playerHp[4] = { 65,43,22,104 };

	for (int i = 0;i < 4;i++)
	{
		printf("HP%d : %d\n", i, playerHp[i]);
	}

	//配列の要素数の省略
	//初期化の時の要素数が配列の要素数となる
	int playerMp[] = { 123,456,789 };
	printf("MP%d ; %d\n", 2, playerMp[2]);

	//配列の要素数と初期化子の数が合わない場合
	//入れる要素のない場所には0が入る
	int playerAttack[4] = { 123,456,789 };
	for (int i = 0;i < 4;i++)
	{
		printf("Attack%d : %d\n", i, playerAttack[i]);
	}

	//要素数よりも初期化しが多い場合はエラー
	//int playerSpeed[4] = {123,456,789,999,888};

	return 0;
}