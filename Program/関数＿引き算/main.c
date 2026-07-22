#include<stdio.h>
#include<windows.h>

//引数:関数に「この数字を使って処理してください」という変数を渡すことができる
//	　 この渡す数のことを引数と呼ぶ

/*文法
void 関数名(引数のデータ型　仮引数）
{
		関数で行う処理;
}
*/

void f(int x)
{
	printf("渡された変数の値は%dデス\n", x);
	x = x + 1;
	printf("1を足した値は%dになります\n", x);
	return;//returnが呼ばれた時点で関数が終了
		  //戻り値がvoidの場合　省略可
}

int main()
{
	SetConsoleOutputCP(65001);		

	int num = 5;

	f(num);//関数内で渡した数値を+1している

	//変数numを使ってもらうわけではなく
	//中身のコピーをしているだけなので
	//関数内で数値を変更しても変数には影響がない
	printf("num = %d\n", num);

	float value = 3.14f;
	f(value);

	return 0;
}