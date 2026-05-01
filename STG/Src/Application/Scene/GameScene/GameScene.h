#pragma once
#include "../BaseScene.h"

//==================== 前方宣言 ====================
class C_BaseObject;

class C_GameScene : public C_BaseScene
{
public:
	C_GameScene() {}
	~C_GameScene() {}

	void Init()		override;
	void Draw()		override;
	void Update()	override;
	
private:
	void Release()	override;

	//==================== クラスポインタ宣言 ====================
	std::shared_ptr<C_BaseObject> m_back = nullptr;
	std::shared_ptr<C_BaseObject> m_player = nullptr;
	std::shared_ptr<C_BaseObject> m_enemy1 = nullptr;
};