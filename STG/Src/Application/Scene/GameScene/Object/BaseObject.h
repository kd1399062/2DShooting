#pragma once

class C_GameScene;

// 各オブジェクトの基底クラス
class C_BaseObject
{
public:
	// オブジェクトの種類
	enum class ObjectType
	{
		None,		// なし
		Back,		// 背景
		Player,		// プレイヤー
		Enemy1,		// 敵1
		Enemy2,		// 敵2
		Enemy3,		// 敵3
		PBullet,	// プレイヤー弾
		E1Bullet,	// 敵1弾
		E2Bullet,	// 敵2弾
		E3Bullet,	// 敵3弾
	};

	C_BaseObject() {}
	virtual ~C_BaseObject() { Relese(); }

	virtual void Init();														// 初期化
	virtual void Init(Math::Vector2 pos, Math::Vector2 dir, ObjectType obj);	// Bullet用初期化 (生成座標 発射方向 弾の種類)
	virtual void Update();														// 更新
	virtual void Update(Math::Vector2 scroll);									// スクロール込み更新
	virtual void Draw();														// 描画
	virtual void OnHit();														// 当たり判定処理
	virtual void OnHit(int damage);
	virtual void Damage(int damage);
	virtual void Dead();
	virtual Math::Vector2 GetScroll();											// スクロール値取得
	virtual void ShotCoolTime();												// 弾発射クールタイム計算

	bool GetAliveFlg() { return m_aliveFlg; }									// 生存フラグ取得
	float GetRadius() { return m_radius; }										// 半径取得
	Math::Vector2 GetPos() { return m_pos; }									// 座標取得
	ObjectType GetObjType() const { return m_objType; }							// オブジェクトタイプ取得

	void SetOwner(C_GameScene* _owner) { m_owner = _owner; }					// シーン情報をセット

protected:
	virtual void Relese();														// 解放

	// 画面サイズ
	const float WINDOW_WIDTH = 1280;			// 画面幅
	const float WINDOW_HIGHT = 720;				// 画面高さ

	// マップサイズ
	const float MAP_WIDTH = WINDOW_WIDTH * 2;	// マップ幅
	const float MAP_HIGHT = WINDOW_HIGHT * 2;	// マップ高さ

	// オーナー
	C_GameScene* m_owner = nullptr;

	// オブジェクトの種類
	ObjectType		m_objType = ObjectType::None;

	KdTexture		m_tex;							// テクスチャ
	Math::Vector2	m_pos			= { 0,0 };		// 座標
	Math::Vector2   m_posMax		= { 0,0 };		// 最大移動範囲
	Math::Vector2   m_posMin		= { 0,0 };		// 最小移動範囲
	Math::Vector2	m_scroll		= { 0,0 };		// スクロール量
	Math::Vector2	m_move			= { 0,0 };		// 移動量
	Math::Vector2	m_dir			= { 0,0 };		// 方向
	Math::Vector2	m_size			= { 0,0 };		// サイズ
	Math::Matrix    m_scaleMat;						// 拡大行列
	Math::Matrix    m_transMat;						// 移動行列
	Math::Matrix    m_rotasionMat;					// 移動行列
	Math::Matrix    m_mat;							// 合成行列
	Math::Vector2	m_shotDir		= { 1,1 };		// 弾発射方向
	int				m_hp			= 1;			// HP
	int				m_maxHp			= 1;			// 最大HP
	int				m_dmgCool		= 1;			// ダメージクールタイム
	int				m_maxDmgCool	= 1;			// 最大ダメージクールタイム
	float           m_radius		= 1.0f;			// 半径
	float           m_scaleX		= 1.0f;			// 拡大率
	float           m_speed			= 1.0f;			// 移動速度
	bool			m_aliveFlg		= true;			// 生存フラグ
	int				m_shotCool		= 10;			// 弾発射クールタイム
	int				m_shotCoolMax	= 10;			// 最大弾発射クールタイム
};