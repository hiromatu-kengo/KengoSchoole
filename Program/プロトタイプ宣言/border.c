#include<stdio.h>
#include<windows.h>
#include"Border.h"

//プロトタイプ宣言


void DrawMultiBorder(int count)
{
	for (int i = 0; i < count; i++)
	{
		DrawBorder();
	}
}

void DrawBorder(void)
{
	printf("~~~~~~~~\n");
}