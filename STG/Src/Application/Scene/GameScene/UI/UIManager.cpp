#include "UIManager.h"
#include "../../../Scene/GameScene/GameScene.h"
#include "../Object/BaseObject.h"

void C_UIManager::Init()
{
	// HPバー
	m_HpFrameTex.Load("Texture/UI/HpBarFrame.png");
	m_HpTex.Load("Texture/UI/HpBar.png");
	m_HpSize = { 96,24 };	// サイズ
	m_HpPos = { -350,330 };	// 座標

	// ロケットHPバー
	m_RHpFrameTex.Load("Texture/UI/HpBarFrame.png");
	m_RHpTex.Load("Texture/UI/RocketHpBar.png");
	m_RHpSize = { 96,24 };	// サイズ
	m_RHpPos = { -350,300 };	// 座標
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

		// ロケットHP取得
		if (a->GetObjType() == C_BaseObject::ObjectType::Rocket)
		{
			m_maxRHp = a->GetMaxHp();
			m_rhp = a->GetHp();
			m_rhpRate = m_rhp / m_maxRHp;
			rhpWidth = (float)m_RHpSize.x * (float)m_rhpRate;
		}
	}

	//==================== 行列 ====================
	// HPバー
	m_scaleMat = Math::Matrix::CreateScale(5.0f, 1.0f, 1.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_HpPos.x, m_HpPos.y, 0);
	m_HpFrameMat = m_scaleMat * m_transMat;

	m_scaleMat = Math::Matrix::CreateScale(5.0f, 1.0f, 1.0f);
	float offsetX1 = 0.0f;
	offsetX1 = (m_HpSize.x - hpWidth) * 0.5f * 5.0f;
	m_transMat = Math::Matrix::CreateTranslation(m_HpPos.x - offsetX1, m_HpPos.y, 0);
	m_HpMat = m_scaleMat * m_transMat;

	// ロケットHPバー
	m_scaleMat = Math::Matrix::CreateScale(5.0f, 1.0f, 1.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_RHpPos.x, m_RHpPos.y, 0);
	m_RHpFrameMat = m_scaleMat * m_transMat;

	m_scaleMat = Math::Matrix::CreateScale(5.0f, 1.0f, 1.0f);
	float offsetX2 = 0.0f;
	offsetX2 = (m_RHpSize.x - rhpWidth) * 0.5f * 5.0f;
	m_transMat = Math::Matrix::CreateTranslation(m_RHpPos.x - offsetX2, m_RHpPos.y, 0);
	m_RHpMat = m_scaleMat * m_transMat;
}

void C_UIManager::Draw()
{
	// HPバー
	SHADER.m_spriteShader.SetMatrix(m_HpFrameMat);
	SHADER.m_spriteShader.DrawTex(&m_HpFrameTex, Math::Rectangle(0, 0, m_HpSize.x, m_HpSize.y), 1.0f);
	SHADER.m_spriteShader.SetMatrix(m_HpMat);
	SHADER.m_spriteShader.DrawTex(&m_HpTex, Math::Rectangle(0, 0, hpWidth, m_HpSize.y), 1.0f);

	// ロケットHPバー
	SHADER.m_spriteShader.SetMatrix(m_RHpFrameMat);
	SHADER.m_spriteShader.DrawTex(&m_RHpFrameTex, Math::Rectangle(0, 0, m_RHpSize.x, m_RHpSize.y), 1.0f);
	SHADER.m_spriteShader.SetMatrix(m_RHpMat);
	SHADER.m_spriteShader.DrawTex(&m_RHpTex, Math::Rectangle(0, 0, rhpWidth, m_RHpSize.y), 1.0f);
}

void C_UIManager::Release()
{
}
