#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	float height[3] = { 170.5f,169.0f,178.5f };
	/*
	//sizeof 演算子
	//データの大きさをByteで取得する
	printf("sizeof(char) : %zu\n", sizeof(char));
	printf("sizeof(int) : %zu\n", sizeof(int));
	printf("sizeof(double) : %zu\n", sizeof(double));

	//変数のデータサイズを取得する
	double num = 0;
	printf("sizeof(num) : %zu\n", sizeof(num));

	//配列名を指定することで配列全体のサイズを取得できる
	printf("sizeof(height) : %zu\n", sizeof(height));

	//配列全体のサイズと配列要素のサイズから配列の要素数を計算できる
	printf("height[]の要素数は%dです\n", sizeof(height) / sizeof(height[0]));
	*/
	printf("float型のサイズは%zuバイトです\n", sizeof(height[0]));

	//配列は必ず順番メモリに配置される
	//配列名=配列全体の先頭アドバイス
	printf("heigt[0]のアドレスは%pです\n", &height[0]);
	printf("heightの値は        %pです\n", height);

	//アドレスの足し算は単純に加算されるのではなく、
	//+１するごとにデータ型のサイズ分アドレスが移動していく
	printf("heigt[1]のアドレスは%pです\n", &height[1]);
	printf("heigh+1の値は       %pです\n", height+1);

	printf("heigt[2]のアドレスは%pです\n", &height[2]);
	printf("height+2の値        %pです\n", height+2);

	//関節参照演算子を使ってアドレスから配列各要素にアクセス
	printf("*height  の値は%fです\n",*height);
	printf("*height+1の値は%fです\n", *(height+1));
	printf("*height+2の値は%fです\n", *(height+2));

	return 0;
}