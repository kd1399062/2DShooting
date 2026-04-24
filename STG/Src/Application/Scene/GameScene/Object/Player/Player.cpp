#include "Player.h"

void C_Player::Init()
{
	m_tex.Load("Texture/Player/Player.png");

	m_pos = { 0,0 };

	m_aliveFlg = true;

	/*
	m_scrollMax.x = 
	m_scrollMin.x = 
	m_scrollMax.y = 
	m_scrollMin.y =
	*/
}

void C_Player::Update(Math::Vector2 pPos)
{
	//============================== à⁄ìÆèàóù ==============================
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pos.x -= 5;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pos.x += 5;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_pos.y += 5;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pos.y -= 5;
	}


	//============================== çsóÒ ==============================
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, 1.0f, 1.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - pPos.x, m_pos.y - pPos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Player::Draw()
{
	Math::Rectangle rc;
	rc = { 0,0,64,64 };

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 64, 64), 1.0f);

	char str[80];
	sprintf_s(str, "m_scroll.xÅF%f", m_pos.x);
	SHADER.m_spriteShader.DrawString(0, 300, str, Math::Vector4(0, 1, 0, 1));
	
}

void C_Player::Relese()
{
}
