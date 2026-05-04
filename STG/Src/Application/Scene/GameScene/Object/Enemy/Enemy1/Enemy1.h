#pragma once
#include "../../BaseObject.h"

class C_BulletManager;

class C_Enemy1 : public C_BaseObject
{
public:
	C_Enemy1(){}
	~C_Enemy1() override { Relese(); }

	void Init() override;								// 初期化
	void Update(Math::Vector2 scroll) override;			// 更新
	void Draw() override;								// 描画

private:
	void Relese()	override;							// 解放処理

	bool i = true;	// 仮移動フラグ

};
