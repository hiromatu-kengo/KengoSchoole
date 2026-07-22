#include "SceneMain.h"
#include "DxLib.h"
#include"Game.h"



SceneMain::SceneMain() :
	m_playerIdleHandle(-1),
	m_playerRunHandle(-1),
	m_itemHandle(-1),
	m_trapHandle(-1),
	m_bgmHandle(-1),
	m_hitSeHandle(-1),
	m_uiFontHandle(-1),
	m_fadeAlpha(0),
	m_fadeSpeed(0),
	m_frameCount(0),
	m_isGameOver(false)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	//シーン内で使用するリソースのロード
	m_playerIdleHandle = LoadGraph("image/idle.png");
	m_playerRunHandle = LoadGraph("image/run.png");
	m_itemHandle = LoadGraph("image/Strawberry.png");
	m_trapHandle = LoadGraph("image/saw.png");

	//サウンドのロード
	m_hitSeHandle = LoadSoundMem("sound/hit.mp3");
	m_bgmHandle = LoadSoundMem("sound/bgm.mp3");

	//フォントの作成
	m_uiFontHandle = CreateFontToHandle("Magneto", 48, -1, -1);

	m_frameCount = 0;

	//ゲームオーバーじゃない状態から開始
	m_isGameOver = false;

	m_bg.Init();
	m_player.SetIdleGraph(m_playerIdleHandle);
	m_player.SetRunGraph(m_playerRunHandle);
	m_player.Init();
	for (int i = 0;i < kItemNum;i++)
	{
		//使用するグラフィックのハンドルを各Itemに渡す
		m_item[i].SetHandle(m_itemHandle);
		m_item[i].Init();
	}

	m_trap.SetHandle(m_trapHandle);
	m_trap.Init();

	//フェードイン開始
	m_fadeAlpha = 255;
	m_fadeSpeed = -8;


	//BGMを鳴らし始める
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
}

void SceneMain::End()
{
	//BGMの停止
	StopSoundMem(m_bgmHandle);

	m_bg.End();
	m_player.End();
	m_trap.End();
	for (int i = 0;i < kItemNum;i++)
	{
		m_item[i].End();
	}

	//シーンで使用したリソースをメモリから削除
	DeleteGraph(m_playerIdleHandle);
	DeleteGraph(m_playerRunHandle);
	DeleteGraph(m_itemHandle);
	DeleteGraph(m_trapHandle);
	//サウンドをメモリから削除
	DeleteSoundMem(m_hitSeHandle);
	DeleteSoundMem(m_bgmHandle);
	//フォントをメモリから削除
	DeleteFontToHandle(m_uiFontHandle);

}

void SceneMain::Update()
{
	m_frameCount++;
	//フェードの処理
	m_fadeAlpha += m_fadeSpeed;
	if (m_fadeAlpha < 0)
	{
		//フェードイン終了
		m_fadeAlpha = 0;
		m_fadeSpeed = 0;
	}
	if (m_fadeAlpha > 255)
	{
		//フェードアウトの終了
		m_fadeAlpha = 255;
		m_fadeSpeed = 0;
	}

	//ゲームの処理
	m_bg.Update();
	m_player.Update();
	for (int i = 0;i < kItemNum;i++)
	{
		m_item[i].Update();
	}
	m_trap.Update();
	//プレイヤーと各アイテムの当たり判定
	for (int i = 0;i < kItemNum;i++)
	{
		//存在しないアイテムとの当たり判定はとらない
		if (!m_item[i].IsExist()) continue;


		float dx = m_player.GetColCenterX() - m_item[i].GetColCenterX();
		float dy = m_player.GetColCenterY() - m_item[i].GetColCenterY();
		float sqDist = (dx * dx) + (dy * dy);

		float sumRadius = m_player.GetRadius() + m_item[i].GetRadius();
		if (sqDist < (sumRadius * sumRadius))
		{
			//当たった場合の処理
			m_item[i].OnHit();
			//	PlaySoundFile("sound/hit.mp3", DX_PLAYTYPE_BACK);
			PlaySoundMem(m_hitSeHandle, DX_PLAYTYPE_BACK);
		}
	}
	//プレイヤーとトラップの当たり判定
	{
		float dx = m_player.GetColCenterX() - m_trap.GetColCenterX();
		float dy = m_player.GetColCenterY() - m_trap.GetColCenterY();
		float sqDist = (dx * dx) + (dy * dy);

		float sumRadius = m_player.GetRadius() + m_trap.GetRadius();
		if (sqDist < (sumRadius * sumRadius))
		{
			printf("のこぎりに当たっている\n");
			m_isGameOver = true;
		}
	}



	//アイテムをすべてチェックして、存在するアイテムがない場合はゲームを終了する
	//アイテムの数が0ならゲーム終了
	if (GetItemNum() <= 0)
	{
		m_fadeSpeed = 8;
	}
}

void SceneMain::Draw()
{
	m_bg.Draw();
	m_player.Draw();
	for (int i = 0;i < kItemNum;i++)
	{
		m_item[i].Draw();
	}
	m_trap.Draw();


	//UIの表示 UIはゲームの最前面に表示させる
	int uiWidth = GetDrawFormatStringWidthToHandle(m_uiFontHandle, "%d", GetItemNum());
	DrawFormatStringToHandle(Game::kScreenWidth / 2 + 2 - uiWidth, 8 + 2, GetColor(255, 0, 255), m_uiFontHandle, "%d", GetItemNum());
	//DrawFormatString(Game::kScreenWidth / 2, 8, GetColor(255, 255, 255), "%d", GetItemNum());

	//ゲームオーバーの表示
	if (m_isGameOver)
	{
		int width = GetDrawStringWidthToHandle("GAME OVER", strlen("GAME OVER!"), m_uiFontHandle);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, Game::kScreenHeight / 2, "GAME OVER",GetColor(255,0,0), m_uiFontHandle);
	}

	//フェード処理
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString(0, 0, "SeceMain", GetColor(255, 255, 255));
	DrawFormatString(0, 16, GetColor(255, 255, 255), "FRAME:%d", m_frameCount);


}
int SceneMain::GetItemNum() const
{
	int itemNum = 0; //存在するアイテム数
	for (int i = 0;i < kItemNum;i++)
	{
		if (m_item[i].IsExist())
		{
			itemNum++;
		}
	}
	return itemNum;
}
