#pragma once

class C_GameScene;

class C_CollisionManager
{
public:
	C_CollisionManager() {};
	~C_CollisionManager() {};

	void Init();	// ‰Šú‰»
	void Update();	// XV
	void Draw();	// •`‰æ

	void SetOwner(C_GameScene* _owner) { m_owner = _owner; }

private:
	void Relese();	// ‰ğ•ú

	C_GameScene* m_owner = nullptr;
};