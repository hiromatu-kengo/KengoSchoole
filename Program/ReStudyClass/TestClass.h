#pragma once

class TestClass
{
public:
	//1.コンストラクタ
	//インスタンスを作成する際に必ず呼ぶ関数(クラスのインスタンス)
	TestClass()
	{
		//インスタンスを作成するときに実行したい処理
	}
	//2.デストラクタ
	//インスタンスを削除する際に呼ばれる関数
	virtual ~TestClass()
	{
		//インスタンスを消すときに実行したい処理
	}

	//4.メンバ関数(C++意外だとメソッド)
	int GetPosX()//getter : こちらからは送れないけど呼ばれたのかを確認したいときに使う
	{
		return PosX;
	}
	void GetPosY(int _posY)//setter
	{
		PosY = _posY;
	}

private:
	//3.メンバ変数
	int PosX = 0, PosY = 0;


};