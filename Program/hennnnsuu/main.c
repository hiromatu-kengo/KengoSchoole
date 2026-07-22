#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);
	
	//変数を宣言すると同時に値を代入することができる
	int maxHp =128;  //最大HP
	int nowHp = maxHp;  //現在のHP

	int attack = 0;  //後で値を代入するけど念のため０で初期化しておく、よくやる

	//maxHp = 128;
	//nowHp = maxHp;//現在のHPを最大HPに
	

	printf("HP%d / %d\n", nowHp, maxHp);

	return 0;
}