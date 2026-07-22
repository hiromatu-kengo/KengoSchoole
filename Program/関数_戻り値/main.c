#include<stdio.h>
#include<windows.h>

//戻り値のある関数
// 文法
// 戻り値のデータ型　関数名（仮引数のデータ型　仮引数名...）
// {
//		関数に行わせたい処理;
//		return 戻り値;
// }
//

//引数として与えられた２つの数の足し算を行い、
//その結果を戻り値として返す関数

int Add(int x, int y)
{
	//int z = x + y;
	return x+y;
}

// 引き算　Sub x - y
int Sub(int x, int y)
{
	//int z = x - y;
	return x-y;
}
//掛け算　Mul x * y
int Mul(int x, int y)
{
	//int z = x * y;
	return x*y;
}
//割り算 Div x / y
int Div(int x, int y)
{
	//int z = x / y;
	return x/y;
}
//大きいほうの数値を取得する　GetMax x or y
int GetMax(int x, int y)
{
	if (x > y)
	{
		return x;
	}
	else
	{
		return y;
	}
}

int main()
{
	SetConsoleOutputCP(65001);

	int num0 = 100;
	int num1 = 20;

	//int ans = num0 + num1;
	int addAns = Add(num0, num1);
	int subAns = Sub(num0, num1);
	int mulAns = Mul(num0, num1);
	int divAns = Div(num0, num1);
	int getMax = GetMax(num0, num1);

	printf("addAns = %d\n", addAns); // 120
	printf("subAns = %d\n", subAns); // 80
	printf("mulAns = %d\n", mulAns); // 2000
	printf("divAns = %d\n", divAns); // 5
	printf("getMax = %d\n", getMax); //100



	return 0;
}