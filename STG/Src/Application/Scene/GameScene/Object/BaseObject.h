#pragma once

// 各オブジェクトの基底クラス
class C_BaseObject
{
public:
	C_BaseObject() {}
	virtual ~C_BaseObject() { Relese(); }

	virtual void Init();							// 初期化
	virtual void Update();							// 通常更新
	virtual void Update(Math::Vector2 scroll);		// スクロール込み更新
	virtual void Draw();							// 描画

	virtual Math::Vector2 GetScroll();				// スクロール値取得
	
protected:
	virtual void Relese();							// 解放

	KdTexture		m_tex;				// テクスチャ
	Math::Vector2	m_pos;				// 座標
	Math::Matrix    m_scaleMat;			// 拡大行列
	Math::Matrix    m_transMat;			// 移動行列
	Math::Matrix    m_rotasionMat;		// 移動行列
	Math::Matrix    m_mat;				// 合成行列
	float           m_scaleX = 1.0f;	// 拡大率
	bool			m_aliveFlg = true;	// 生存フラグ
};