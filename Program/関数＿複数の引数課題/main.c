#include<stdio.h>
#include<windows.h>

//引数として  横幅w
//　　　　　　縦幅h
//を受け取り、そのサイズの□を＊を使って表示する

void drawSq(int w, int h)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			printf("＊");
		}
		printf("\n");
	}
}

void drawTr(int x)
{
	for (int i = 0; i < x;i++)
	{
		for (int j = 0;j < x-i;j++)
		{
			printf("＊");
		}
		printf("\n");
	}
}


int main()
{
	SetConsoleOutputCP(65001);		

	drawSq(4, 3);

	printf("drawTr\n");
	drawTr(8);

	return 0;
}