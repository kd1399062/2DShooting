#pragma once
#include "../../BaseObject.h"

class C_BulletManager;

class C_Enemy1 : public C_BaseObject
{
public:
	C_Enemy1(){}
	~C_Enemy1() override { Relese(); }

	void Init() override;								// ‰Šú‰»
	void Update(Math::Vector2 scroll) override;			// XV
	void Draw() override;								// •`‰æ

private:
	void Relese()	override;							// ‰ğ•úˆ—

	bool i = true;

};
