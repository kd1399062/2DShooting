#include "GameScene.h"
#include "../SceneManager.h"
#include "Collision/CollisionManager.h"
#include "Object/Back/Back.h"
#include "Object/Player/Player.h"
#include "Object/Enemy/Enemy1/Enemy1.h"
#include "Object/Bullet/Bullet.h"

void C_GameScene::Init()
{
	// 当たり判定
	m_collision = std::make_shared<C_CollisionManager>();
	m_collision->SetOwner(this);

	// 背景
	std::shared_ptr<C_Back> m_back;
	m_back = std::make_shared<C_Back>();
	m_back->Init();
	m_objList.push_back(m_back);

	// プレイヤー
	m_player = std::make_shared<C_Player>();
	m_player->Init();
	m_player->SetOwner(this);
	m_objList.push_back(m_player);

	// 敵１
	m_enemy1 = std::make_shared<C_Enemy1>();
	m_enemy1->Init();
	m_enemy1->SetOwner(this);
	m_objList.push_back(m_enemy1);
	
}

void C_GameScene::Draw()
{
	// 全オブジェクトの描画
	for (int i = 0;i < m_objList.size();i++)
	{
		m_objList[i]->Draw();
	}
}

void C_GameScene::Update()
{
	//==================== 無効オブジェクト削除処理 ====================
	// イテレータ作成 auto版
	auto it = m_objList.begin();

	while (it != m_objList.end())	// end() は 最後の要素の1個後ろを返す
	{
		// オブジェクトの有効チェック
		if ((*it)->GetAliveFlg() == false)
		{
			// 無効なオブジェクトをリストから削除
			it = m_objList.erase(it);
		}
		else
		{
			it++;	// 次の要素へイテレータを進める
		}
	}

	//==================== 更新処理 ====================
	// 全オブジェクトの更新
	for (int i = 0;i < m_objList.size();i++)
	{
		m_objList[i]->Update(m_player->GetScroll());
		m_objList[i]->Update();
	}




	m_collision->Update();

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
