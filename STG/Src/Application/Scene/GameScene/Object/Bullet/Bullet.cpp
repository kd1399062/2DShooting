#include "Bullet.h"

void C_Bullet::Init(Math::Vector2 pos, Math::Vector2 dir, ObjectType obj)
{
	m_aliveFlg = true;
	m_aliveTime = ALIVE_MAX;
	m_pos = pos;
	m_dir = dir;

	// éwíËÇ≥ÇÍÇΩéÌóﬁÇ…âûÇ∂Çƒíeê∂ê¨
	switch (obj)
	{
	case ObjectType::Player:
		m_tex.Load("Texture/Bullet/pBullet.png");
		m_objType = ObjectType::PBullet;
		m_speed = 20;
		m_radius = 16.0f;
		m_aliveTime = 50;
		break;
	case ObjectType::Enemy1:
		m_tex.Load("Texture/Bullet/e1Bullet.png");
		m_objType = ObjectType::E1Bullet;
		m_speed = 10;
		m_radius = 16.0f;
		m_aliveTime = 60;
		break;
	case ObjectType::Enemy2:
		m_tex.Load("Texture/Bullet/e2Bullet.png");
		m_objType = ObjectType::E2Bullet;
		m_speed = 7;
		m_radius = 16.0f;
		m_aliveTime = 70;
		break;
	case ObjectType::Enemy3:
		m_tex.Load("Texture/Bullet/e3Bullet.png");
		m_objType = ObjectType::E3Bullet;
		m_speed = 10;
		m_radius = 16.0f;
		m_aliveTime = 50;
		break;
	}
}

void C_Bullet::Update(Math::Vector2 scroll)
{
	switch (m_objType)
	{
	case ObjectType::PBullet:
		m_pos += m_dir * m_speed;
		break;
	case ObjectType::E1Bullet:
		m_pos += m_dir * m_speed;
		break;
	case ObjectType::E2Bullet:
		m_pos += m_dir * m_speed;
		break;
	case ObjectType::E3Bullet:
		m_pos += m_dir * m_speed;
		break;
	}

	m_aliveTime--;

	// âÊñ äOÇ≈è¡Ç∑
	if (m_aliveTime <= 0)
	{
		m_aliveFlg = false;
	}

	//==================== çsóÒ ====================
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, 1.0f, 1.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - scroll.x, m_pos.y - scroll.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Bullet::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, m_radius * 2, m_radius * 2), 1.0f);
}

void C_Bullet::OnHit()
{
	m_aliveFlg = false;
}

void C_Bullet::Relese()
{
}
