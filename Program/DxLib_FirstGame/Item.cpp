#include "Item.h"
#include "DxLib.h"
#include "Game.h"

//定数定義
namespace
{
	//グラフィックの切り取りサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	//アニメーションの関連の定義
	constexpr int kAnimNum = 17;
	constexpr int kSingleAnimFrame = 4;	//アニメ1コマに書けるフレーム数

	//アニメーション1ループにかかるフレーム数
	constexpr int kAnimTotalFrame = kAnimNum * kSingleAnimFrame;

	//当たり判定の半径
	constexpr float kColRadius = 6.0f;
}

Item::Item() :
	m_graph(-1),
	m_x(0.0f),
	m_y(0.0f),
	m_animFrame(0),
	m_isExist(false)
{
}

Item::~Item()
{
}

void Item::Init()
{
	//	自分でロードするのではなく渡してもらったハンドルを使用する
//	m_graph = LoadGraph("image/Strawberry.png");

	//ランダムな位置に配置する
	m_x = GetRand(Game::kScreenWidth) - kWidth;
	m_y = GetRand(Game::kScreenHeight) - kHeight;

	//アニメーションが同期しないようにする
//	m_animFrame = GetRand(kAnimTotalFrame - 1);

	//存在する状態から開始
	m_isExist = true;
}

void Item::End()
{
	//	DeleteGraph(m_graph);
}

void Item::Update()
{
	//存在しないアイテムの処理は実行しない
	if (!m_isExist)return;

	m_animFrame++;
}

void Item::Draw()
{
	//存在しないアイテムは描画しない
	if (!m_isExist)return;

	int animNo = (m_animFrame % kAnimTotalFrame) / kSingleAnimFrame;

	DrawRectGraph(m_x, m_y,
		animNo * kWidth, 0, kWidth, kHeight,
		m_graph, true);

#ifdef _DEBUG
	//当たり判定のデバッグ表示
	DrawCircle(GetColCenterX(), GetColCenterY(), GetRadius(), GetColor(0, 0, 255), false);
#endif
}

float Item::GetColCenterX() const
{
	return m_x + kWidth / 2;
}

float Item::GetColCenterY() const
{
	return m_y + kHeight / 2;
}

float Item::GetRadius()const
{
	return kColRadius;
}

void Item::OnHit()
{
	m_isExist = false;
}
