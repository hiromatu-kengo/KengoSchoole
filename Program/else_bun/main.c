#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	int num = 777;

	// numが7の倍数なら"XXは7の倍数！\n"と表示する(XXはnumの値)

	if (num % 7 == 0)
	{
		//条件を満たす
		printf("%dは7の倍数！\n",num);
	}
	else
	{
		//条件を満たさない
		printf("%dは7の倍数ではない！\n", num);
	}

	int attack = 90;

	//攻撃力が１００以上ならボスを倒せる	"ボスを倒した！\n"
	// 100未満だけど80以上なら逃げる		"逃げ切った...\n"
	//条件を満たさなったら死亡する			"死亡した...\n"

	if (attack >= 100)
	{
		printf("ボスを倒した！\n");
	}
	else if (attack >= 80)
	{
		printf("逃げ切った...\n");
	}
	else
	{
		printf("死亡した...\n");
	}

	//ありがちなミス
	if (attack >= 80)
	{
		printf("逃げ切った...\n");
	}
	//attack>=80ならここまで到達しない
	else if (attack >= 100)
	{
		printf("ボスを倒した！\n");
	}
	else
	{
		printf("死亡した...\n");
	}

	/*if ()のあとのブロックを開始{を
	　条件式と同じに各流派もあり
	 　どちらでもよい
	  */
	if(attack == 100){
	
	}

	return 0;
}