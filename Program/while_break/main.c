#include<stdio.h>
#include<windows.h>

#include<stdlib.h>
#include<time.h>
int main()
{
	SetConsoleOutputCP(65001);		

	unsigned int seed = (unsigned int)time(NULL);
	srand(seed);

	int enemyHp = 100;
	int playerMp = 9;

	//敵キャラクターに対して連続で魔法攻撃を行う
	//魔法1回のダメージ量は10でMPを2消費する

	//敵を倒すかMPが0になったら攻撃終了

	//終了条件				　繰り返す条件			　　プログラム
	//敵を倒したら攻撃終了→　enemyHpが0より大きい→ 　 enemyHp > 0
	//MPが0で攻撃終了→		　playerMpが2以上→　       playerMp >= 2

	//繰り返し条件を両方満たしている必要がある
	//while (enemyHp > 0 && playerMp >= 2)
	while (enemyHp > 0)
	{
		//消費MPをらんだむにする
		// 消費MP以上のMPがないと攻撃中断
		
		//ここで消費MPを決定して足りなければ終了とできると楽
		// ループ処理強制終了するのがbreak文

		//消費MPをランダムに決定して、MPが足りていなければ終了
		int useMp = rand() % 5;//0~4消費MPをランダムに決定
		if (playerMp < useMp)//MPが足りていなければ
		{
			printf("MPが足りない！\n");
			break;//ループが強制終了
		}
		
		//敵に対して魔法攻撃を行う
		enemyHp -= 10;
		playerMp -= useMp;

		printf("魔法を行った！10ダメージ！\n");
		printf("敵のHP:%d\n",enemyHp);
		printf("残りMP:%d\n",playerMp);
	}

	return 0;
}