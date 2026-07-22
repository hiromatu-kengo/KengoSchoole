#include<iostream>

class Player
{
public:
	//コンストラクタ
	Player();

	void DispStatus();
	

private:
	int m_hp;
	int m_mp;
};

//Playerクラスのコンストラクタの実装

//コンストラクタにはメンバー変数の初期化を行う仕組みがある
//メンバー変数の初期化を行うときは基本的にはこちらの方法で初期化を行う
Player::Player():
	m_hp(10),//横に並べると見ずらいときは改行
	m_mp(20)
{
	std::cout << "コンストラクタ" << std::endl;
}
void Player::DispStatus()
{
	std::cout << "HP:" << m_hp << std::endl;
	std::cout << "MP:" << m_mp << std::endl;
}

int main()
{
	Player pl;
	pl.DispStatus();


	return 0;
}