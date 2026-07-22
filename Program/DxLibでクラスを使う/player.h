#pragma once

class Player
{
public:
	//初期化
	void Init();
	//終了処理
	void End();

	//毎フレーム行う処理
	void Update();
	void Draw();

private:
	int handle;//使用するグラフィック
	double angle;//回転量
	int x;
	int y;

};