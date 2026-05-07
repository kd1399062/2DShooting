#pragma once
#include "../BaseObject.h"

class C_Bullet : public C_BaseObject
{
public:
	C_Bullet() {};
	~C_Bullet() override { Relese(); };

	void Init(Math::Vector2 pos, Math::Vector2 dir) override;	// ‰Šú‰» (¶¬À•W ”­Ë•ûŒü)
	void Update(Math::Vector2 scroll)				override;	// XV
	void Draw()										override;	// •`‰æ
	void OnHit()									override;	// “–‚½‚è”»’è‚Ìˆ—

private:
	void Relese()									override;	// ‰ğ•ú

	static const int ALIVE_MAX = 30;							// Å‘å¶‘¶ŠÔ
	int m_aliveTime;											// ¶‘¶ŠÔ
};