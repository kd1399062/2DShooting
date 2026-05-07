#include "Enemy1.h"
#include "../../../../../Scene/GameScene/GameScene.h"
#include "../../Bullet/Bullet.h"

void C_Enemy1::Init()
{
	m_tex.Load("Texture/Enemy/Enemy1.png");

	m_objType   = ObjectType::Enemy1;
	m_aliveFlg	= true;
	m_size		= { 64,64 };
	m_pos		= { 100,0 };
	m_speed		= 10;
	m_radius = 32.0f;
	m_shotCoolMax = 3;
	m_shotCool = m_shotCoolMax;

	// à⁄ìÆîÕàÕê›íË
	m_posMax.x = MAP_WIDTH * 0.5 - m_size.x * 0.5;
	m_posMin.x = MAP_WIDTH * 0.5 * (-1) + m_size.x * 0.5;
	m_posMax.y = MAP_HIGHT * 0.5 - m_size.y * 0.5;
	m_posMin.y = MAP_HIGHT * 0.5 * (-1) + m_size.y * 0.5;
}

void C_Enemy1::Update(Math::Vector2 scroll)
{
	//==================== à⁄ìÆèàóù ====================
	// à⁄ìÆó èâä˙âª
	m_move = { 0,0 };

	// âºà⁄ìÆèàóù
	if (m_pos.x >= m_posMax.x) i = true;
	if (m_pos.x <= m_posMin.x) i = false;
	if (i)
	{
		m_move.x -= m_speed;
	}
	else
	{
		m_move.x += m_speed;
	}
	
	// ç¿ïWämíË
	m_pos += m_move;

	// à⁄ìÆîÕàÕêßå¿
	if (m_pos.x >= m_posMax.x) m_pos.x = m_posMax.x;
	if (m_pos.x <= m_posMin.x) m_pos.x = m_posMin.x;
	if (m_pos.y >= m_posMax.y) m_pos.y = m_posMax.y;
	if (m_pos.y <= m_posMin.y) m_pos.y = m_posMin.y;

	//==================== íeî≠éÀèàóù ====================
	ShotCoolTime();

	if (m_shotCool == m_shotCoolMax)
	{
		std::shared_ptr<C_Bullet> bullet;
		bullet = std::make_shared<C_Bullet>();
		bullet->Init(m_pos, m_shotDir, m_objType);
		m_owner->AddObject(bullet);

	}


	//==================== çsóÒ ====================
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, 1.0f, 1.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - scroll.x, m_pos.y - scroll.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Enemy1::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 64, 64), 1.0f);
}

void C_Enemy1::OnHit()
{
	m_aliveFlg = false;
}

void C_Enemy1::Relese()
{
}