#pragma once
#include "../../BaseObject.h"

class C_GameScene;

// 行動遷移
enum class Enemy1State
{
	Spawn,	// 出現
	Search,	// 捜索
	Attack,	// 攻撃
	Dead	// 死亡
};

class C_Enemy1 : public C_BaseObject
{
public:
	C_Enemy1(){}
	~C_Enemy1() override { Relese(); }

	void Init() override;								// 初期化
	void EnemyInit(Math::Vector2 pos) override;			// 初期化
	void Update(Math::Vector2 scroll) override;			// 更新
	void Draw() override;								// 描画
	void OnHit(int damage) override;					// 当たり判定時の処理
	void Damage(int damage) override;					// ダメージ
	void Dead() override;								// 死亡

	void SetOwner(C_GameScene* _owner) { m_owner = _owner; }	// シーン情報をセット

private:
	void Relese()	override;							// 解放処理

	// ステート更新
	float DisPlayerChk();								// プレイヤーとの距離判定	
	void  StateChange(Enemy1State next);				// ステート変更
	void  SpawnUpdate();								// 出現更新
	void  SearchUpdate();								// 捜索更新
	void  AttackUpdate();								// 攻撃更新
	void  DeadUpdate();									// 死亡更新

	int m_stateTimer = 0;								// ステートタイマー
	Enemy1State m_state = Enemy1State::Spawn;			// 現在のステート
	Math::Vector2 m_searchDir = { 0,0 };				// search時の移動方向

	bool i = true;	// 仮移動フラグ

};
