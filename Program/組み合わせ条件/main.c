#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);	

	int attack = 80;
	int magic = 70;

	int bossHp = 50;

	//attack >=bossHp magic >= bossHp
	//どちらかの条件を満たせばボスを倒すことができる

	//複数の条件が存在して、どちらかを満たせば条件達成とする場合
	//その複数の条件を｜｜でつなげる
	//|		:shiftをおして\で入力
	if (attack >= bossHp || magic >= bossHp)
	{
		printf("ボスを倒した\n");
	}
	else
	{
		printf("～～死～～\n");
	}

	//裏ボス
	//attack >=bossHp magic >= bossHp
	//両方の条件を満たさなければ倒すことができない

	//複数の条件が存在して、両方を満たせば条件達成とする場合
	//その複数の条件を && でつなげる
	//&		:shiftをおして6で入力
	if (attack >= bossHp && magic >= bossHp)
	{
		printf("裏ボスを倒した\n");
	}
	else
	{
		printf("世界崩壊\n");
	}

	//論理否定
	//! で条件を満たした、満たしてない、の判定を逆転させる
	 
	//if文の条件式、条件を書きづらいパターンが存在する
	//成功条件書きづらいが失敗条件はかける
	//失敗条件を書いてそれを逆転させる、という書き方
	int a = 100;
	if (!(a >= 100))
	{
		printf("aの値が100未満\n");
	}

	int b = 100;
	int c = 120;
	if (a > 100 || b > 100 || c > 100)
	{

	}
	if (a > 100 && b > 100 && c > 100)
	{

	}
	if (a > 100 || b >= 100 && c >= 100)
	{

	}
	if (!(a > 100 || b > 100) && c > 100)
	{

	}
	//横に長くなりすぎる場合は適宜開業を入れて見やすくする
	if (a > 100 ||
		b > 100 ||
		c > 100)
	{

	}

	return 0;
}