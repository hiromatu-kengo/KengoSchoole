#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	int enemyHp = 200;

	printf("5回線族攻撃!\n");
	//n回処理繰り返したい場合
	//for(int i = 1;i<=5;i++)
	//のような書き方は非推奨

	for (int i = 0;i < 5;i++) //この書き方で覚える
	{
		enemyHp -= 20;
		printf("20ダメージ！ 残りHP%d\n", enemyHp);
	}

	return 0;
}