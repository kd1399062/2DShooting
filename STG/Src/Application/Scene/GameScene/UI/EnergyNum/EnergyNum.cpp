#include "EnergyNum.h"

void C_EnergyNum::Init()
{
	// 保持エネルギー数
	m_tex.Load("Texture/UI/Number/number.png");

	for (int i = 0;i < NUM_MAX;i++)
	{
		if (i == 0)
		{
			m_pos[i] = { 600,300 };
		}
		else
		{
			m_pos[i].x = m_pos[i - 1].x - m_size.x * 2;
			m_pos[i].y = 300;
		}
	}
	// エネルギーマーク
	m_eneTex.Load("Texture/Item/ene.png");
	m_enePos = { 415,303 };
}

void C_EnergyNum::Update()
{
	//==================== 行列 ====================
	// 保持エネルギー数
	for (int i = 0;i < NUM_MAX;i++)
	{
		m_scaleMat = Math::Matrix::CreateScale(m_scaleX, m_scaleX, 1.0f);
		m_transMat = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0);
		m_mat[i] = m_scaleMat * m_transMat;
	}
	// エネルギーマーク
	m_scaleMat = Math::Matrix::CreateScale(m_eneScaleX, m_eneScaleX, 1.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_enePos.x, m_enePos.y, 0);
	m_eneMat = m_scaleMat * m_transMat;
}

void C_EnergyNum::Draw()
{
	// 保持エネルギー数
	for (int i = 0;i < NUM_MAX;i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat[i]);
		SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(m_size.x * i, 0, m_size.x, m_size.y), 1.0f);
	}
	// エネルギーマーク
	SHADER.m_spriteShader.SetMatrix(m_eneMat);
	SHADER.m_spriteShader.DrawTex(&m_eneTex, Math::Rectangle(m_eneSize.x, 0, m_eneSize.x, m_eneSize.y), 1.0f);
}

void C_EnergyNum::Release()
{
}
