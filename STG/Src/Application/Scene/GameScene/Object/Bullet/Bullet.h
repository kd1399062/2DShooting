#pragma once
#include "../BaseObject.h"

class C_Bullet : public C_BaseObject
{
public:
	C_Bullet() {};
	~C_Bullet() override { Relese(); };
	
	void Init(Math::Vector2 pos, Math::Vector2 dir, ObjectType obj)	override;
	void Update(Math::Vector2 scroll)								override;
	void Draw()														override;
	void OnHit()													override;

private:
	void Relese()													override;

	static const int ALIVE_MAX = 30;							// ç≈ëÂê∂ë∂éûä‘
	int m_aliveTime;											// ê∂ë∂éûä‘
};