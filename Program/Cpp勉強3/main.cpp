#include<iostream>

int main()
{
	int num0 = 10;
	int num1 = 20;

	//メモリを確保したとき、
	//以前使われた情報がそのまま残っている
	// //そのアドレスがたまたま重大なバグを引き起こす先を参照している可能性がある

	//子のポインタはどこも参照していないという状を持っておきたい
	//nullptrはどこも参照していない、という情報
	int* pNum = nullptr;

	//ポインタがどこを指している(nullptrではない)場合、処理を行う
	//nullptrはコンピュータの内部的には0となっている
//	if (pNum != nullptr)
	if(pNum)		//nullptrが内部的には0、if文が0以外なら実行する、という性質を組み合わせてこう書くこともできる
	{
		std::cout << "high =" << *pNum << std::endl;
	}
	if (num1 > num0)
	{
		pNum = &num1;
	}
	else
	{
		pNum = &num0;
	}

	std::cout << "high ="<< * pNum << std::endl;

	return 0;
}