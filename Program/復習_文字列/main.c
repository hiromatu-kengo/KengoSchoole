#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	//文字と文字列

	//文字 : 半角１文字
	//半角１文字を''でくくって表示する
	//文字はchar型変数に保存する
	char moji = 'd';
	//%cを使って表示
	printf("moji:%c\n", moji);

	//文字列 : 文字の集まり(0文字以上)
	//文字列を""でくくって表示する

	//%sを使って表示
	printf("文字列:%s\n", "abcde");

	//文字列はchar型の配列に保存する
	char str[4];
	str[0] = 'a';
	str[1] = 'b';
	str[2] = 'c';
	str[3] = '\0'; //文字列は\0で終わる
	printf("str:%s\n", str);  //文字列を指定するときは配列名を書く

	//char str2[7] = "abcdef";
	//char str2[] = "abcdef";
	char str2[] = "全角OK";
	printf("str2:%s\n", str2);

	//scanfを使って文字列をキーボードから入力
	char input[256];   //大きめの配列を準備

	//第１引数　"%S"
	//第２引数　配列名　&は不要
	//第３引数　配列のサイズ
	scanf_s("%s",input,256);
	printf("キーボードから入力した文字列:%s\n", input);

	return 0;
}