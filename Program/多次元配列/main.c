#include<stdio.h>
#include<windows.h>

#include<stdlib.h>
#include<time.h>

int main()
{
	SetConsoleOutputCP(65001);

	//ランダムをいい感じにする
	unsigned int seed = 0;
	seed = (unsigned int)time(NULL);
	srand(seed);

	//パズルゲーム

	//変数を柔軟に使おう
	//変数に入っている数値の使い方は自由

	/* kind:
	0:〇　赤
	1:▽　青
	2:△　緑
	3:□　黄色
	//それ以外の数値が入っていたらバグとする
	*/
	//int kind = 0;
	int lineData[6] = { 1,1,2,3,0,0 };//ぷよぷよ1列文

	for (int i = 0;i < 6;i++)
	{
		switch (lineData[i])
		{
		case 0:
			printf("〇");//\nなし
			break;
		case 1:
			printf("▽");
			break;
		case 2:
			printf("△");
			break;
		case 3:
			printf("□");
			break;
		default:
			printf("存在しない色のデータが入っています!");
			break;
		}
	}

	printf("\n");
	printf("\n");
	printf("\n");

	//ぷよぷよ
	//縦12 * 横6　子分のぷよのデータを配列でもちたい
	int puyoSetting[12][6];  //[6]の配列が[12]子並んだ配列を利用する

	puyoSetting[0][0] = 1;//添え字を２つ使って各要素にアクセスする
						  //どちらの添え字も使うことができる
	//ランダムにぷよをせっち
	for (int tate = 0;tate < 12;tate++)
	{
		for (int yoko = 0;yoko < 6;yoko++)
		{
			puyoSetting[tate][yoko] = rand() % 4;
		}
	}
	/*for (int i = 0; i < 6; i++)
	{
		puyoSetting[i] = rand() % 4; //0~3のランダムな値
	}
	*/
	//ランダムに設置されたぷよの表示
	for (int tate = 0;tate < 12;tate++)
	{
		//プ夜を１行表示
		for (int yoko = 0;yoko < 6;yoko++)
		{
			switch (puyoSetting[tate][yoko])
			{
			case 0:
				printf("〇");//\nなし
				break;
			case 1:
				printf("▽");
				break;
			case 2:
				printf("△");
				break;
			case 3:
				printf("□");
				break;
			default:
				printf("存在しない色のデータが入っています!");
				break;
			}
		}
		//改行
		printf("\n");
	}
	/*
	for (int i = 0;i < 6;i++)
	{
		switch (lineData[i])
		{
		case 0:
			printf("〇");//\nなし
			break;
		case 1:
			printf("▽");
			break;
		case 2:
			printf("△");
			break;
		case 3:
			printf("□");
			break;
		default:
			printf("存在しない色のデータが入っています!");
			break;
		}
	}
	*/
	printf("\n");

	return 0;
}