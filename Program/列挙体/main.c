#include<stdio.h>
#include<windows.h>

//列挙体
//職業を定義する

//自分でJobTypeという名前のデータ型を定義した
enum JobType
{
	HERO,    //勇者
	WARRIOR, //戦士
	PLAYBOY, //遊び人
	HEALER,  //僧侶
	MAGIC    //魔法使い
};

struct Player
{
	enum jobType job;

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
	case HERO:
		printf("勇者\n");
		break;
	case WARRIOR:
		printf("戦士\n");
		break;
	case PLAYBOY:
		printf("遊び人\n");
		break;
	case HEALER:
		printf("僧侶\n");
		break;
	case MAGIC:
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
	/*
	//作ったJobTypeをデータ型として待つ変数を作成
	enum JobType job;
	//列挙体をデータがとして待つ変数には
	//列挙体の要素のいずれかが代入可能
	job = HERO;
	job = MAGIC;
	//JobTypeは実は内部的にはint型
	//なので↓のような代入もできるが
	//避けるようにする
	job = 10;
	*/
	struct Player party[4] =
	{
		{WARRIOR ,400,0}, //party2[0]の初期化
		{HERO    ,300,50}, //party2[1]の初期化
		{HEALER  ,200,150}, //party2[2]の初期化
		{MAGIC   ,150,200}  //party2[3]の初期化
	};
	for (int i = 0;i < 4;i++)
	{
		DispPlayerptr(&party[i]);
	}

	return 0;
}