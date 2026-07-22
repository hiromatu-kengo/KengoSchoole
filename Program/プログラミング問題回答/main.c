#include<stdio.h>
#include<windows.h>
#include<math.h>

//関数とは : 複数の入力を渡すと、何やら計算して、一つの出力を返すもの。
float Dstance(float x1, float y1, float x2, float y2)
{
	float xDiff = x1 - x2;
	float yDiff = y1 - y2;
	return sqrt(xDiff * xDiff + yDiff * yDiff);
}

int Dot(int x1, int y1, int x2, int y2) 
{
	int z = (x2 * x1) + (y2 * y1);
	printf("内角%d\n", z);
}


int division(int enemyHp, int attack)
{
	int z = enemyHp / attack;
	printf("あと%d回で倒れる\n",z);
}

int MoneyLeft(int cash, int price)
{
	int z = cash - price;
	printf("残金%d\n",z);
}

int  Daikei(int up, int down, int height)
{
	int z = (up + down) * height / 2;
	printf("台形%d\n", z);
}

Multi(int x, int y)
{
	int z = x * y;
	printf("掛け算%d\n", z);
}

float AreaCalculation(float x1, float y1, float x2, float  y2)
{
	float z = (x2 * y1) - (x1 * y2);
	printf("外積%d\n", z);
}

int main()
{
	SetConsoleOutputCP(65001);		
	
	Dstance(8, 4, 5, 6);
	printf("ベクトル%f\n", sqrt);
	Dot(2, 3, 4, 5);
	division(10, 1);
	MoneyLeft(72,23);
	Daikei(3, 2, 5);
	Multi(6 , 3);



	return 0;
}