#pragma once
#include "../BaseObject.h"

class C_GameScene;

class C_Player : public C_BaseObject
{
public:
	C_Player() {}
	~C_Player() { Relese(); }

	void Init() override;						// 初期化
	void Update(Math::Vector2 pPos);						// 更新
	void Draw() override;						// 描画

	Math::Vector2 GetPlayerPos() { return m_pos; }		// プレイヤー座標取得
	Math::Vector2 GetScroll() { return m_scroll; }		// スクロール値取得


	Math::Vector2 m_scroll;
	Math::Vector2 m_scrollMax;
	Math::Vector2 m_scrollMin;

private:
	void Relese();		// 解放処理

	const float WINDOW_WIDTH = 1280;
	const float WINDOW_HIGHT = 720;
	const float MAP_WIDTH = 1280 * 4;
	const float MAP_HIGHT = 720 * 4;
};