#include "SceneMain.h"
#include"DxLib.h"

//定数マクロを使って定数を定義する
#define TEST_NUM 256

//定数ではないマクロのみを定義できる
#define MACRO_TEST

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
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
	m_frameCount++;
}

void SceneMain::Draw()
{
	//定数マクロを使用例
	DrawFormatString(256, 256, GetColor(255, 255, 255), "*** %d *** ", TEST_NUM);

	//マクロが定義されているか、されていないか、で処理を分けることができる
#ifdef MACRO_TEST
	//#ifdefとendifの間に書かれた処理はMACRO_TESTが定義されていないと通らない
	DrawString(256, 272, "MACRO_TESTがされています", GetColor(255, 255, 255));
#endif 
#ifndef MACRO_TEST
	//ifndefはifdefの逆でMACRO_TESTが定義されていない場合通る
	DrawString(256, 272, "MACRO_TESTがされています", GetColor(255, 255, 255));
#endif

#ifdef MACRO_TEST
	//MACRO_TESTが定義されていれば実行
#else
	//MACRO_TESTが定義されていなければ実行
#endif

	//Debug版でコンパイルすると胃は常に_DEBUGが定義された状態でコンパイルが始まる
#ifdef _DEBUG
	DrawString(256, 288, "Debug版ではこちらが実行される", GetColor(255, 255, 255));
#else
	DrawString(256, 288, "Release版ではこちらが実行される", GetColor(255, 255, 255));
#endif

#ifdef NDEBUG
	DrawString(256, 304, "Release版ではこちらが実行される", GetColor(255, 255, 255));
#endif

	DrawString(0, 0, "SceneMain", GetColor(255, 255, 255));
	DrawFormatString(0, 16, GetColor(255, 255, 255), "FRAME:%d", m_frameCount);
}