#pragma once
class Player
{
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw();
	void Release();

	//使用するグラフィックハンドルの設定
	void SetIdleGraph(int handle) { m_idleGraph = handle; }
private:
	//使用するグラフィックハンドル
	int m_idleGraph;
};

