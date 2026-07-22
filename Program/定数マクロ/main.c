#include<stdio.h>
#include<windows.h>

//定数（変化しない数字）を定義する
//C言語では定数マクロを使用して定数を定義する

//文法
//#define 定数名　定数

#define PLAYER_NUM 5

//C言語のマクロはアッパースネークケースで定義されることが多い
//変数と違う命名規則を使うことでこれが
//変数なのか定数なのかが一目でわかる

int main()
{
	SetConsoleOutputCP(65001);

	int num;  //変数

	int playerHp[PLAYER_NUM];

	//HPの初期設定
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		playerHp[i] = 120;
	}

	printf("全体攻撃を受けた\n");
	//全員のHPを減らす
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		playerHp[i] -= 20;
	}

	printf("残りHP\n");
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		printf("[%d]:%d", i, playerHp[i]);
		if (playerHp[i] <= 0)
		{
			printf("死");
		}
		printf("\n");
	}

	return 0;
}