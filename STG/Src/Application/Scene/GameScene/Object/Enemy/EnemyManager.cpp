#include "EnemyManager.h"
#include "../../GameScene.h"
#include "../BaseObject.h"
#include "Enemy1/Enemy1.h"
#include "Enemy2/Enemy2.h"
#include "Enemy3/Enemy3.h"

void C_EnemyManager::Init()
{
	// 初回スポーン
	for (int i = 0; i < ENEMY1_MAX; i++)
	{
		SpawnEnemy1();
	}

	for (int i = 0; i < ENEMY2_MAX; i++)
	{
		SpawnEnemy2();
	}

	for (int i = 0; i < ENEMY3_MAX; i++)
	{
		SpawnEnemy3();
	}
}

void C_EnemyManager::Update()
{
	//==================== 敵スポーン処理 ====================
	// 常に最大数存在させる
	if (CountEnemy((int)C_BaseObject::ObjectType::Enemy1) < ENEMY1_MAX)
	{
		SpawnEnemy1();
	}

	if (CountEnemy((int)C_BaseObject::ObjectType::Enemy2) < ENEMY2_MAX)
	{
		SpawnEnemy2();
	}

	if (CountEnemy((int)C_BaseObject::ObjectType::Enemy3) < ENEMY3_MAX)
	{
		SpawnEnemy3();
	}
}

void C_EnemyManager::SpawnEnemy1()
{
	//==================== 座標計算 ====================
	Math::Vector2 enemyPos = { 0,0 };
	//enemyPos.x= 

	//==================== 敵生成 ====================
	std::shared_ptr<C_Enemy1> enemy;
	enemy = std::make_shared<C_Enemy1>();
	enemy->EnemyInit(EnemySpown());
	enemy->SetOwner(m_owner);
	m_owner->AddObject(enemy);
}

void C_EnemyManager::SpawnEnemy2()
{
	//==================== 座標計算 ====================

	//==================== 敵生成 ====================
	std::shared_ptr<C_Enemy2> enemy;
	enemy = std::make_shared<C_Enemy2>();
	enemy->EnemyInit(EnemySpown());
	enemy->SetOwner(m_owner);
	m_owner->AddObject(enemy);
}

void C_EnemyManager::SpawnEnemy3()
{
	//==================== 座標計算 ====================

	//==================== 敵生成 ====================
	std::shared_ptr<C_Enemy3> enemy;
	enemy = std::make_shared<C_Enemy3>();
	enemy->EnemyInit(EnemySpown());
	enemy->SetOwner(m_owner);
	m_owner->AddObject(enemy);
}

int C_EnemyManager::CountEnemy(int type)
{
	int count = 0;

	auto& list = m_owner->GetObjList();

	for (auto& obj : list)
	{
		if ((int)obj->GetObjType() == type)
		{
			count++;
		}
	}

	return count;
}

Math::Vector2 C_EnemyManager::EnemySpown()
{
	// スポーン位置
	Math::Vector2 enemyPos = { 0,0 };

	// 上下左右ランダム
	int dir = rand() % 4;

	switch (dir)
	{
	case 0: // 上
		enemyPos.x = (float)(rand() % 2560 - 1280);
		enemyPos.y = 800;
		break;

	case 1: // 下
		enemyPos.x = (float)(rand() % 2560 - 1280);
		enemyPos.y = -800;
		break;

	case 2: // 左
		enemyPos.x = -1400;
		enemyPos.y = (float)(rand() % 1440 - 720);
		break;

	case 3: // 右
		enemyPos.x = 1400;
		enemyPos.y = (float)(rand() % 1440 - 720);
		break;
	}

	return enemyPos;
}
