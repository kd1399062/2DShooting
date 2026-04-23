#pragma once

#include "../BaseObject.h"

class C_Back : public C_BaseObject
{
public:
	C_Back() {}
	~C_Back() { Relese(); }

	void Init() override;		// ‰Šú‰»
	void Update() override;		// XV
	void Draw() override;		// •`‰æ
	
private:
	void Relese();		// ‰ğ•úˆ—
};