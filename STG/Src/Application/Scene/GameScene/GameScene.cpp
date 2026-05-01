#include "GameScene.h"
#include "../SceneManager.h"
#include "Object/Back/Back.h"
#include "Object/Player/Player.h"
#include "Object/Enemy/Enemy1/Enemy1.h"
#include "Object/Bullet/Bullet.h"

void C_GameScene::Init()
{
	// 背景
	m_back = std::make_shared<C_Back>();
	m_back->Init();

	// プレイヤー
	m_player = std::make_shared<C_Player>();
	m_player->Init();
	
	m_enemy1 = std::make_shared<C_Enemy1>();
	m_enemy1->Init();

}

void C_GameScene::Draw()
{
	// 背景
	m_back->Draw();

	// プレイヤー
	m_player->Draw();

	m_enemy1->Draw();

}

void C_GameScene::Update()
{
	// プレイヤー
	m_player->Update(m_player->GetScroll());

	m_enemy1->Update(m_player->GetScroll());

	// 背景
	m_back->Update(m_player->GetScroll());


	// Zでタイトルシーンへ遷移
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		C_SceneManager::Instance().SetNextScene(C_SceneManager::SceneType::Title);
	}
}

void C_GameScene::Release()
{
	//==================== 開放処理 ====================
	
}
