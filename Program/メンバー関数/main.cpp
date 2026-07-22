#include<iostream>

class Player
{
	//クラスは変数だけでなく、関数もメンバーとして持つことができる
public:
	void DispStatus()
	{
		//このメンバー関数を呼び出したインスタンスが持つめばー変数の値を参照する
		std::cout << "HP:" << hp << std::endl;
		std::cout << "MP:" << mp << std::endl;
		std::cout << "ATK:" << attack << std::endl;

	}

	//private名メンバー関数経由で値を設定する
	void SetAttack(int val)
	{
		//メンバー関数からならprivate名メンバーにアクセスできる
		attack = val;
	}
public:
	int hp;
	int mp;

private:
	int attack;
};

int main()
{
	Player pl;
	pl.hp = 100;
	pl.mp = 50;
	pl.SetAttack(20);

	Player pl2;
	pl2.hp = 1000;
	pl2.mp = 500;

	//メンバー関数を呼び出す
	pl.DispStatus();  //plのHPとMPを表示する
	pl2.DispStatus();  //pl2のHPとMPを表示する

	return 0;
}