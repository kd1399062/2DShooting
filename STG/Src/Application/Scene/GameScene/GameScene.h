#pragma once
#include "../BaseScene.h"

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
	KdTexture m_tex;

};