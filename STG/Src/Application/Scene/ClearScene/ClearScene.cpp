#include "ClearScene.h"
#include "../SceneManager.h"

void C_ClearScene::Init()
{
}

void C_ClearScene::Draw()
{
	SHADER.m_spriteShader.DrawString(-150, 100, "ゲームクリア", Math::Vector4(1, 1, 0, 1));
}

void C_ClearScene::Update()
{
	// エンターでゲームシーンへ遷移
	if (GetAsyncKeyState('X') & 0x8000)
	{
		C_SceneManager::Instance().SetNextScene(C_SceneManager::SceneType::Title);
	}
}

void C_ClearScene::Release()
{
}
