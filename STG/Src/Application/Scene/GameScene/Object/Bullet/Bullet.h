#pragma once
#include "../BaseObject.h"

class C_Bullet : public C_BaseObject
{
public:
	C_Bullet() {};
	~C_Bullet() override { Relese(); };

	void Init(Math::Vector2 pos, Math::Vector2 dir) override;	// ‰Šú‰»
	void Update()									override;	// XV
	void Draw()										override;	// •`‰æ
	bool IsAlive();												// ¶€”»’è
private:
	void Relese()									override;	// ‰ğ•ú

	const int ALIVE_MAX = 30;									// Å‘å¶‘¶ŠÔ
	int m_aliveTime;											// ¶‘¶ŠÔ
};