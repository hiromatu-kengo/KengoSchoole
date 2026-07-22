#include<stdio.h>
#include<windows.h>

//学生１人分のデータ
struct Student
{
	int no;
	float height;
	float weight;
};

//学生データを受け取って身長を表示する関数
void dispHeight(struct Student s)
{
	printf("出席番号%dの生徒の身長は%fcmです\n", s.no, s.height);
	return;
}

int main()
{
	SetConsoleOutputCP(65001);

	struct Student student1 = { 1,170.5f,58.0f };

	//構造体が12Byteなので12Byteデータが引数としてコピーされる
	//int型の３倍のデータコピー　->引数を渡すのにint型の3倍時間がかかる
	
	dispHeight(student1);

	return 0;
}