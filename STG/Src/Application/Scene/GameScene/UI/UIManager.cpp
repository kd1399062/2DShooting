#include "UIManager.h"
#include "../../../Scene/GameScene/GameScene.h"

void C_UIManager::Init()
{
	// HPバー
	m_HpFrameTex.Load("Texture/UI/HpBarFrame.png");
	m_HpTex.Load("Texture/UI/HpBar.png");
	m_HpSize = { 96,24 };	// サイズ
	m_HpPos = { -300,325 };	// 座標
}

void C_UIManager::Update()
{
	//==================== 行列 ====================
	// HPバー
	m_scaleMat = Math::Matrix::CreateScale(5.0f, 1.0f, 1.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_HpPos.x, m_HpPos.y, 0);
	m_HpMat = m_scaleMat * m_transMat;
}

void C_UIManager::Draw()
{
	// HPバー
	SHADER.m_spriteShader.SetMatrix(m_HpMat);
	SHADER.m_spriteShader.DrawTex(&m_HpFrameTex, Math::Rectangle(0, 0, m_HpSize.x, m_HpSize.y), 1.0f);
	SHADER.m_spriteShader.DrawTex(&m_HpTex, Math::Rectangle(0, 0, m_HpSize.x, m_HpSize.y), 1.0f);
}

void C_UIManager::Release()
{
}
