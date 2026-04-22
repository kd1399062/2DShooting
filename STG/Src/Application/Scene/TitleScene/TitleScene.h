#pragma once
#include "../BaseScene.h"


class C_TitleScene : public C_BaseScene
{
public:
	C_TitleScene() {}
	~C_TitleScene() {}

	void Init() override;
	void Draw() override;
	void Update() override;
	void Release() override;

private:
	KdTexture m_tex;

};