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
			Math::Vector2 v;	// 対象同士の距離
			float rad = 0;		// 対象の半径の合計

			// 当たり判定
			if (a->GetObjType() == C_BaseObject::ObjectType::Enemy1 &&
				b->GetObjType() == C_BaseObject::ObjectType::PBullet)
			{
				v = a->GetPos() - b->GetPos();
				rad = a->GetRadius() + b->GetRadius();

				if (v.Length() < rad)
				{
					// HIT時の処理
					a->OnHit();
					b->OnHit();
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
