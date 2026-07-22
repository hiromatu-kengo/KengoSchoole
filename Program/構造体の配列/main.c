#include<stdio.h>
#include<windows.h>

struct Player
{
	int job;//0：勇者１：戦士２：僧侶３：魔法使い

	int hp;
	int mp;
};

void DispPlayerPtr(struct Player* pPlayer)
{
	//構造体のポインタから各メンバーにアクセスする場合、
	// . ではなく[->]を使用する
	// ->は[アロー演算子]と呼ぶ
	switch (pPlayer->job)
	{
	case 0:
		printf("勇者\n");
		break;
	case 1:
		printf("戦士\n");
		break;
	case 2:
		printf("僧侶\n");
		break;
	case 3:
		printf("魔法使い\n");
		break;
	default:
		printf("存在しない職業\n");
		break;
	}
	printf("HP: %d\n", pPlayer->hp);
	printf("MP: %d\n", pPlayer->mp);
}

int main()
{
	SetConsoleOutputCP(65001);		

	//構造体の配列を宣言する
	struct Player party[4];

	//配列のそれぞれの要素に対して値を代入していく
	party[0].job = 1;
	party[0].hp = 400;
	party[0].mp = 0;

	party[1].job = 0;
	party[1].hp = 300;
	party[1].mp = 50;

	party[2].job = 2;
	party[2].hp = 200;
	party[2].mp = 100;

	party[3].job = 3;
	party[3].hp = 1500;
	party[3].mp = 200;

	for (int i = 0; i < 4; i++)
	{
		DispPlayerPtr(&party[i]);
	}

	printf("*********************\n");

	//構造体の配列の初期化
	struct Player party2[4] =
	{
		{0,100,10}, //party2[0]の初期化
		{1,100,10}, //party2[1]の初期化
		{2,100,10}, //party2[2]の初期化
		{3,100,10}  //party2[3]の初期化
	};
	for (int i = 0;i < 4;i++)
	{
		DispPlayerptr(&party2[i]);
	}

	return 0;
}