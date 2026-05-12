#pragma once
#include "../BaseObject.h"

class C_GameScene;

class C_Rocket : public C_BaseObject
{
public:
	C_Rocket() {}
	~C_Rocket() override { Relese(); }

	void Init() override;										// 初期化
	void Update(Math::Vector2 scroll) override;					// 更新
	void Draw() override;										// 描画
	void OnHit(int damage) override;							// 当たり判定時の処理
	void Damage(int damage) override;							// ダメージ
	void Dead() override;										// 死亡

	void SetOwner(C_GameScene* _owner) { m_owner = _owner; }	// シーン情報をセット

	void AddCharge(int energy) override;									// 燃料チャージ
	bool GetClearFlg(); 

private:
	void Relese()	override;							// 解放処理

	C_GameScene* m_owner = nullptr;

	bool m_clearFlg = false;							// クリアフラグ

	// 燃料
	int m_energyMax = 100;

};
