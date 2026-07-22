#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	//変数の初期化
	//変数宣言と同時にその変数に値を代入する
	//特に初期化したい値がない場合も大体0で初期化する
	int hp = 100;
	printf("HP:%d\n", hp);

	//四則演算
	//足し算　加算
	//演算子: +
	hp = 100 + 200;  //右辺の計算の結果が変数に代入される
	printf("+HP: %d\n", hp);

	//引き算　　減算
	//演算子: -
	hp = 100 - 200;
	printf("-HP:%d\n", hp);

	//掛け算　乗算
	//演算子: *
	hp = 10 * 20;
	printf("*HP:%d\n", hp);
	
	//割り算　除算
	//演算子: /
	hp = 150 / 10;
	printf("/HP: %d\n", hp);

	//余り　余算
	//演算子: %
	hp = 158 % 10; //158/10の余りである8をhpに代入される
	//printf("%%HP:%d",hp); //文字の％を表示したい場合は%%と重ねる
	printf("%%HP: %d", hp);

	//割り算の余りは切り捨てられる
	hp = 158 / 10;  //15.8よう数点以下の部分は切り捨て
	printf("HP: %d\n", hp);

	//float,doubleのような小数点以下を扱うデータ型
	//浮働小数点数　と呼ぶ

	//余の計算は浮動小数に対しては行えない
	float testFloat1 = 128.0f;
	float testFloat2 = 10.0f;

	//float result = testFloat1 % testFloat2;  errorが出る


	return 0;
}