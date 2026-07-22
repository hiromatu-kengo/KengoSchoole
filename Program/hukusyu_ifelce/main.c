#include<stdio.h>
#include<windows.h>

#include<stdlib.h>
#include<time.h>

int main()
{
	SetConsoleOutputCP(65001);	

	//rand()の値をいい感じにランダムにする
	unsigned int seed = (unsigned int)time(NULL);
		srand(seed);

	int attack = rand() % 80;
	int magic = rand() % 80;

	int bossHp = rand() % 101 + 20;		//ボスのHPは20~120
	//rand() % 101		0~100までのランダムな値を生成
	//+20				0~100を20~120に変換する

	//printf("PLAYER:%d vs %d:BOSS\n", attack, bossHp);
	printf("PLAYER:\n");
	printf("攻撃:%d\n",attack);
	printf("魔法:%d\n",magic);
	printf("\n");
	printf("BOSS HP:%d\n",bossHp);
	printf("\n");

	/*プレイヤーの攻撃力がボスのHPより多ければ物理で倒す
	　物理では倒せないけどプレイヤーの魔力がボスのHPより多ければ魔法で倒す
	 　どちらも満たしていなければ死*/
	if (attack >= bossHp)
	{
		printf("ボスを吹き飛ばした！\n");
	}
	else if (magic >= bossHp)
	{
		printf("ボスを焼き尽くした");
	}
	else
	{
		//if分の中にif文を書くことができる

		/*1/2の確率で逃げる
		 rand()を使って2つの数字を生成できればそれを使って判定できる
		 ->　rand()関数を使って0 か 1　を生成する
			　0奈良逃走成功とする*/
		if (rand() % 2 == 0)
		{
			printf("逃走成功\n");
		}
		else
		{
			printf("～～死～～\n");
		}
	}

	/*
	//プレイヤーの攻撃でボスの攻撃を0にできればボスを倒せる
	//プレイヤーの攻撃がボスのHP以上ならボスを倒せる
	if (attack >= bossHp)
	{
		printf("ボスを撲殺！\n");
	}
	else
	{
		printf("～～死～～\n");
	}
	*/

	return 0;
}