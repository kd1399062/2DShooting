#pragma once

// 各シーンの基底クラス
class C_BaseScene
{
public:
	C_BaseScene() {}
	virtual ~C_BaseScene() {}

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Release();

private:

};