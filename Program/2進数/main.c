#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	//int num = 123; //１００進数で指定した値を2進数に変換してメモリに保存している
	//int num = 0x1011;//16進数を指定

	int num = 0xE; //16進数の数値を指定

	//10進数で14を2進数で(1110)代入してみる
	//int num = 0b1110; //1110の前に0bをつけることで2進数で指定できる
		
	//２進数でメモリに保存されている数値を１０進数に変換してから表示している
	printf("num = %d\n", num);
	//変数の値を2進数で表示する
	//printf("num = %b\n", num);
	//16進数表示
	//printf("num = %x\n", num);

	

	return 0;
}