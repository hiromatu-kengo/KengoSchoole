#include<iostream>

class Player
{
	//アクセスして意思がない場合はprivate
	int speed;
private:  //porivate名メンバーにはクラス外からアクセスできない
	int attack;
	//クラスの外からメンバーにしてもOK、とする
	//public:と書くとそこ意向で宣言されたメンバーにはクラス外からアクセスできる
public:  //public名メンバーには九r巣の外からアクセスできる
	int hp;
	int mp;

};


int main()
{

	std::cout << "クラス基礎" << std::endl;

	//作ったクラスを使用する
	Player pl;
	pl.hp = 100;
	pl.mp = 50;

//	pl.attack = 60;//privateなメンバーなのでアクセスできない

	std::cout << "HP" << pl.hp << std::endl;
	std::cout << "MP" << pl.mp << std::endl;

	return 0;
}