#include "UIManager.h"
#include "../../../Scene/GameScene/GameScene.h"
#include "../Object/BaseObject.h"

void C_UIManager::Init()
{
	// HPバー
	m_HpFrameTex.Load("Texture/UI/HpBarFrame.png");
	m_HpTex.Load("Texture/UI/HpBar.png");
	m_HpSize = { 96,24 };	// サイズ
	m_HpPos = { -350,325 };	// 座標
}

void C_UIManager::Update()
{
	// オブジェクトリスト取得
	auto& list = m_owner->GetObjList();
	for (size_t i = 0; i < list.size(); i++)
	{
		auto& a = list[i];

		// HP取得
		if (a->GetObjType() == C_BaseObject::ObjectType::Player)
		{
			m_maxHp = a->GetMaxHp();
			m_hp = a->GetHp();
			m_hpRate = m_hp / m_maxHp;
			hpWidth = (float)m_HpSize.x * (float)m_hpRate;
		}
	}

	//==================== 行列 ====================
	// HPバー
	m_scaleMat = Math::Matrix::CreateScale(4.0f, 1.0f, 1.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_HpPos.x, m_HpPos.y, 0);
	m_HpFrameMat = m_scaleMat * m_transMat;

	m_scaleMat = Math::Matrix::CreateScale(4.0f, 1.0f, 1.0f);
	float offsetX = (m_HpSize.x - hpWidth) * 0.5f * 4.0f;

	m_transMat = Math::Matrix::CreateTranslation(
		m_HpPos.x - offsetX,
		m_HpPos.y,
		0);
	m_HpMat = m_scaleMat * m_transMat;
}

void C_UIManager::Draw()
{
	// HPバー
	SHADER.m_spriteShader.SetMatrix(m_HpFrameMat);
	SHADER.m_spriteShader.DrawTex(&m_HpFrameTex, Math::Rectangle(0, 0, m_HpSize.x, m_HpSize.y), 1.0f);

	SHADER.m_spriteShader.SetMatrix(m_HpMat);
	SHADER.m_spriteShader.DrawTex(&m_HpTex, Math::Rectangle(0, 0, hpWidth, m_HpSize.y), 1.0f);
}

void C_UIManager::Release()
{
}
