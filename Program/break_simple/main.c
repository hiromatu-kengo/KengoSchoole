#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		
	
	int enemyHp = 50;

	//10回連続攻撃
	for (int i = 0;i < 10;i++)
	{
		enemyHp -= 10;
		printf("HP:%d\n", enemyHp);
		if (enemyHp <= 0)
		{
			printf("敵を倒した");
			break;
		}
	}

	return 0;
}