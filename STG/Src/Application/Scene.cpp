#include "main.h"
#include "Scene.h"
#include "Scene/TitleScene/TitleScene.h"
#include "Scene/GameScene/GameScene.h"

void Scene::Init()
{
	m_nowScene = std::make_shared<C_GameScene>();
	m_nowScene->Init();
}

void Scene::Draw2D()
{
	m_nowScene->Draw();
}

void Scene::Update()
{
	m_nowScene->Update();
}

void Scene::Release()
{
	
}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}
