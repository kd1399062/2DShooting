#include "SceneManager.h"

#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"
#include "ClearScene/ClearScene.h"

void C_SceneManager::Init()
{
	// ゲーム開始時のシーン設定
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
	m_CurrentScene->Update();
}

void C_SceneManager::Draw()
{
	m_CurrentScene->Draw();
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
			m_CurrentScene = std::make_shared<C_TitleScene>();
			break;
		}
		case SceneType::Game:
		{
			m_CurrentScene = std::make_shared<C_GameScene>();
			break;
		}
		case SceneType::Clear:
		{
			m_CurrentScene = std::make_shared<C_ClearScene>();
			break;
		}
	}

	if (m_CurrentScene)
	{
		m_CurrentScene->Init();
	}

	m_currentSceneType = _SceneType;
}
