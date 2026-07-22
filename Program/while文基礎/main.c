#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	int enemyHp = 123;

	printf("敵が死ぬまで攻撃を繰り返す\n");

	/*構文
	  while(ループ条件)
	  {
	  　　繰り返し処理
	  }*/

	while (enemyHp > 0)
	{
		enemyHp -= 12;
		printf("残りHP : %d\n",enemyHp);
	}

	return 0;
}