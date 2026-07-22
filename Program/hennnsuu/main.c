#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		
	//int型　整数を入れるためのデータ型
	//大体-21億～+21億の間の数値を保全できる
	int intData;
	intData = -1600000000;
	printf("INT:%d\n", intData);

	//doubile型　小数点以下の数値を入れることのできるデータ型
	double doubleData;
	doubleData = 12.345;
	printf("DOUBLE:%F\n", doubleData);

	//float型　小数点以下の数値を入れることのできるデータ型
	float floatData;
	floatData = 12.345f;  //float型に直接数値を代入するときは数値のあとにfをつける
	printf("FLOAT:%f\n", floatData);

	//char型　文字を1文字入れること御できるデータ型　半角1文字を入れる
	char charData;
	charData = 'a';  //半角1文字をシングルクオーテーションで囲う
	                //' shiftを押しながらキーボードの7で入力
	printf("CHAR:%c", charData);

	return 0;
}