#include<stdio.h>
#include<windows.h>

//引数も戻り値も存在しない関数
// voed 関数 (void)
//voie = 無
//引数がvoid（戻り値がない）、引数もvoid(引数がない)関数を宣言していた

void DrawBorder(void)
{
	printf("~~~~~~~~\n");
}

// 引数を１つ受け取る関数
//void 関数名（引数のデータ型　仮引数の変数名）
void DrawMultiBorder(int count)
{
	for (int i = 0; i < count; i++)
	{
		DrawBorder();
	}
}

//引数を複数受け取る関数
//複数受け取る場合は各引数を , で区切る

//九九の表示
//x*yまで表示
void DrawMultTable(int x, int y)
{
	for (int i = 1; i <= y; i++)
	{
		for (int j = 1; j <= x; j++)
		{
			printf("%3d", i * j);
		}
		printf("\n");
	}
}

//戻り値の存在する関数
//関数名の前、今までvoidと書いていた部分に戻り値のデータ型を指定する
int GetScore(void)
{
	//戻り値が存在する関数は必ずreturnで値を返す必要がある
	return 10;
}

//floatの足し算を行う関数
float AddFloat(float val0, int val1)
{
	float ans = val0 + val1;
	return ans;
}

int main()
{
	SetConsoleOutputCP(65001);	

	//DrawBorder();
	DrawMultiBorder(4);

	DrawMultTable(9, 10);
	//DrawMultTable(8); //引数の数が合わないのでエラー

	int score = GetScore();
	printf("score = %d\n", score);

	float value = AddFlat(1.2f, 4.3f);
	printf("value = %f\n", value);

	return 0;
}