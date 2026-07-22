#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		
/**
	//4任パーティー
	int playerHp0 = 128;
	int playerHp1 = 128;
	int playerHp2 = 128;
	int playerHp3 = 128;

	printf("HP0 : %d\n"playerHp0);
	printf("HP0 : %d\n"playerHp1);
	printf("HP0 : %d\n"playerHp2);
	printf("HP0 : %d\n"playerHp3);


	*/

	//同じような役割をも乙変数を複数個まとめて作成したい
	//HPを保存するための変数をまとめて４個作成したい
	// →配列を使用する

	//文法
	//型名　配列名[要素名];
	int playerHp[4];

	//インデックスを指定して
	//度の変数に値を代入したり参照したりするかを決める
	//配列のいんでっくるを指定するときは0から指定する
	playerHp[0] = 128;
	playerHp[1] = 228;
	playerHp[2] = 328;
	playerHp[3] = 428;
	//配列の数が４なので[４]は使えない

	printf("[0] : %d\n", playerHp[0]);
	printf("[1] : %d\n", playerHp[1]);
	printf("[2] : %d\n", playerHp[2]);
	printf("[3] : %d\n", playerHp[3]);

	return 0;
}