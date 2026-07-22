#include<iostream>

class Player
{
public:
	//メンバー関数の実相をクラス内に直接書くことは少ない
	/*void Setup(int h,int m)
	{
		hp = h;
		mp = m;
	}*/
	//クラス宣言部分では関数の宣言のみ行う　中身の実相は別の場所で行う
	void Setup(int h, int m);

	//const名メンバー関数はその関数内でメンバー変数の値を変更できない
	//メンバー変数の値を変更してはいけない関数内で間違えて変更することを防ぐ
	//この関数を呼び出しても絶対にメンバー変数の値は変更されていないことが保証される
	int GetHp() const { return hp; }
	int GetMp() const { return mp; }

public:
	int hp;
	int mp;
};

//クラスのメンバー関数の中身を書いていく
//Playerクラスに属するSetup関数だよ、ということをコンパイラに教える
//クラス名::メンバー関数名()
void Player::Setup(int h, int m)
{
	hp = h;
	mp = m;
}

int main()
{
	Player pl;
	pl.Setup(100, 50);
	std::cout << pl.GetHp() << std::endl;


	return 0;
}