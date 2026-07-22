#include<iostream>

struct Player
{
	int hp;
	int mp;
};

union Test
{
	int num;
	double value;
};

enum Val
{
	VALUE_0,
	VALUE_1,
	VALUE_2,
	VALUE_3

};

//C++風列挙体の宣言
enum class Category
{
	Value1,
	Value2,
	Value3,
	Value4

};

enum class Category2
{
	Value1,
	Value2,
	Value3,
	Value4

};

int main()
{
//	struct Player p;
	Player p;
	p.hp = 100;
	p.mp = 100;

	//unionTest t;
	Test t; //C++ではStruct省略可能

	//enum Val v =VALUE_0;
	Val v = VALUE_0;
//	v = 123;		//C言語だと内部的にintだったので数値を代入できたが
					//C++ではおかしい値を入れようとしている都市テイラーになる

	Category c = Category::Value1;
	c = Category::Value2;
	
	Category2 c2 = Category2::Value1;
	c2 = Category2::Value2;

	return 0;
}