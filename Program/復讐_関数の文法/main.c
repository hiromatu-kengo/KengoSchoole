#include<stdio.h>
#include<windows.h>

/*引数がない関数の文法
* void 関数名(void)
* {
*	//関数が行う処理
* }
*/

//関数名はパスカルケース
//同氏を先頭に持ってくることが多い
void DrawMysteryString(void)
{
	//関数が行う処理をここに書く
	printf("<>+179836huf.oel\n");
}

//自分が作る関数の中から自分の作った感を呼び出せる
void DrawDoubleMysteryString(void)
{
	DrawMysteryString();
	DrawMysteryString();
}

//引数のある関数の文法
//void 関数名（引数のデータ型　仮引数名）
//{
	//関数が行う処理
//}

//指定した回数DrawMysteryString();を呼び出す関数
void DrawMultiMysteryString(int count)
{
	//countに代入されている回数だけ
	//DrawMysteryString();を呼び出してやればよい
	for (int i = 0; i < count; i++)
	{
		DrawMysteryString();
	}
}

//複数の引数を関数に渡すこともできる
//void 関数名（引数1のデータ型　仮引数名1,引数2のデータ型　仮引数2,　引数3のデータ型　仮引数名3 ...）
//{
	//関数が行う処理
//}
void TestFunction(int num0, int num1, float num2)
{
	printf("num0 = %d\n", num0);
	printf("num1 = %d\n", num1);
	printf("num2 = %f\n", num2);
}

void TestFunctionx(int x)
{
	printf("X = %d\n", x);
	x += 100;
	printf("x2 = %d\n", x);

}

int main()
{
	SetConsoleOutputCP(65001);		

	//同じ処理を何度も書くことはできるが義理酒用
	// 
	// 修正した場合、何か所を修正しない解けない
	// 修正漏れが発生したりする

	//同じ処理を何度も行う場合は
	//その処理を関数化しましょう
	
	//引数なしの関数の呼び出し
	//DrawDoubleMysteryString(); //関数名（）;
	//引数あり関数の呼び出し　関数に渡したい数値を（）野中仁鶴
	//関数に渡したい数値のことを[引数]と呼ぶ
	DrawMultiMysteryString(3);

	printf("test\n");

	DrawMultiMysteryString(8);

	//渡したい数値を "," で区切る
	//渡した順番に関数の仮引数に代入される
	//今回は　num0 = 10, num1 = 100, num2 = 3.14f
	TestFunction(10, 100, 3.14f);

	//引数の数が合わない場合はビルドエラー
	//TestFunction(10,  3.14f);//エラー　引数が３つ必要なのだが２つしかしていない
	//TestFunction(10, 100, 3.14f,1000);//エラー　引数は３つなのだが４つ値を渡している

	int y = 16;
	TestFunctionx(y);

	printf("y = %d\n", y);

	return 0;
}