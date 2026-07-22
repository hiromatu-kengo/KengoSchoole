#include<iostream>

class Player
{
public:
	Player():m_hp(0)
	{
		std::cout << "コンストラクタ" << std::endl;
	}

	//メモリが解放されるときに必ず呼ばれる関数を
	//[デストラクタ]と呼ぶ

	//~クラス名();
	//引数なし、戻り値なし
	//終了時に必ずやらなければいけない後処理を書く
	~Player()
	{
		std::cout << "デストラクタ" << std::endl;
	}

private:
	int m_hp;
};

int main()
{
	Player pl;


	return 0;
}