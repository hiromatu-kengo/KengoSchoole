#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	printf("0:%d\n", 123);

	//%4d 4文字分のスペースが準備がされ、左揃えで表示される
	printf("1:%4d\n", 123);
	//%5d　5文字分のスペースが準備され、左揃えで表示される
	printf("2:%5d\n", 123);

	//数値の値をそろえて表示する
	printf("%5d\n", 1);
	printf("%5d\n", 12);
	printf("%5d\n", 123);
	printf("%5d\n", 1234);
	printf("%5d\n", 12345);

	int num = 0;
	for (int i = 0;i < 16; i++)
	{
		for (int j = 0;j < 16;j++)
		{
			printf("%3d", num);
			num++;
		}
		printf("\n");
	}

	//0埋め
	//%0.5 位の位置をそろえるのは%5dと同じ
	//00123 のように%5dだとスペースだった部分が0で埋められる
	printf("%05d\n", 1);
	printf("%05d\n", 12);
	printf("%05d\n", 123);
	printf("%05d\n", 1234);
	printf("%05d\n", 12345);

	float floatValue = 12.345f;
	printf("%f\n",floatValue);
	printf("%.3f\n", floatValue);//小数点以下の３位まで表示
	printf("%8.3f\n", floatValue);//８桁分スペースを準備して右揃え　&　小数点以下３位まで表示

	return 0;
}