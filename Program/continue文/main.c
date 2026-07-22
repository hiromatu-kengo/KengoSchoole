#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	//1からnumまでの数字をprintfで表示するプログラム
	int num = 10; //2以上正の値のみ
	int answer = 0;
	//num回繰り返すfor文を書く

	for (int i = 1;i <= num; i++)
	{
		//3の倍数は足さない

		//3の倍数以外であれば足す

		//3の倍数なら足す
		if (i % 3 == 0)
		{
			continue;
		}
			answer += i;
			printf("%d\n", i);
	}
	printf("%d\n", answer);

	return 0;
}