#pragma once
#include "../BaseObject.h"

class C_Back : public C_BaseObject
{
public:
	C_Back() {}
	~C_Back() override { Relese(); }

	void Init() override;						// 初期化
	void Update(Math::Vector2 scroll) override;	// 更新
	void Draw() override;						// 描画
	
private:
	void Relese() override;						// 解放処理

	//スクロール
	float m_scrollX = 0;
	int scrollMin;
	int scrollMax;

};