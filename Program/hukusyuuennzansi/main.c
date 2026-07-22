#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	int hp = 100;

	//15ダメージを受けた
	hp = hp - 15;
	printf("15ダメージを受けた！\n");
	printf("残りHP:%d\n",hp);

	//変数自身の値を変更したい場合、
	//複合代入演算子を使用する

	//hpを20回復
	hp += 20;
	printf("HPを20回復\n");
	printf("残りHP:%d\n", hp);


	return 0;
}