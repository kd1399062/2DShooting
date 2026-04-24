#pragma once
#include "../BaseObject.h"

class C_GameScene;

class C_Player : public C_BaseObject
{
public:
	C_Player() {}
	~C_Player() { Relese(); }

	void Init() override;								// 初期化
	void Update(Math::Vector2 pPos);					// 更新
	void Draw() override;								// 描画

	Math::Vector2 GetScroll() { return m_scroll; }		// スクロール値取得

	// 移動範囲
	Math::Vector2 m_pPosMax;		// 最大移動範囲
	Math::Vector2 m_pPosMin;		// 最小移動範囲

	// スクロール
	Math::Vector2 m_scroll;			// スクロール値
	Math::Vector2 m_scrollMax;		// 最大スクロール値
	Math::Vector2 m_scrollMin;		// 最小スクロール値

private:
	void Relese();		// 解放処理

	// 画面サイズ
	const float WINDOW_WIDTH = 1280;
	const float WINDOW_HIGHT = 720;

	// マップサイズ
	const float MAP_WIDTH = 1280 * 2;
	const float MAP_HIGHT = 720 * 2;

	// プレイヤーサイズ
	const Math::Vector2 PLAYER_SIZE = { 64,64 };

	Math::Vector2 m_move = { 0,0 };		// 移動量
	float m_pSpeed = 10;				// 移動速度

};