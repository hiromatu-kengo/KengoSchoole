#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		
	int playerHp = 0;

	//scanf_s関数を利用して
	//キーボードから値を取得する
	printf("<プレイヤーのHPを決定してください>");

	//第１引数 "%d"
	//第２引数 "&playerHp"

	//第１引数　これで覚える　\nを入れないように
	//第２変数　値を入れたい変数の前に & をつける
	//どちらもありがちなミス
	scanf_s("%d", &playerHp);

	printf("HP:%d\n", playerHp);
	if (playerHp >= 200)
	{
		printf("ボスの攻撃に耐えた\n");
	}
	else
	{
		printf("------- 死 -------\n");
	}

	//浮動小数点を入力
	float h;
	scanf_s("%f", &h);

	if (h >= 170.0f)
	{
		printf("人権あり\n");
	}
	else
	{
		printf("人権なし\n");
	}

	return 0;
}