#pragma once
#include "../../BaseObject.h"

class C_GameScene;

// 行動遷移
enum class EnemyState
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
	void Update(Math::Vector2 scroll) override;			// 更新
	void Draw() override;								// 描画
	void OnHit() override;								// 当たり判定時の処理

	void SetOwner(C_GameScene* _owner) { m_owner = _owner; }	// シーン情報をセット

private:
	void Relese()	override;							// 解放処理

	// ステート更新
	float DisPlayerChk();								// プレイヤーとの距離判定	
	void  StateChange(EnemyState next);					// ステート変更
	void  SpawnUpdate();								
	// 出現更新
	void  SearchUpdate();								// 捜索更新
	void  AttackUpdate();								// 攻撃更新
	void  DeadUpdate();									// 死亡更新

	C_GameScene* m_owner = nullptr;

	int m_stateTimer = 0;								// ステートタイマー
	EnemyState m_state = EnemyState::Spawn;				// 現在のステート

	bool i = true;	// 仮移動フラグ

};
