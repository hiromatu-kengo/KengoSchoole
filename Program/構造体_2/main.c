#include<stdio.h>
#include<windows.h>

struct Student
{
	int no;
	float height;
	float weight;
};

int main()
{
	SetConsoleOutputCP(65001);		

	struct Student Pisuden1 = { 1,170.5f,58.0f };
	struct Student student2 = { 2,169.0f.,54.5f };

	return 0;
}