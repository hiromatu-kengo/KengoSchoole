#include "SceneMain.h"
#include"DxLib.h"

SceneMain::SceneMain() :
	m_frameCount(0)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	m_frameCount = 0;
	m_player.Init();
	m_enemy.Init();
}

void SceneMain::End()
{
	m_player.End();
	m_enemy.End();
}

void SceneMain::Update()
{
	m_frameCount++;
	m_player.Update();
	m_enemy.Update();

	//当たり判定

	//各円の中心間の距離を求めるために
	//X方向の距離とY方向の距離を計算する
	int dx = m_player.GetCenterX() - m_enemy.GetCenterX();
	int dy = m_player.GetCenterY() - m_enemy.GetCenterY();
	//距離の計算過程でdx,dyともに2条するので
	//dx,dyがマイナスになるのは気にしなくてもいい

	//三平方の定理を使って直線距離(斜辺)を求める
	float sqDist = (dx * dx) + (dy * dy);//距離の２条を求めた

	//平方根の計算をなくすため
	//距離の2条と半径の合計の２条　を使って比較を行う
	//ソースコードが見づらくなりそうなので半径の合計を別の変数に保存しておく
	int radSum = m_player.GetRadius() + m_enemy.GetRadius();

	if (sqDist < radSum * radSum)
	{
		m_enemy.OnCollision();
	}

	/*
	//ほしいのは距離なので距離の2条(sqDist)の平方根を求める
	float dist = sqrtf(sqDist);  //doubleなsqrtだがFloat活用のsprf関数を使う
	//中心点の距離と各円の半径の合計を比較する
	if (dist < (m_player.GetRadius() + m_enemy.GetRadius()))
	{
		//printfDx("当たっている\n");
		m_enemy.OnCollision();
	}
	*/
}

void SceneMain::Draw()
{
	DrawString(0, 0, "SceneMain", GetColor(255, 255, 255));
	DrawFormatString(0, 16, GetColor(255, 255, 255), "FRAME:%d", m_frameCount);

	m_player.Draw();
	m_enemy.Draw();
}