#include "BaseObject.h"

void C_BaseObject::Init()
{
}

void C_BaseObject::Init(Math::Vector2 pos, Math::Vector2 dir)
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

void C_BaseObject::Relese()
{
}
