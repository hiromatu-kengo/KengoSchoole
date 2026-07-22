#include<stdio.h>
#include<windows.h>

struct Player
{
	int job;//0：勇者１：戦士２：僧侶３：魔法使い

	int hp;
	int mp;
};

//値渡しで作成
void DispPlayerData(struct Player p)
{
	switch (p.job)
	{
	case 0:
		printf("勇者\n");
		break;
	case 1:
		printf("戦士\n");
		break;
	case 2:
		printf("僧侶\n");
		break;
	case 3:
		printf("魔法使い\n");
		break;
	default:
		printf("存在しない職業\n");
		break;
	}
	printf("HP: %d\n", p.hp);
	printf("MP: %d\n", p.mp);
}

//ポインタ渡し
//ポインタで渡す場合、構造体のサイズにかかわらず、
//常にポインタサイズである8Byteしかコピーが発生しない
void DispPlayerPtr(struct Player* pPlayer)
{
	//構造体のポインタから各メンバーにアクセスする場合、
	// . ではなく[->]を使用する
	// ->は[アロー演算子]と呼ぶ
	switch (pPlayer->job)
	{
	case 0:
		printf("勇者\n");
		break;
	case 1:
		printf("戦士\n");
		break;
	case 2:
		printf("僧侶\n");
		break;
	case 3:
		printf("魔法使い\n");
		break;
	default:
		printf("存在しない職業\n");
		break;
	}
	printf("HP: %d\n", pPlayer->hp);
	printf("MP: %d\n", pPlayer->mp);
}

//ポインタ渡しであれば関数から構造体のデータの変更できる
void OnDamage(struct Player* pPlayer, int damage)
{
	printf("%dダメージ受けた!\n", damage);
	pPlayer->hp -= damage;
}

int main()
{
	SetConsoleOutputCP(65001);		
	struct Player hero = { 0,200,50 };
//	DispPlayerData(hero);
	DispPlayerPtr(&hero);

	OnDamage(&hero, 50);//heroが５０ダメージ受ける

	DispPlayerPtr(&hero);//ダメージ受けた後のデータ表示

	return 0;
}