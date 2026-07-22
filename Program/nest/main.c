#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	int attack = 50;
	int hp = 128;

	if (attack >= 100)
	{
		printf("ボスを倒した！\n");
	}
	else
	{
		//HPが１００以上なら逃げ切る
		//そうじゃないなら死

		//if分のあとのブロックの中にifぶんをかくこともできる
		if (hp >= 100)
		{
			printf("にげきった...\n");
		}
		else
		{
			printf("　死　\n");
		}
	}

	return 0;
}