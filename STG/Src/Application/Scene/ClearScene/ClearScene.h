#pragma once
#include "../BaseScene.h"

class C_ClearScene : public C_BaseScene
{
public:
	C_ClearScene() {}
	~C_ClearScene() { Release(); }

	void Init()		override;
	void Draw()		override;
	void Update()	override;

private:
	void Release()	override;
};