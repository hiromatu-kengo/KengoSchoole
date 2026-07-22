#include<iostream>
#include<string>

int main()
{
	//文字列はstring型に保存する
	std::string str = "こんにちは";
	std::cout << str << std::endl;
	//代入も可能
	str = "こんばんは";
	std::cout << str << std::endl;

	//比較や連結なども簡単にできる
	if (str == "こんばんは")
	{
		std::cout << "夜" << std::endl;
	}

	return 0;
}