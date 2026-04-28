#include "Back.h"

void C_Back::Init()
{
	m_tex.Load("Texture/Back/Back.png");

	m_pos = { 0,0 };

	m_aliveFlg = true;
}

void C_Back::Update(Math::Vector2 scroll)
{
	// スクロール値を取得
	m_scroll = scroll;

	//============================== 行列 ==============================
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, 1.0f, 1.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - m_scroll.x, m_pos.y - m_scroll.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Back::Draw()
{
	Math::Rectangle rc;
	rc = { 0,0,64,64 };

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, MAP_WIDTH, MAP_HEGHT), 1.0f);

}

void C_Back::Relese()
{
}
