#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	int a;
	int* ptA;

	printf("変数aのアドレスは0x%pです\n",&a);

	//&を使って取得した変数aのアドレスを
	//ポインタptAに代入している
	ptA = &a;
	//アドレスが正しく代入されているかprintfで確認
	printf("ポインタptAの値は0x%pです\n", ptA);

	//この学校ではポインタの場合は先頭にpをつけるというルールが一般的
	//float* pFloat;

	return 0;
}