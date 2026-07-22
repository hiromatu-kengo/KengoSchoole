#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	//C言語、C++では[文字]と[文字列]は明確に違う

	//char型　文字を半角１文字を保存するための変数

	//半角１文字を扱う場合は　　その文字を''でくくる
	char moji = 'a';
	printf("moji = %c\n", moji);

	//文字列とわ
	//文字の集まり
	//その集まりを""でくくる
	printf("文字列を表示\n");//実はprintfの引数は文字列だった

	//半角１文字でも""でくくればそれは文字列という扱い
	printf("c");

	//文字列を保存するにはどんなデータ型に入ればいいのか？
	char str[8];  //"C_Gengoという文字列を保存したい
	str[0] = 'C';
	str[1] = '_';
	str[2] = 'G';
	str[3] = 'e';
	str[4] = 'n';
	str[5] = 'g';
	str[6] = 'o';
	str[7] = '\0'; //NULL文字　文字列の終端を表す
                  //文字列の終端には必ず入れる
	//最後に必ず\0を入れる必要があるので文字列の長さ+1の要素数が必要

	printf(str);   //文字列の配列を表示したい場合は配列名を引数にする
	printf("\n");

	//配列の初期化と同じ方法で文字列の初期化も可能
	char str2[8] = { 'C','_','G','e','n','g','o','\0' };
	printf(str2);
	printf("\n");

	//文字はこんな書記官可能
	char str3[8] = "G_Gengo"; //""でくくる　さいごの \0は不要
	printf(str3);
	
	//str3 ="H_Gengo";//NG初期化の時のみこういう書きかができる

	printf("\n");

	//さらにべんりなしょきか
	char str4[] = "I_Gean"
		printf(cstr)

	return 0;
}