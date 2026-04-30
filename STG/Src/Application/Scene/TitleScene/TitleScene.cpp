#include "TitleScene.h"
#include "../SceneManager.h"

void C_TitleScene::Init()
{
}

void C_TitleScene::Draw()
{
	SHADER.m_spriteShader.DrawString(0, 0, "タイトル", Math::Vector4(1, 1, 0, 1));

}

void C_TitleScene::Update()
{
	// エンターでゲームシーンへ遷移
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		C_SceneManager::Instance().SetNextScene(C_SceneManager::SceneType::Game);
	}
}

void C_TitleScene::Release()
{
}
