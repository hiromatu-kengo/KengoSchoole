#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		
	/*
	in num = 0;

	//キーボードから値を代入する

	//第1引数 ; 整数値を入力したい場合は%d
	//			浮動小数点数を入力したい場合は%f
	//			※最後に\n入れない
	//第２引数: &値を入力した変数名　&num
	scanf_s("%d",&num);

	printf("num = %d\n", num);
	*/

	//配列の復讐;
	//配列を使うと同じデータ型の
	
	int playerHp[4];
	/*
	playerHp[0] = 123;
	playerHp[1] = 123;
	playerHp[2] = 123;
	playerHp[2] = 123;
	*/

	//添え字は変数を使うことができる
	/*
	scanf_s("%d ", playerHp[1]);
	printf("player1 : %d\n", playerHp[1]);
	*/
	//要素数を指定しなかった場合、初期化しの数が配列の要素数になる

	//要素数よりも初期化しが少ない場合
	//要素数は指定された数準備される
	//初期化しがない要素には0が代入される

	return 0;
}