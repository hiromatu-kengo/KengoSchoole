#include<stdio.h>
#include<windows.h>

//定数名　TBL_SIZE_1D
#define TBL_SIZE_1D 8

int main()
{
	SetConsoleOutputCP(65001);		

	//一次元配列（通常配列）
	int tbl1d[TBL_SIZE_1D];
	for (int i = 0;i < TBL_SIZE_1D;i++)
	{
		tbl1d[i] = i * 10;
		printf("[%d] : %d\n", i, tbl1d[i]);
	}

	//二次元配列
	//配列の配列と表現される(配列が複数ある)
	int tbl2d[2][3];  //サイズ3の配列が2つある

	tbl2d[0][0] = 123;
	printf("tbl2d[0][0] = %d\n", tbl2d[0][0]);
	tbl2d[0][1] = 64;
	printf("tbl2d[0][1] = %d\n", tbl2d[0][1]);
	tbl2d[0][2] = 4;
	printf("tbl2d[0][2] = %d\n", tbl2d[0][2]);

	//二次元配列の初期化
	//int tbl[4] = { 1,2,3,4, };//一次元配列の初期化
	int tbl2d_2[2][3] = { {1,10,100},{2,20,200} };

	//２重for文を使って二次元配列の中身を表示
	for (int j = 0;j < 2;j++)
	{
		for (int i = 0; i < 3; i++)
		{
			//tbl2d_2[0][0]
			//tbl2d_2[0][1]
			//tbl2d_2[0][2]
			printf("%4d", tbl2d_2[j][i]);
		}
		printf("\n");
	}

	return 0;
}