#pragma once
#include "../../BaseObject.h"

class C_GameScene;

class C_Energy : public C_BaseObject
{
public:
	C_Energy() {}
	~C_Energy() override { Relese(); }

	void Init(Math::Vector2 pos,int energyNum);			// 初期化
	void Update(Math::Vector2 scroll) override;			// 更新
	void Draw() override;								// 描画
	void OnHit() override;								// 当たり判定時の処理
	void Dead() override;								// 死亡

	void SetOwner(C_GameScene* _owner) { m_owner = _owner; }	// シーン情報をセット

	int GetEnergy();										// 燃料取得

private:
	void Relese()	override;							// 解放処理

	C_GameScene* m_owner = nullptr;

	int m_energy;										// 燃料量

};
