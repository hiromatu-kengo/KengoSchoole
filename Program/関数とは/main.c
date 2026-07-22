#include<stdio.h>
#include<windows.h>

//いい感じの境界線を表示するための関数

/*文法
　void関数名(void)
 ｛
  　　関数が実行する処理；
  }
*/
void drowBorder(void)
{
	//printf("*************************************\n");
	printf("*************************************\n");
}

//九九の表を表示する関数
//drawkukuを作成
void drowkuku(void)
{
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1;j <= 9;j++)
		{
			printf("%4d", i * j);
		}
		printf("\n\n");
	}
}

int main()
{
	SetConsoleOutputCP(65001);	

	//printf("*************************************\n");
	drowBorder();  //自作の関数を呼び出す
	printf("            九九の表!\n ");
	drowBorder(); //自作の関数を呼び出す

	//drowkukuを呼び出して九九の表を表示
	drowkuku();

	/*
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1;j <= 9;j++)
		{
			printf("%4d", i * j);
		}
		printf("\n\n");
	}
	*/

	drowBorder(); //自作の関数を呼び出す

	//drowkukuでもう一度九九の表を表示
	drowkuku();

	return 0;
}