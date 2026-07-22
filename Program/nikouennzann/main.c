#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		
	int hp = 100;

	//ダメージを受けたのでHP１０減らす
	hp = hp - 10;	//hpから１０を引いた値をhpに代入する
	printf("10ダメージを受けた\n");
	printf("残りHP: %d\n", hp);
	
	//魔力
	int magic = 20;
	
	//魔力の分HPを回復させたい
	hp = hp + magic;
	printf("残りHP: %d\n", hp);

	//変数自身の値を増やしたり、減らしたりしたい、
	//ということはよくある
	//そういう場合は複合代入演算子を使用する

	//ダメージを受けたのでHP２０減らす
	//hp = hp - 20;
	hp -= 20;	// -= が演算子 -と=の間にスペースを入れてはならない
				//hpから２０を引いた値をhpに代入する
				//→hpの中身を２０減らす
	printf("20ダメージを受けた\n");
	printf("残りHP: %d\n", hp);

	//バフ効果で魔力を２倍にする
	// magic = magic * 2; 複合代入演算子を使わない場合
	magic *= 2; // *= が演算子
				//magicの中身を２倍する
	printf("魔力バフ！魔力が%dになった\n", magic);

	//魔力分回復
	hp += magic;  //右辺を変数にすることも可能
				  //hpをmagic分増やす
	printf("HPを%d回復\n", magic);
	printf("残りのHP: %d\n", hp);
	
	return 0;
}