#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	//n買い繰り返す場合の書き方
	//基本的にこの書き方をする
	for (int i = 0; i < 10; i++)
	{
		printf("10回繰り返す\n");
	}

	//場合によっては初期化やループ条件を
	//ほかの書き方にしたほうが楽
	for (int i = 1; i <= 10; i++)
	{
		printf("%d回目の繰り返し処理\n", i);
	}

	//1~100の間の偶数をすべて表示する
	/*for (int i = 1; i <= 100; i++)
	{
		if (i % 2 == 0)//偶数なら=2で割り切れる
		{
			printf("%d\n", i);
		}
	}
	*/

	//書き方を工夫
	for (int i = 2; i <= 100;i += 2)
	{
		printf("%D\n", i);
	}

	//降順で数字を表示する
	//for(int i = 10; i <=1; i--) //ループ条件ミス　1回もループしない
	for (int i = 10; i >= 1; i--)
	{
		printf("%d\n", i);
	}

	printf("1~100の間の数を表示する\n");
	printf("ただし、２の倍数\n");
	printf("　　　　３の倍数\n");
	printf("　　　　５の倍数\n");
	for (int i = 1;i <= 100;i++)
	{
		//２の倍数でもなく		(i % 2) != 0
		//３の倍数でもなく		(i % 3) != 0
		//５の倍数でもなく		(i % 5) != 0
		//数値のみ表示する		↑の条件すべて満たしたら表示
		if ((i % 2) != 0 && (i % 3) != 0 && (i % 5) != 0)
		{
			printf("%d\n", i);
		}
	}

	//continue文を使ってもう少し見やすく
	for (int i = 1;i <= 100;i++)
	{

		if (i % 2 == 0) //偶数の場合
		{
			continue;
		}
		if (i % 3 == 0)//３の倍数
		{
			continue;
		}
		if (i % 5 == 0) //５倍数の場合
		{
			continue;
		}

		//最終的にはこんな感じの書き方に収まる
		if (i % 2)continue;
		if (i % 3)continue;
		if (i % 5)continue;

		printf("%d\n", 1);
		
	}

	return 0;
}