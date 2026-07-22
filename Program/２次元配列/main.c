#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	//今まで勉強してきた配列を
	//1次元配列と呼ぶこともある
	//int playerHp[4];
	/*
	int hairetu[3][4];

	//添え字を２つ使って各要素にアクセスする
	hairetu[0][0] = 1;

	hairetu[2][3] = 12;

	printf("[2][3] = %d\n", hairetu[2][3]);
	*/

	//int hairetu[4] = { 1,2,3,4 };
	//大きさ４の配列が３つ入っているような初期化を行う必要がある
	int hairetu[3][4] =
	{
		{ 1,2,3,4 } ,
		{ 5,6,7,8 } ,
		{ 9,10,11,12 } 
	};

	/*
	for (int i = 0;i < 3;i++)
	{
		printf("%3d", hairetu[i][0]);
		printf("%3d", hairetu[i][1]);
		printf("%3d", hairetu[i][2]);
		printf("%3d", hairetu[i][3]);
		printf("%3d", hairetu[i][4]);

	}
	*/

	for (int i = 0;i < 3;i++)
	{
		for(int j = 0;j<4;j++)
		{
			printf("%3d", hairetu[i][j]);
		}
		printf("\n");
	}

	return 0;
}