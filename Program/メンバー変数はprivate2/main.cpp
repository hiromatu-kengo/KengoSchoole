#include<iostream>

class Player
{
public:
	void DispStatus()
	{
		std::cout << hp << "/" << maxHp << std::endl;
	}
public:
	int hp;
	int maxHp;
};

int main()
{
	Player pl;
	pl.hp = 50;
	pl.maxHp = 100;

	pl.DispStatus();


	return 0;
}