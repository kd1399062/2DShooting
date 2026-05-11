#pragma once

class C_GameScene;

class C_EnemyManager
{

public:
	void Init();
	void Update();

	void SetOwner(C_GameScene* owner) { m_owner = owner; }

private:
	// 敵生成
	void SpawnEnemy1();
	void SpawnEnemy2();
	void SpawnEnemy3();

	// 敵総量カウント
	int CountEnemy(int type);

	// 敵スポーン位置
	Math::Vector2 EnemySpown();

	C_GameScene* m_owner = nullptr;

	// 敵総量
	const int ENEMY1_MAX = 10;
	const int ENEMY2_MAX = 5;
	const int ENEMY3_MAX = 2;
};