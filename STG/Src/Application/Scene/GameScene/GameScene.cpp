#include "GameScene.h"
#include "Object/Back/Back.h"
#include "Object/Player/Player.h"

void C_GameScene::Init()
{
	// 背景
	m_back = std::make_shared<C_Back>();
	m_back->Init();

	// プレイヤー
	m_player = std::make_shared<C_Player>();
	m_player->Init();

}

void C_GameScene::Draw()
{
	m_back->Draw();
	m_player->Draw();
}

void C_GameScene::Update()
{
	m_back->Update(m_player->GetPlayerPos());
	m_player->Update(m_player->GetPlayerPos());
}

void C_GameScene::Release()
{
	//============================== 開放処理 ==============================
	
}
