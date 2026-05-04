#pragma once
#include "../BaseObject.h"

class C_BulletManager;

class C_Player : public C_BaseObject
{
public:
	C_Player() {}
	~C_Player() override { Relese(); }

	void Init() override;								// 初期化
	void Update(Math::Vector2 scroll) override;			// 更新
	void Draw() override;								// 描画

	void GetMousePos(POINT* mousePos);					// マウス座標関数
	Math::Vector2 GetScroll() { return m_scroll; }		// スクロール値取得

private:
	void Relese()	override;							// 解放処理

	// スクロール
	Math::Vector2 m_scroll;								// スクロール値
	Math::Vector2 m_scrollMax;							// 最大スクロール値
	Math::Vector2 m_scrollMin;							// 最小スクロール値

	POINT m_mouse;										// マウスポインタ

	// 弾
	Math::Vector2 m_shotDir = { 0,1 };					// 弾発射方向
	std::shared_ptr<C_BulletManager> m_shot = nullptr;
};