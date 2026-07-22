#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<windows.h>

/*
struct Character
{
	char name[7];
	int life;
	int strength;
	int defense;
};
*/
/*
struct Character
{
	char name[11];
	int life;
	int strength;
	int defense;
};
struct Character enemy[3] =
{
	{"suraimu",200,80,30},
	{"sukeruton",500,240,120},
	{"doragon",3000,800,300}
};
*/
/*
struct Character
{
	char name[7];
	int life;
	int strength;
	int defense;
};
*/

int main()
{
	SetConsoleOutputCP(65001);		

	/*char title[12] = "Holy Dragon";
	printf("ゲームタイトルは「%s」\n", title);
	*/
	/*	char title[12] = "Holy Dragon";
	title[4] = '+';
	for (int i = 0; i < 11; i++)printf("%c,", title[i]);*/
	/*char monster[3][10] = {"Slime", "Ghost", "Vampire"};
	for (int i = 0;i < 3;i++)
	{
		printf("敵%dの名前は「%s」\n", i, monster[i]);
	}
	*/
	/*char txt[11];
	printf("※要素数11の配列は半角10文字まで、全角は5文字まで代入できます\n");
	printf("あなたの名前は?\n");
	scanf("%s", txt);
	printf("%sよ、いよいよ、冒険の旅に出発じゃ。", txt);
	*/
	/*char str1[20] = "伝説の";
	char str2[] = "勇者";
	char str3[] = "sword";
	char str4[] = "shield";
	char str5[] = "邪悪な魔竜を倒す冒険の旅へ";
	char str6[30];

	printf("「%s」と「%s」をstr1に連結します。\n", str1, str2);
	printf("連結前のstr1の長さは%dです。\n", strlen(str1));
	strcat(str1, str2);
	printf("連結した模試は「%s」\n", str1);
	printf("連結後のstr1の長さは%dです。\n", strlen(str1));

	int c = strcmp(str3, str4);
	printf("「%s」と「%s」を比較した結果は%d。\n", str3,str4,c);

	printf("初期値を未代入のstr6に「%s」をコピーします。\n", str5);
	strcpy(str6, str5);
	printf("str6の中身は「%s」になりました。", str6);
	*/
	/*
	struct Character player = { "ma-zu",1000,500,300 };
	printf("プレイヤーのパラメーターを出力します\n");
	printf("名前 %s\n", player.name);
	printf("体力 %d\n", player.life);
	printf("腕力 %d\n", player.strength);
	printf("防御力 %d\n", player.defense);
	*/
	/*
	for (int i = 0;i < 3; i++)
	{
		printf("%s\n", enemy[i].name);
		printf("体力%d\n", enemy[i].life);
		printf("腕力%d\n", enemy[i].strength);
		printf("防御力%d\n", enemy[i].defense);
		printf("-----------------\n");
	}
	*/
	/*
	struct Character player;
	strcpy(player.name, "ma-zu");
	player.life = 1000;
	player.strength = 500;
	player.defense = 300;
	printf("名前 %s\n", player.name);
	printf("体力 %d\n", player.life);
	printf("腕力 %d\n", player.strength);
	printf("防御力 %d\n", player.defense);
*/
	/*
	for (int i = 0; i < 5;i++)
	{
		int r = rand();
		printf("敵に%dのダメージを与えた!\n", r);
	}
	*/

	return 0;
}