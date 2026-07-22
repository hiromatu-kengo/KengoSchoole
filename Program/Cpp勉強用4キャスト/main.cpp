#include<iostream>

int main()
{
	int num = 13;

	//C言語風キャストなので今後は使わない
//	//警告を消すため、キャスト(型変換)してから代入する
//	float value = (float)num;

	//c++風キャスト
	float value = static_cast<float>(num);

	std::cout << value << std::endl;

	return 0;
}