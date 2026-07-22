#pragma once

class Bg
{
public:
	//コンストラクタ　もメモリが確保されたとき、最初に呼ばれる
	Bg();
	//デストラクタ
	~Bg();
	void Init();
	void End();
	void Update();
	void Draw();


private:
	//グラフィックのハンドル
	int m_handle;
};