#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	//変数はメモリ上に保存するための領域を確保する
	int num = 123;

	//どこに確保したか、場所のことをを【アドレス】と呼ぶ

	//アドレスを取得するときは
	//アドレスを取得したい変数名の前に&をつける
	printf("addr : 0x%p\n", &num);

	//アドレスを保存するときはポインタに代入する

	//保存したい変数の型名* ポインタ名;
	int* pNum = &num;

	printf("ptr : 0x%p\n", pNum);

	//ポインタから
	//その参照先に入っているデータを取得することができる
	printf("ptr = %d\n", *pNum);

	//関節参照演算子で参照した先の変数の中身に代入することもできる
	*pNum =64;
	printf("num = %d\n", num);

	return 0;
}