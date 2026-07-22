#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		
	
	//変数の宣言
	//データ型　変数名;
	//変数名は基本的に英語をつける
	int hp;

	//変数に値を代入
	// = 演算子を使用して値を代入する
	hp = 128;

	//printfを使って変数の中身を表示
	printf("HP: %d\n", hp);

	//変数には
	//整数 : int型
	//小数点以下の値を持つ数値 : double型　floatに比べて誤差が小さい　低速、メモリ消費大
	//小数点以下の値を持つ数値 : float型　誤差が出る　高速でメモリ消費が少ない
	//半角文字を1文字入れる : char型
	double doubleData;
	doubleData = 12.345;
	printf("doubleData = %f\n", doubleData);

	float floatData;
	//floatData = 54.321;   doubleのデータをfloatの変数に代入しようとしているdouble->floatの変換に時間がかかる
	floatData = 54.321f;   //数値のあとにfをつけることで最初からfloat型として扱える
	printf("floatData = %f\n", floatData);

	char charData;
	charData = 'a'; //半角文字を1文字扱い場合は''でくくる
	printf("charData = %c\n", charData);

	return 0;
}