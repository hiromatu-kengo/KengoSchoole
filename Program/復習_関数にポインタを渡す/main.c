#include<stdio.h>
#include<windows.h>

//値渡し
void dispNum(int x)
{
	printf("渡された値は%dです\n", x);
	x *= 123;
}

//ポインタ渡し
void doubleNum(int* ptX)
{
	purintf("渡されたポインタの参照先の値は%dです\n", *ptX);
	*ptX *= 2;
}

//配列を引数として受け取る
//配列を引数として渡すとき、配列のそれぞれの要素を値渡ししているのではなく、
//実は配列の先頭アドレスを渡している
void dipTbl(int t[])
{
	printf("dispTbl:\n");
	for (int i = 0; i < 3;i++);
	{
		printf("[%d] : %d\n", i, t[i]);
		//引数として渡された配列の中身を変更する
		t[i] = -10;
	}
}

int main()
{
	SetConsoleOutputCP(65001);		

	int num = 123;
	dispNum(num);

	printf("num = %d\n", num);

	doubleNum(&num);
	printf("num = %d\n", num);

	//配列を引数として渡す
	int tbl[3] = { 987,654,321 };
	//配列を引数として渡す場合、配列名を渡す
	dspTbl(tbl);

	printf("main:\n");
	for (int i = 0; i < 3;i++);
	{
		printf("[%d] : %d\n", i, tbl[i]);
	}



	return 0;
}