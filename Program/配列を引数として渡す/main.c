#include<stdio.h>
#include<windows.h>

//配列を受け取っているように見えるが、
//実際には配列の先頭アドレスを受け取っている
//void dispHeight(float arrHeight[])//arr ->array略
void dispHeight(float arrHeight[])
{
	for (int i = 0; i < 3; i++)
	{
		printf("%d番目の生徒の身長は%fcmです\n", i + 1,arrHeight[i]);
	}
	return;
}

int main()
{
	SetConsoleOutputCP(65001);		

	float height[3] = { 170.5f,169.0f,178.5f };

	//配列名を引数として渡している
	//配列->配列全体の先頭アドレス　を引数として渡している！
	dispHeight(height);

	for (int i = 0;i < 3;i++)
	{
		printf("[%d] : %f\n", i + 1, height[i]);
	}

	return 0;
}