#pragma once
class Item
{
public:
	Item();
	~Item();

	void Init();
	void End();
	void Update();
	void Draw();

	//使用するぐらふぃくのハンドルを受け取る
	void SetHandle(int handle) { m_graph = handle; }

	//このアイテムが存在するか
	bool IsExist()const { return m_isExist; }

	//当たり判定実装用
	float GetColCenterX() const;
	float GetColCenterY() const;
	float GetRadius() const;

	//プレイヤーと当たった場合の処理
	void OnHit();

private:
	//グラフィックハンドル
	int m_graph;

	//位置情報
	float m_x;
	float m_y;

	//アニメーション関連
	int m_animFrame;

	//存在しているか
	bool m_isExist;
}; 