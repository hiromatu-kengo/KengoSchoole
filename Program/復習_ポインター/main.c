#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	int num = 123;

	//変数numがメモリ上のどこに作られたかを確認したい
	//アドレスを取得したい変数名の前に&をつけて取得する
	//%pを使用して表示する
	printf("Addr : %p\n", &num);

	//アドレスを保存するための変数をポインタと呼ぶ

	//文法
	//あどれすを取得したい変数のデータ型*ポインタ名;

	int* pNum = &num;
	printf("pNum = %p\n", pNum);

	//int型以外でも同じようか書き方
	float val = 1.25;
	float* pVal = &val;

	//アドレス（ポインタ）が参照している先の値を取得sる
	printf("*pNum = %f");

	return 0;
}