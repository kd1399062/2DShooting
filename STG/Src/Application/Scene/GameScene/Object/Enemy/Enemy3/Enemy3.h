#pragma once
#include "../../BaseObject.h"

class C_GameScene;

class C_Enemy3 : public C_BaseObject
{
public:
	C_Enemy3() {}
	~C_Enemy3() override { Relese(); }

	void Init() override;								// 初期化
	void Update(Math::Vector2 scroll) override;			// 更新
	void Draw() override;								// 描画
	void OnHit() override;								// 当たり判定時の処理
	void OnHit(int damage) override;					// 当たり判定時の処理
	void Damage(int damage) override;					// ダメージ
	void Dead() override;								// 死亡

	void SetOwner(C_GameScene* _owner) { m_owner = _owner; }	// シーン情報をセット

private:
	void Relese()	override;							// 解放処理

	C_GameScene* m_owner = nullptr;

	bool i = true;	// 仮移動フラグ

};
