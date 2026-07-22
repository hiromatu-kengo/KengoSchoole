#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);	

	//for文
	//繰り返し大会数が決まっているばあい、for文を使う

	for (int i = 0; i < 10;i++)
	//for (int i = 1; i <= 10;i++)
	{
		//printf("繰り返し実行した処理");
		printf("%d回目の処理\n",i+1);

	}

	//while文
	//条件を満たすまで繰り返す場合、while文を使う
	int hp = 100;
	while (hp > 0)
	{
		hp -= 10;
		printf("while 残りHP : %d\n", hp);
	}

	/*do-while文
	条件を満たすまで処理を行う
	条件のチェックが繰り返し処理のあとに行われる
	->最初から条件を満たしていなくても最低1回処理が行われる
	*/

	hp = 0;
	do
	{
		hp -= 10;
		printf("do-while 残りHP : %d\n", hp);
	} while (hp > 0);		//最後にセミコロンが必要

	//for文の中にfor文を書くこともできる

	int loopNum = 10;
	for (int i = 0; i < loopNum; i++)
	{
		for (int j = 0;j < loopNum;j++)
		{
			printf("%d ", j);
		}
		printf("\n");
	}

	return 0;
}