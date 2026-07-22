#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	printf("wr\n");

	/*

	//変数に数値を保存する
	//変数:数値を記憶するための領域

	//変数を使うには宣言を行う必要がある
	//宣言方法:データ型　変数名;
	//データ型→int　とか　floatとか
	//変数名→自分でもわかりやすい名前を付ける
	int hp;

	//変数に数値を代入する
	//= 演算子を使って変数に値を入れる
	hp = 100;

	//printfを使って変数の中身を表示する
	printf("000:HP:%d\n", hp);

	//四則演算
	hp = 100 + 8;
	printf("001:HP:%d\n", hp);
	hp = 100 - 8;
	printf("002:HP%d\n", hp);

	hp = 9 * 8;
	printf("003:HP:%d\n", hp);
	hp = 125 / 10;
	printf("004:HP:%d\n", hp);
	hp = 125 % 10;
	printf("005:HP:%d\n", hp);

	*/

	//変数の型

	/*
	//int型　整数を入れるための変数
	int intvalue = 128;

	printf("intValue = %d\n", intvalue);

	//double型　小数点以下の数値を含む値を入れるための変数
	double doubleValue = 12.8;
	//printfで少数を表示したい場合は%fを使用する
	printf("doubleValue = %f\n", doubleValue);
	//print("doubleValue = %d\n", doubleValue); //%dでは正しく表示されない
	//float型　少数を入れるための変数
	//ゲームプログラムでは大体doubleではなくfloatが使われる
	//doubleは処理が重く、メモリの消費も大きいため
	float floatValue = 25.6f;//floatに値を入れる問いは数値の最後にfをつける
	printf("floatValue = %f\n", floatValue);

	//char型　半角を一文字入れるための変数
	char charValue = 'a'; // シングルクォーテーションで囲む
	// printfで文字を一文字表示したい場合は%cを使う
	printf("charValue = %c\n", charValue);
	*/

	int a = 128;

	printf("-a = %d\n", -a);

	//インクリメント(++)
	a++;
	printf("a = %d\n", a);

	//デクリメント(--)
	a--;
	printf("a = %d\n", a);

	int hp = 128;
	int enemyAttack = 16;
	printf("残りのHP:%d\n", hp);

	hp = hp - enemyAttack;
	printf("%dダメージを受けた\n", enemyAttack);
	printf("残りHP:%d\n", hp);

	//変数自身の値を変更したい場合は複合代入演算子を使う
	hp -= enemyAttack;
	printf("%dダメージを受けた\n",enemyAttack);
	printf("残りHP:%d\n", hp);

	return 0;
}