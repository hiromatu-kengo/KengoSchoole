#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	int hp = 0;

	while (hp > 0)
	{
		printf("敵に攻撃した!\n");
		hp--;
	}

	do
	{
		printf("敵に攻撃した!\n");
		hp--;
	} while (hp > 0);  //セミコロンあり

	return 0;
}