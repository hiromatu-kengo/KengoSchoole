#include<stdio.h>
#include<windows.h>

//ソースコードの中に直接数値を埋め込まないこと
//ソースコードに直接書かれた数値のことを【マジックナンバー】と呼ぶ

//数値を定数かしてそれを使用する
//文法
//#define 定数 数値
//定数マクロはアッパースネークケースで名前を付ける
//・定数は大体ソースコードの先頭で行う
#define PLAYER_NUM 3	//プレイヤーの数
#define DEFAULT_HP 200  //初期HP

//なぜ定数化するのか？
//・同じ意味の数値を1か所で管理する修正を容易にする
//・数値に意味を持たせる　その値にする根拠を英語で表現する

//いったん数値にして後で数値化しよう!
//→後、はいつまでたってもやってこないので最初から定数化しよう!

int main()
{
	SetConsoleOutputCP(65001);		

	//プレイヤーのHP
	int playerHp[PLAYER_NUM];

	//HPの初期化
	for (int i = 0; i < PLAYER_NUM;i++)
	{
		playerHp[i] = DEFAULT_HP;
	}

	//HPの表示
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		printf("[%d] : %d\n", i, playerHp[i]);
	}

	return 0;
}