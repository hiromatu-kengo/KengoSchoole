#include<iostream>

int main()
{

	std::cout << "全角確認" << std::endl;

	//coutを使って変数の値を表示する
	int num = 10;
	float value = 1.75f;

	//型を判断していい感じに表示してくれるので
	//intだろうとfloatだろうとおなじようなかきかたになる
	std::cout << "num =" << num<<std::endl;
	std::cout << "value =" <<value<<std::endl;

	char c = 'x';
	std::cout << "c =" << c<<std::endl;

	//char型文字ではなく文字コードを表示したい
	//表示したいデータ型にキャストして表示
	std::cout << "c =" <<(int)c<< std::endl;

	//これももちろんOK
	std::cout << num << std::endl;

	//const修飾子
	num = 16; //変数は値を代入して変更できる

	//変数は変更してほしくない、変更するとバグの原因になるみたいなことがある
	//自分で変更してはいけないことはわかっていてもチームメイトが変更してしまう、ということがある
	//
	//変更してほしくない変数の値を変更できないようにする仕組みが[const]
	// 
	//通常の変数宣言の前にconstをつける
	const int cNum = 256;

	//const int cNum2; //後から変更できないので初期化で初期値を入れてやらないといけない
	//cNum2 = 333; //後から値を入れられない

	//bool型
	//bool型にはtrueかfalseしか言えれられない

	//true: 真
	//false: 偽

	bool isFlag = true;
	isFlag = false;

	//ON,OFFの2つの状態のみで表現できるものはbool型で管理する

	bool isDead; //キャラクターが死んでいるフラグ
	isDead = true;//しんでいる
	isDead = false;//死んでいない

	if (isDead)
	{
		//死んでいるなら(isDead=true)の時の処理
		std::cout << "死んでいる" << std::endl;
	}
	else
	{
		//死んでいないなら(isDead=false)の時の処理
		std::cout << "死んでいない" << std::endl;
	}

	return 0;
}