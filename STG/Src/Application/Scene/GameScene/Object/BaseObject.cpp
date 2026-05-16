#include "BaseObject.h"

void C_BaseObject::Init()
{
}

void C_BaseObject::EnemyInit(Math::Vector2 pos)
{
}

void C_BaseObject::Init(Math::Vector2 pos, Math::Vector2 dir, ObjectType obj)
{
}

void C_BaseObject::Update()
{
}

void C_BaseObject::Update(Math::Vector2 scroll)
{
}

void C_BaseObject::Draw()
{
}

void C_BaseObject::Anim()
{
	// クールタイム加算
	m_animCool++;

	// 一定時間ごとにアニメ変更
	if (m_animCool >= m_animCoolMax)
	{
		// 次のアニメへ
		m_animNum++;

		// 最大を超えたら最初へ
		if (m_animNum >= m_animMax)
		{
			m_animNum = 0;
		}

		// クールタイムリセット
		m_animCool = 0;
	}
}

void C_BaseObject::OnHit()
{
}

void C_BaseObject::OnHit(int damage)
{
}

void C_BaseObject::Damage(int damage)
{
}

void C_BaseObject::Dead()
{
}

Math::Vector2 C_BaseObject::GetScroll()
{
	return Math::Vector2();
}

void C_BaseObject::ShotCoolTime()
{
	if (m_shotCool <= m_shotCoolMax)
	{
		m_shotCool++;
	}
	else
	{
		m_shotCool = 0;
	}
}

void C_BaseObject::SetEnergy(int energyNum)
{
	m_energy += energyNum;
}

int C_BaseObject::GetEnergy()
{
	return m_energy;
}

bool C_BaseObject::GetClearFlg()
{
	return false;
}

void C_BaseObject::AddCharge(int energy)
{
}

void C_BaseObject::UseEnergy(int energy)
{
}

void C_BaseObject::ObjectFloat()
{
	m_floatTimer++;

	if (m_floatTimer < 20)
	{
		m_move.y -= 0.5f;
	}
	else if (m_floatTimer < 40)
	{
		m_move.y += 0.5f;
	}
	else
	{
		m_floatTimer = 0;
	}
}

void C_BaseObject::Relese()
{
}
