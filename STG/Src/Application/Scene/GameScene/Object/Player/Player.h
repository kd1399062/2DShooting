#pragma once

// 基本的にヘッダーファイルの中で
// 別のヘッダーファイルをインクルードするのはＮＧ
// 継承元クラスのヘッダーのみインクルードが必須なので可とする
#include "../BaseObject.h"

class C_Player : public C_BaseObject
{
public:
	C_Player() {}
	~C_Player() { Relese(); }

	void Update() override;		// 更新
	void Draw() override;		// 描画
	void Init() override;		// 初期化

private:
	void Relese();		// 解放処理
};