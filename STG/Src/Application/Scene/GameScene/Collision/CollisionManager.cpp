#include "CollisionManager.h"
#include "../GameScene.h"
#include "../Object/BaseObject.h"

void C_CollisionManager::Init()
{
}

void C_CollisionManager::Update()
{
	// オブジェクトリスト取得
	auto& list = m_owner->GetObjList();

	for (size_t i = 0; i < list.size(); i++)
	{
		for (size_t j = i + 1; j < list.size(); j++)
		{
			auto& a = list[i];	// 対象1
			auto& b = list[j];	// 対象2

			// nullチェック
			if (!a || !b) continue;

			// 死亡済みは無視
			if (!a->GetAliveFlg() || !b->GetAliveFlg()) continue;

			Math::Vector2 v;	// 対象同士の距離
			float rad = 0;		// 対象の半径の合計

			//==================== 当たり判定 ====================
			// プレイヤー弾と各敵の当たり判定
			if (b->GetObjType() == C_BaseObject::ObjectType::PBullet)
			{
				if (a->GetObjType() == C_BaseObject::ObjectType::Enemy1 ||
					a->GetObjType() == C_BaseObject::ObjectType::Enemy2 ||
					a->GetObjType() == C_BaseObject::ObjectType::Enemy3)
				{
					v = a->GetPos() - b->GetPos();
					rad = a->GetRadius() + b->GetRadius();

					if (v.Length() < rad)
					{
						// HIT時の処理
						a->OnHit(5);
						b->OnHit();
					}
				}
			}

			// プレイヤーと各敵弾の当たり判定
			if (a->GetObjType() == C_BaseObject::ObjectType::Player)
			{
				if (b->GetObjType() == C_BaseObject::ObjectType::E1Bullet ||
					b->GetObjType() == C_BaseObject::ObjectType::E2Bullet ||
					b->GetObjType() == C_BaseObject::ObjectType::E3Bullet)
				{
					v = b->GetPos() - a->GetPos();
					rad = b->GetRadius() + a->GetRadius();

					if (v.Length() < rad)
					{
						// HIT時の処理
						b->OnHit();
						a->OnHit(5);
					}
				}
			}

			// プレイヤーと燃料の当たり判定
			if (a->GetObjType() == C_BaseObject::ObjectType::Player)
			{
				if (b->GetObjType() == C_BaseObject::ObjectType::Energy)
				{
					v = b->GetPos() - a->GetPos();
					rad = b->GetRadius() + a->GetRadius();

					if (v.Length() < rad)
					{
						// HIT時の処理
						a->SetEnergy(b->GetEnergy());
						b->OnHit();
					}
				}
			}

			// プレイヤーと燃料の当たり判定
			if (a->GetObjType() == C_BaseObject::ObjectType::Player)
			{
				if (b->GetObjType() == C_BaseObject::ObjectType::Rocket)
				{
					v = b->GetPos() - a->GetPos();
					rad = b->GetRadius() + a->GetRadius();

					if (v.Length() < rad)
					{
						// HIT時の処理
						b->AddCharge(a->GetEnergy());
						a->UseEnergy(a->GetEnergy());
					}
				}
			}
		}
	}
}

void C_CollisionManager::Draw()
{
}

void C_CollisionManager::Relese()
{
}
