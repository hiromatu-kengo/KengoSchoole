#include<stdio.h>
#include<windows.h>

struct CHARACTER
{
	char name[7];
	int life;
	int strength;
	int defense;
};


int main()
{
	SetConsoleOutputCP(65001);	

	struct CHARACTER player = { "マーズ",1000,500,300 };
	printf("プレイヤーのパラメーターを出力します。\n");
	printf("名前%s\n", player.name);
	printf("体力%d\n", player.life);
	printf("腕力%d\n", player.strength);
	printf("防御力%d\n", player.defense);


	return 0;
}