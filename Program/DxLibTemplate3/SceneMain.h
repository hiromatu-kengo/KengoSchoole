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

	//透明度
	int m_alpha;
	int m_alphaAcc;//透明度の変化量

	//フェードインアウト
	int m_fadeAlpha;
	int m_fadeAcc;

};
