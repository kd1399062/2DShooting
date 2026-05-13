#include "TitleScene.h"
#include "../SceneManager.h"

void C_TitleScene::Init()
{
	m_tex.Load("Texture/Title/title1.png");
}

void C_TitleScene::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, m_size.x, m_size.y), 1.0f);

	//SHADER.m_spriteShader.DrawString(-150, 100, "至急帰還せよ", Math::Vector4(1, 1, 0, 1));
	//SHADER.m_spriteShader.DrawString(-150, -150, "Enterでゲームスタート", Math::Vector4(1, 1, 0, 1));
}

void C_TitleScene::Update()
{
	// エンターでゲームシーンへ遷移
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		C_SceneManager::Instance().SetNextScene(C_SceneManager::SceneType::Game);
	}

	//==================== 行列 ====================
	m_scaleMat = Math::Matrix::CreateScale(1.0f, 1.0f, 1.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_TitleScene::Release()
{
	
}
