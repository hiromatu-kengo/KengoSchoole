#include<stdio.h>
#include<windows.h>

int SquareArea(int x, int y)
{
	printf("横 %d : 縦 %d の四角形の面積は%d\n",x,y,x * y);
}

int Race(int i, int j)
{
	if (i > j)
	{
		printf("兄のほうが足が速かった\n");
	}
	else
	{
		printf("弟のほうが足が速かった\n");
	}

}

int MuscleTraining(a)
{
	for (int i = 0;i < a;i++)
	{
		printf("残り%d回\n", a - i);
	}
}

int NotMultiple(int num)
{
	for (int i = 1;i <= num;i++)
	{
		if ((i % 2) != 0 && (i % 3) != 0 &&(i % 7) != 0)
		{
			printf("%d\n",i);
		}
	}
}

int main()
{
	SetConsoleOutputCP(65001);		

	SquareArea(5, 6);

	Race(10, 2);

	MuscleTraining(10);

	NotMultiple(100);

	return 0;
}

