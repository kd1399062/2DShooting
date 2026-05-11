#include "Energy.h"

void C_Energy::Init(Math::Vector2 pos, int energyNum)
{
	m_tex.Load("Texture/Item/Energy.png");

	m_objType = ObjectType::Energy;
	m_aliveFlg = true;
	m_radius = 16.0f;
	m_size = { 32,32 };
	m_pos = pos;

	m_speed = 10.0f;
}

void C_Energy::Update(Math::Vector2 scroll)
{
	//==================== çsóÒ ====================
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, 1.0f, 1.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - scroll.x, m_pos.y - scroll.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Energy::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, m_size.x, m_size.y), 1.0f);
}

void C_Energy::OnHit()
{
	Dead();
}

void C_Energy::Dead()
{
	m_aliveFlg = false;
}

int C_Energy::GetEnergy()
{
	return m_energy;
}

void C_Energy::Relese()
{
}
