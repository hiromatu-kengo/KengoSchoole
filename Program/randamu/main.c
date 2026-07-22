#include<stdio.h>
#include<windows.h>

#include<stdlib.h>
#include<time.h>

int main()
{
	SetConsoleOutputCP(65001);

	//ゲームの開始時点で取得する
	unsigned int seed = 0;//シード値　ランダムを発生させるために使う
	//現在時刻(秒単位)を変数seedに代入する
	seed = (unsigned int)time(NULL);
	//seed値をもとにランダムな値を生成してもらう
	//起動時間は毎回変わるので毎回別のランダムな値が生成される
	srand(seed);

	/*==========================================================
	　rand()を使うときは最初に
	　unsigned int seed = (unsigned int)time(NULL);
	　srand(seed);
	　と書いておく
	 ==========================================================*/

	/*rand()を使っても毎回同じ順番で数値が出てしまう
	　↓
	　ゲームを起動するたびに変化する情報使用して
	  rand()がかえす値をランダムにする
	  */

	//6面ダイス　1~6のいずれかの目が出る
	int diceDeme = rand();
	//diceDeme = diceDeme % 6;
	//diceDemeを６で割った余をdiceDemeに代入
	diceDeme %= 6;	//0~5   0 1 2 3 4 5
	diceDeme += 1;  //		1 2 3 4 5 6

	printf("さいころの出目は%dでした\n", diceDeme);

	 diceDeme = rand() % 6 + 1;
	printf("さいころの出目は%dでした\n", diceDeme);

	diceDeme = rand() % 6 + 1;
	printf("さいころの出目は%dでした\n", diceDeme);

	return 0;
}