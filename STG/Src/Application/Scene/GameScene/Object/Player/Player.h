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

	Math::Vector2 GetScroll() { return m_scroll; }		// スクロール値取得

	// スクロール
	Math::Vector2 m_scroll;								// スクロール値
	Math::Vector2 m_scrollMax;							// 最大スクロール値
	Math::Vector2 m_scrollMin;							// 最小スクロール値

	//マウス座標関数
	void GetMousePos(POINT* mousePos);
	POINT m_mouse;

private:
	void Relese()	override;							// 解放処理

	// プレイヤーサイズ
	//const Math::Vector2 PLAYER_SIZE = { 64,64 };
	

	Math::Vector2 m_shotDir = { 0,1 };					// 弾発射方向

	// 弾
	std::shared_ptr<C_BulletManager> m_shot = nullptr;
};