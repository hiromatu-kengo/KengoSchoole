#include<stdio.h>
#include<windows.h>

//テストの成績データ構造体
struct Test
{
	int kokugo;
	int sansu;
	int rika;
	int syakai;
};

//学生１人分のデータ
struct Student
{
	int no;
	float height;
	float weight;
	struct Test exam; //構造体Testを構造体のメンバーとして持つ
};

int main()
{
	SetConsoleOutputCP(65001);

	struct Student student1;
	student1.no = 1;
	student1.height = 170.5f;
	student1.weight = 70.5f;
	//メンバーの構造体が持つメンバーにアクセスする
	student1.exam.kokugo = 80;
	student1.exam.sansu = 80;
	student1.exam.rika = 80;
	student1.exam.syakai = 80;

	//メンバーとして構造体を持つ場合の初期化方法
	struct Student student2 = { 2,169.5f,54.5f,{80,70,90,95} };


	return 0;
}