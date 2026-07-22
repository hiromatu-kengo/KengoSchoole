#include<iostream>

void Func(int x)
{
	std::cout << "x =" << x << std::endl;

	x *= 2;//値渡しなので元の変数には影響しない
}

//ポインタ渡しで引数として渡した変数の値を直接変更する
void DoubleNum(int* pX)
{
	*pX *= 2;
}

//DispNum : 数値を表示する
//数値を表示するための関数だと思っていたのになぜか変数の値を2倍にしてしまっている

//ポインタを渡した場合、関数内でその数値を変更することができる
//ポインタを渡してしまうと勝手に数値を書き換えられてしまうかもしれない...
//
//関数を使う側としては渡した値が変更されるかどうかを知っておきたい

//ポインタ宣言の前にconstをつけるとその参照先は変更できなくなる
//関数を使う側 : この関数を読んでもかってに値を変更されないことが保証される
//関数を作る側 : 間違えて変更してはいけない値を変更してしまうことを防ぐ
void DispNum(const int* pX)
{
//	*pX *= 2;//constなポインタの参照先は変更できない error
	std::cout << "disp:" << *pX << std::endl;
}

int main()
{
	int num = 10;
	std::cout << "num =" << num << std::endl;

//	Func(num);
//	std::cout << "num =" << num << std::endl;

//	DoubleNum(&num);//変数のポインタを渡す
//	std::cout << "num =" << num << std::endl;

	DispNum(&num);
	std::cout << "num =" << num << std::endl;

	return 0;
}