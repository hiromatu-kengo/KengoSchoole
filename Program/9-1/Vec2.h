#pragma once
#include<cmath>

class Vec2
{
public:
	float x;
	float y;

public:
	//引数なしコンストラクタ　各成分を０で初期化
	Vec2() : x(0.0f), y(0.0f) {}
	//実態生成時に同時に初期化も可能
	Vec2(float x_, float y_) : x(x_), y(y_) {}

	//ベクトルの長さの２条を取得する
	float SqLength() const
	{
		return  (x * x) + (y * y);
	}

	//ベクトルの長さを取得する
	float Length() const
	{
		return sqrtf(SqLength());
	}

	//ベクトルの正規化
	void Normalize()
	{
		float len = Length();
		//長さが０のベクトルは正規化できないので処理を抜ける
		if (len == 0.0f)  return;
		x /= len;
		y /= len;
	}

};