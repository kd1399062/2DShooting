#pragma once

class C_GameScene;

class C_UIManager
{
public:
	C_UIManager() {}
	~C_UIManager() {}

	void Init();
	void Draw();
	void Update();
	void Release();

	void SetOwner(C_GameScene* _owner) { m_owner = _owner; }	// シーン情報をセット

private:
	C_GameScene* m_owner = nullptr;

	Math::Vector2	m_scroll = { 0,0 };		// スクロール量
	Math::Vector2	m_move = { 0,0 };		// 移動量
	Math::Vector2	m_dir = { 0,0 };		// 方向
	Math::Vector2	m_size = { 0,0 };		// サイズ
	Math::Matrix    m_scaleMat;				// 拡大行列
	Math::Matrix    m_transMat;				// 移動行列
	Math::Matrix    m_rotasionMat;			// 移動行列
	Math::Matrix    m_mat;					// 合成行列
	float           m_scaleX = 1.0f;		// 拡大率

	// HPバー
	KdTexture		m_HpFrameTex;					// HPバー枠テクスチャ
	KdTexture		m_HpTex;						// HPバーテクスチャ
	Math::Matrix    m_HpMat;						// 合成行列
	Math::Vector2	m_HpSize		= { 96,24 };	// サイズ
	Math::Vector2	m_HpPos			= { 100,100 };	// 座標
};
