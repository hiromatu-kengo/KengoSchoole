#include<stdio.h>
#include<windows.h>

#include<stdlib.h>
#include<time.h>

int main()
{
	SetConsoleOutputCP(65001);		
	
	/*おみくじのプログラム
			数値
	　大吉	0
	  中吉	1
	  吉	2
	  凶	3
	  */
	unsigned int seed = (unsigned int)time(NULL);
	srand(seed);

	//ランダムに運勢を決定
	int result = rand() % 4;
	/*
	if (result == 0)
	{
		printf("大吉\n");
	}
	else if (result == 1)
	{
		printf("中吉\n");
	}
	else if (result == 2)
	{
		printf("吉\n");
	}
	else 
	{
		printf("凶\n");
	}
	*/

	switch(result)  //resultの中身が何か、出条件分岐を行う
	{
		case 0: // セミコロンじゃなくてコロン
			//resultが0の場合の処理を書く
			printf("大吉\n");
			break;  //result=0の時の処理終了
		case 1:
			printf("中吉\n");
			break;
		case 2:
			printf("吉\n");
			break;
		case 3:
			printf("凶\n");
			break;
			//caseがそんざいしないばいはここにくる
		default:
			printf("存在しない数値を検知");
			break;
	}

	return 0;
}