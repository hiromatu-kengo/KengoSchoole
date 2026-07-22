#pragma once
class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	void End();
	void Update();
	void Draw();
	//シーン終了フラグの取得
	bool IsEnd() const { return m_isEnd; }

private:
	//タイトル終了フラグtrueならゲームに移行する
	bool m_isEnd;

	int m_frameCount;

	//タイトル風ロゴ
	int m_logoHandle;
	//フォント
	int m_fontHandle;
	//フェード管理
	int m_fadeFrame;
	int m_fadeSpeed; //-1 or +1
	//演出に使用するsinカーブで使う角度
	float m_sinAngle;
};

