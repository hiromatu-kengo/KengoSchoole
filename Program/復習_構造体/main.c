#include<stdio.h>
#include<windows.h>



int main()
{
	SetConsoleOutputCP(65001);		

//	int playerHp[4];
//	int playerMp[4];
//	int playerAttack[4];
	//構造体
	//複数のデータを組み合わせた新しいデータ型を作る
	//プレイヤーのデータをメンバーとして持つ構造体を定義する
	struct player
	{
		int hp;
		int MP;
		int Attack;
	};
	//構造体をデータ型として持つ変数を作成する
	struct Player p;

	//構造体の各メンバーにアクセスするときは.でつなぐ
	p.hp = 200;
	p.mp = 50;
	p.attack = 100;

	printf("HP : %d", p.hp);
	printf("MP : %d", p.mp);
	printf("ATK : %d", p.attack);

	//構造体の各メンバーの初期化
	struct Player p2 = { 400,100,200 };
	printf("HP : %d", p.hp);
	printf("MP : %d", p.mp);
	printf("ATK : %d", p.attack);

	//構造体同士の代入
	//構造体が持つすべてのメンバーがコピーする
	struct Player p3;
	p3 = p;
	printf("HP : %d", p.hp);
	printf("MP : %d", p.mp);
	printf("ATK : %d", p.attack);



	return 0;
}