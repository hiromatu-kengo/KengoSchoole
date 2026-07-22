#include<iostream>

class Player
{
public:
	//キャラクターのステータスを表示
	void DispStatus();

	int GetHp()const { return m_hp; }
	void SetHp(int hp) { m_hp = hp; }

	int GetHp()const { return m_mp; }
	void SetHp(int mp) { m_mp = mp; }

private:
	//メンバー変数にはこれが変数だと
	//一目でわかるような変数名を付けてやる

	//ルールは何でもOK
	//度のルールを選んだとっしても統一化する
	int m_hp;
	int m_mp;
};

//Playerのメンバー関数
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