#include<stdio.h>
#include<windows.h>

//共用体
//hpとmpがメモリ上の同じ位置に配置される
//->hpを変更したらmp書き変わるし逆もまた叱り
union Player
{
	int hp;
	int mp;
};

//メンバーのサイズが違う場合
union Test
{
	int i;	  //4Byte
	double d; //8Byte
	char c;   //1Byte
};

int main()
{
	SetConsoleOutputCP(65001);		

	union Player p;
	p.hp = 100;
	p.mp = 50;

	printf("hp %d\n", p.hp);
	printf("mp %d\n", p.mp);

	//共用体を使用するときはメンバーの
	//いずれか１つのみしか使用できない

	//どうしてもデータサイズを小さくしたい場合などで使われる
	//通信など

	return 0;
}