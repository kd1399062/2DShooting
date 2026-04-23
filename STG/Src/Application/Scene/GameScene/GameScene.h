#pragma once
#include "../BaseScene.h"

//============================== 前方宣言 ==============================
class C_Player;

class C_GameScene : public C_BaseScene
{
public:
	C_GameScene() {}
	~C_GameScene() {}

	void Init() override;
	void Draw() override;
	void Update() override;
	void Release() override;

private:
	//============================== クラスポインタ宣言 ==============================
	std::shared_ptr<C_Player> m_player;

};