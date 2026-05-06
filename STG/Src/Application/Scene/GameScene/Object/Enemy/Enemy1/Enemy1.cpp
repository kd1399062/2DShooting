#include "Enemy1.h"
#include "../../Bullet/BulletManager.h"

void C_Enemy1::Init()
{
	m_tex.Load("Texture/Enemy/Enemy1.png");

	m_objType   = ObjectType::Enemy1;
	m_aliveFlg	= true;
	m_size		= { 64,64 };
	m_pos		= { 100,0 };
	m_speed		= 10;

	// ˆÚ“®”ÍˆÍÝ’è
	m_posMax.x = MAP_WIDTH * 0.5 - m_size.x * 0.5;
	m_posMin.x = MAP_WIDTH * 0.5 * (-1) + m_size.x * 0.5;
	m_posMax.y = MAP_HIGHT * 0.5 - m_size.y * 0.5;
	m_posMin.y = MAP_HIGHT * 0.5 * (-1) + m_size.y * 0.5;
}

void C_Enemy1::Update(Math::Vector2 scroll)
{
	//==================== ˆÚ“®ˆ— ====================
	// ˆÚ“®—Ê‰Šú‰»
	m_move = { 0,0 };

	// ‰¼ˆÚ“®ˆ—
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
	
	// À•WŠm’è
	m_pos += m_move;

	// ˆÚ“®”ÍˆÍ§ŒÀ
	if (m_pos.x >= m_posMax.x) m_pos.x = m_posMax.x;
	if (m_pos.x <= m_posMin.x) m_pos.x = m_posMin.x;
	if (m_pos.y >= m_posMax.y) m_pos.y = m_posMax.y;
	if (m_pos.y <= m_posMin.y) m_pos.y = m_posMin.y;

	//==================== s—ñ ====================
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, 1.0f, 1.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - scroll.x, m_pos.y - scroll.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Enemy1::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 64, 64), 1.0f);
}

void C_Enemy1::Relese()
{
}
