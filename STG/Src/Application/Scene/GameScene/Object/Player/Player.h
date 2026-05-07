#pragma once
#include "../BaseObject.h"

class C_GameScene;

class C_Player : public C_BaseObject
{
public:
	C_Player() {}
	~C_Player() override { Relese(); }

	void Init() override;										// 初期化
	void Update(Math::Vector2 scroll) override;					// 更新
	void Draw() override;										// 描画
	void OnHit() override;										// 当たり判定時の処理

	void GetMousePos(POINT* mousePos);							// マウス座標関数
	void SetOwner(C_GameScene* _owner) { m_owner = _owner; }	// シーン情報をセット
	Math::Vector2 GetScroll() { return m_scroll; }				// スクロール値取得


private:
	void Relese()	override;									// 解放処理

	C_GameScene* m_owner = nullptr;

	// スクロール
	Math::Vector2 m_scroll;								// スクロール値
	Math::Vector2 m_scrollMax;							// 最大スクロール値
	Math::Vector2 m_scrollMin;							// 最小スクロール値

	POINT m_mouse;										// マウスポインタ

	Math::Vector2 m_shotDir = { 0,1 };					// 弾発射方向
};