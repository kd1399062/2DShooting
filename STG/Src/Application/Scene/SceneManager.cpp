#include "SceneManager.h"
#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"


void C_SceneManager::Init()
{
	ChangeScene(m_currentSceneType);
}

void C_SceneManager::PreUpdate()
{
	// シーンを切り替え
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}
}

void C_SceneManager::Update()
{
	m_CurrrentScene->Update();
}

void C_SceneManager::Draw()
{
	m_CurrrentScene->Draw();
}

void C_SceneManager::Release()
{
}

void C_SceneManager::ChangeScene(SceneType _SceneType)
{
	// 次のシーンを作成し、現在のシーンにする
	switch (_SceneType)
	{
	case SceneType::Title:
	{
		m_CurrrentScene = std::make_shared<C_TitleScene>();
		break;
	}
	case SceneType::Game:
	{
		m_CurrrentScene = std::make_shared<C_GameScene>();
		break;
	}
	}

	m_currentSceneType = _SceneType;
}
