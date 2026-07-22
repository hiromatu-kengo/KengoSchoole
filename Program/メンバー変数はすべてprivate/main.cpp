#include<iostream>

class Player
{
public:
	void  SetHp(int h){hp = h;}
	int GetHp(){return hp;}
	void SetMP(int m){mp = m;}
	int GetMp(){return mp;}
private:
	int hp;
	int mp;
};


int main()
{
	Player pl;
	pl.SetHp(100);
	pl.SetMP(50);
	
	std::cout << "HP:" << pl.GetHp() << std:endl;
	std::cout << "HP:" << pl.GetHp() << std:endl;

	return 0;
}