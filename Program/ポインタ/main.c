#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	//アドレスはポインタに保存する

	//pointer宣言の例
	int* ptA;
	float* ptB;
	char* ptC;

	//教科書だと
	//int *ptA;
	//int *ptB;
	//int *ptC;
	// となっている（スペースの位置買いが違う）
	// どっちでも問題ないが
	// Visual Studioが整形してくれた形のほうが一般的

	//int型の変数のアドレスを保存させたい場合は
	//int*

	//float型の変数のアドレスを保存させたい場合は
	//float*

	// ... ほかにも同様
	//元の変数のデータ型が重要!


	return 0;
}