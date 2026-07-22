#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);

	int hp = 100 + 200;

	printf("初期HP: %d\n", hp);

	hp = -hp;	//-300
	printf("反転HP:%d\n", hp);
	hp = +hp;	//-300

	//インクリメント
	//変数の中身を1増やす
	hp++;	//-299
	printf
	("HP++:%d\n", hp);
	hp++;	//-298
	printf("HP++:%d\n", hp);

	//デクリメント
	//変数の中身を1減らす
	hp--;	//-299
	printf("HP--:%d\n", hp);
	--hp;	//インクリメント、デクリメントは演算子を前に置くこともできる（前置）
	printf("HP--:%d\n", hp);//-3000
	
	printf("-------------------\n");

	//インクリメント、デクリメント　前置と後置
	hp = 100;
	printf("HP++ = %d\n", hp++);	//後置の場合、変数の表示が行われたあと、インクリメント
	printf("hp=5d\n", hp);

	hp = 100;
	printf("++HP=%d", ++hp);	//前置の場合、インクリメントしてから変数の表示
	printf("HP=5d\n", hp);

	//↑のような書き方は前置、高知の違いをしっかり理解してないと待ちあえる
	//自分は割っていてもプログラムを見るほかの人がわかってもらえるとは限らない

	//この書き方だと表示してからインクリメント、なのが明白
	hp = 100;
	printf("HP=%d\n", hp);
	hp++;

	return 0;
}