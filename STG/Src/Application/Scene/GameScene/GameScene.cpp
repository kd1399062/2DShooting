#include "GameScene.h"
#include "Object/Player/Player.h"

void C_GameScene::Init()
{
	// プレイヤー
	m_player = std::make_shared<C_Player>();
	m_player->Init();
}

void C_GameScene::Draw()
{
	m_player->Draw();

}

void C_GameScene::Update()
{
	m_player->Update();
}

void C_GameScene::Release()
{
	//============================== 開放処理 ==============================
	
}
