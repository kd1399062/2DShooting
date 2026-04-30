#include "Bullet.h"

void C_Bullet::Init(Math::Vector2 pos, Math::Vector2 dir)
{
	m_tex.Load("Texture/Bullet/pBullet.png");

	m_pos = pos;
	m_dir = dir;
	m_speed = 20;
	m_aliveTime = ALIVE_MAX;

	m_aliveFlg = true;
}

void C_Bullet::Update()
{
	m_pos += m_dir * m_speed;

	m_aliveTime--;

	// âÊñ äOÇ≈è¡Ç∑
	if (m_aliveTime <= 0)
	{
		m_aliveFlg = false;
	}

	//==================== çsóÒ ====================
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, 1.0f, 1.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Bullet::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 64, 64), 1.0f);
}

bool C_Bullet::IsAlive()
{
	return m_aliveFlg;
}

void C_Bullet::Relese()
{
}
