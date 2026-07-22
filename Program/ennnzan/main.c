#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		
	
	//四則演算は掛け算、割り算が優先される
	int a = 2 + 3 * 5;
	printf("2+3*5=%d\n", a);	//17

	//()でくくることで計算の優先順位を変更することができる
	int b = (2 + 3) * 5;
	printf("(2+3)*5=%d\n", b);	//25

	//優先度が同じ場合は左から処理される
	int c = 6 - 2 - 1;
	//c=4-1 //6-2が先に計算される
	//c-3 //4-1	が計算される
	printf("6-2-1=%d\n", c);	//3

	//=演算子は右から順に処理される
	a = b = c;  //a=17 b=25 c=3
	//b - c が先に計算される //a=17 b=25 c=3
	// ->cの値がbに代入される //a=17 b=25 c=3
	//そのあと a = b が計算される
	//->bの値がaに代入される //a=17 b=25 c=3
	printf("a = %d\n", a);
	printf("b = %d\n", b);
	printf("c = %d\n", c);

	return 0;
}