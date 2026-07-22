#include<iostream>

class Player
{
public:
	//コンストラクタには引数を持たせることができる
	Player();//引数がないコンストラクタ
	Player(int hp,int mp);//引数が2つのコンストラクタ

	void DispStatus();


private:
	int m_hp;
	int m_mp;
};
/*
Player::Player():
	m_hp(999),
	m_mp(999)
{
	std::cout << "引数なしのコンストラクタ" << std::endl;
}
*/
Player::Player() :
	Player(100, 50)
{
	std::cout << "引数なしのコンストラクタ" << std::endl;
}
Player::Player(int hp, int mp):
	m_hp(hp),
	m_mp(mp)
{
	std::cout << "引数ありのコンストラクタ" << std::endl;
}

void Player::DispStatus()
{
	std::cout << "HP:" << m_hp << std::endl;
	std::cout << "MP:" << m_mp << std::endl;
}

int main()
{
	//基本的にHP100 MP50 レアキャラは別の数値にしたい
	Player commonPl;
	commonPl.DispStatus();

	/*
	//変数名宣言後{}の中にコンストラクタの引数を書く
	Player pl{ 200,50 };
	pl.DispStatus();

	Player pl2(120,80);//{}ではなく()の中に書くこともできるが、{}のほうがいい
	pl2.DispStatus();

	Player pl3{};
	Player pl4;
	*/
	return 0;
}