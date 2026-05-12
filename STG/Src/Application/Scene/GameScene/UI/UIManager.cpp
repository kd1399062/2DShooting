#include "UIManager.h"
#include "../../../Scene/GameScene/GameScene.h"

void C_UIManager::Init()
{
	m_tex.Load("Texture/Player/Player.png");
	m_size = { 64,64 };
	m_pos = { 100,100 };
}

void C_UIManager::Update()
{
	//==================== çsóÒ ====================
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, 1.0f, 1.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_UIManager::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, m_size.x, m_size.y), 1.0f);
}

void C_UIManager::Release()
{
}
