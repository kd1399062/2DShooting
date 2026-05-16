#pragma once

class C_GameScene;

class C_EnergyNum
{
public:
	C_EnergyNum() {}
	~C_EnergyNum() {}


	void Init();
	void Update();
	void Draw();
	void Release();

	void SetEnergy(float energy);

	void SetOwner(C_GameScene* _owner) { m_owner = _owner; }	// シーン情報をセット

private:
	C_GameScene* m_owner = nullptr;

	// エネルギー量
	static const int NUM_MAX = 5;
	int m_num[NUM_MAX];				// 桁の数字
	float m_charge = 0.0f;

	KdTexture		m_tex;					// テクスチャ
	Math::Vector2	m_pos[NUM_MAX];			// 座標
	Math::Vector2	m_size = { 16.0f,32.0f };		// サイズ
	Math::Matrix    m_scaleMat;				// 拡大行列
	Math::Matrix    m_transMat;				// 移動行列
	Math::Matrix    m_rotasionMat;			// 移動行列
	Math::Matrix	m_mat[NUM_MAX];			// 合成行列
	float           m_scaleX = 2.0f;		// 拡大率

	// エネルギーマーク
	KdTexture		m_eneTex;					// テクスチャ
	Math::Vector2	m_enePos;					// 座標
	Math::Vector2	m_eneSize = { 32.0f,32.0f };		// サイズ
	Math::Matrix	m_eneMat;					// 合成行列
	float           m_eneScaleX = 2.5f;			// 拡大率
	
};
