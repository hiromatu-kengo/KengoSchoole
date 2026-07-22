#pragma once
class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void End();
	void Update();
	void Draw();

private:
	int m_frameCount;

	//のこぎり表示
	int m_sawHandle;
	double m_sawAngle;

	//プレイヤー表示
	int m_playerHandle;
	double m_playerAngle;

};
