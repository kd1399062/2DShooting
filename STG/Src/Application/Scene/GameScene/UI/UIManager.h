#pragma once

class C_GameScene;
class C_EnergyNum;

class C_UIManager
{
public:
	C_UIManager() {}
	~C_UIManager() {}

	void Init();
	void Draw();
	void Update();
	void Update(Math::Vector2 scroll);
	void Release();

	float GetEnergyNum() { return m_charge; }

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
	Math::Matrix    m_HpFrameMat;					// HPバー枠行列
	Math::Matrix    m_HpMat;						// HPバー行列
	Math::Vector2	m_HpSize		= { 96,24 };	// サイズ
	Math::Vector2	m_HpPos			= { 100,100 };	// 座標
	float m_hp = 0.0f;
	float m_maxHp = 0.0f;
	float m_hpRate = 0.0f;
	float hpWidth = 0.0f;

	// ロケットHPバー
	KdTexture		m_RHpFrameTex;					// HPバー枠テクスチャ
	KdTexture		m_RHpTex;						// HPバーテクスチャ
	Math::Matrix    m_RHpFrameMat;					// HPバー枠行列
	Math::Matrix    m_RHpMat;						// HPバー行列
	Math::Vector2	m_RHpSize = { 96,24 };	// サイズ
	Math::Vector2	m_RHpPos = { 100,100 };	// 座標
	float m_rhp = 0.0f;
	float m_maxRHp = 0.0f;
	float m_rhpRate = 0.0f;
	float rhpWidth = 0.0f;

	// 燃料チャージバー
	KdTexture		m_ChargeFrameTex;					// 燃料チャージバー枠テクスチャ
	KdTexture		m_ChargeTex;						// 燃料チャージバーテクスチャ
	Math::Matrix    m_ChargeFrameMat;					// 燃料チャージバー枠行列
	Math::Matrix    m_ChargeMat;						// 燃料チャージバー行列
	Math::Vector2	m_ChargeSize = { 96,24 };	// サイズ
	Math::Vector2	m_ChargePos = { 100,100 };	// 座標
	float m_charge = 0.0f;
	float m_maxCharge = 0.0f;
	float m_chargeRate = 0.0f;
	float chargeWidth = 0.0f;

	// 保持エナジーUI
	std::shared_ptr<C_EnergyNum> m_energyNum;
};
