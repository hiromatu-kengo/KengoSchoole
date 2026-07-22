#include<stdio.h>
#include<windows.h>

//曜日を表す列挙体
enum Week
{
	//列挙体の要素は
	//先頭の要素が 0
	//2つ目以降の要素は一つ上の要素+1
	//という値になる

	SUN,  //内部的には0
	MON, //1
	TUE, //2
	WED, //3
	THU, //4
	FRI, //5
	SAT  //6
};

enum Week2
{
	//内部的な数値を変更することが可能
	_SUN, 
	_MON, 
	_TUE, 
	_WED, 
	_THU, 
	_FRI, 
	_SAT  
};

int main()
{
	SetConsoleOutputCP(65001);		

	enum Week wk;
	//列挙体をデータ型として持つ変数には
	//列挙体の要素のいずれかを代入する
	wk = MON;

	//内部的には実はint型なので
	//整数を代入することもできるがよくないので避ける
	//wk = 16;

	printf("wk = %d\n", wk);

	printf(" _SUN, = %d\n", _SUN);
	printf(" _MON, = %d\n", _MON);
	printf(" _TUE, = %d\n", _TUE);
	printf(" _WED, = %d\n", _WED);
	printf(" _THU, = %d\n", _THU);
	printf(" _FRI, = %d\n", _FRI);
	printf(" _SAT  = %d\n", _SAT);

	return 0;
}