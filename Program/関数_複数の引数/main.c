#include<stdio.h>
#include<windows.h>



//関数呼び出し側が引数として指定した順番に
//仮引数に代入が行われる

//引数が複数ある場合
//前から順番に第１引数、第２引数...と呼ばれる
void bigger(int x, int y)
{
	printf("２つの引数のうち、どちらが大きいか比較します\n");
	if (x > y)
	{
		printf("%dのほうが大きいです\n",x);
	}
	else
	{
		printf("%dのほうが大きいです\n", y);
	}
	return;
}


int main()
{
	SetConsoleOutputCP(65001);

	bigger(1, 5);

	return 0;
}