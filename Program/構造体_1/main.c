#include<stdio.h>
#include<windows.h>

int main()
{
	SetConsoleOutputCP(65001);		

	//構造体
	//自分でデータ型を作る
	//いくつかの型を組み合わせたもの

	//学生１人分のデータを格納するための構造体を定義する
	struct Student
	{
		int no;
		float height;
		float weight;
	};
	//Studentという名前の構造体は
	//メンバーとして、
	// int型の no
	// float型の height
	// float型の weight
	// という３つの変数を持ちますよ、
	//と定義している

	//この時点ではStudentというデータ型があるんですよ、
	// と言っているだけ
	// 実際に値を代入するときはStudent型の変数を作る必要がある

	//文法
	//struct 構造体名 変数名;
	struct Student student1;

	//構造体が持つ各メンバーにアクセスする
	//変数名.メンバー名 で各メンバーにアクセスする
	student1.no = 123;
	student1.height = 165.0f;
	student1.weight = 65.0f;


	//構造体の初期化
	//メンバー変数の並び順に値が入っていく
	printf("学生番号:%d\n",student1.no);
	printf("身長 : %f\n", student1.height);
	printf("体重 : %f\n", student1.weight);


	return 0;
}