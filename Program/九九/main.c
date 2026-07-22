#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	/*２重for文を作って九九の表を作る
	　for(int i = 0; i < 9; i++)
	  for(int i = 1; i <= 9; i++)  //今回はこっち
	  
	  //できた人は見栄えを追求する
	  */

	for (int i = 1;i <= 9; i++)
	{
		printf("%dの段\n", i);
		for(int j = 1;j <= 9;j++)
		{
			//九九の表から30以上の数字を除外する
			if (i * j >= 30)
			{
				break;	//現在の行を強制終了
			};

			printf("%4d", i * j);
		}
		printf("\n");
	}

	return 0;
}