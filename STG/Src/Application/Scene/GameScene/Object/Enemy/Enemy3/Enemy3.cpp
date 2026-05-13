#include "Enemy3.h"
#include "../../../../../Scene/GameScene/GameScene.h"
#include "../../Bullet/Bullet.h"
#include "../../Item/Energy/Energy.h"

void C_Enemy3::EnemyInit(Math::Vector2 pos)
{
	m_tex.Load("Texture/Enemy/Enemy3.png");

	m_objType = ObjectType::Enemy3;
	m_aliveFlg = true;
	m_maxHp = 5;
	m_hp = m_maxHp;
	m_size = { 64,64 };
	m_pos = pos;
	m_speed = 3;
	m_radius = 32.0f;
	m_maxDmgCool = 10;
	m_dmgCool = m_maxDmgCool;
	m_shotCoolMax = 20;
	m_shotCool = m_shotCoolMax;

	// 移動範囲設定
	m_posMax.x = MAP_WIDTH * 0.5 - m_size.x * 0.5;
	m_posMin.x = MAP_WIDTH * 0.5 * (-1) + m_size.x * 0.5;
	m_posMax.y = MAP_HIGHT * 0.5 - m_size.y * 0.5;
	m_posMin.y = (MAP_HIGHT - 240) * 0.5 * (-1) + m_size.y * 0.5;
}

void C_Enemy3::Update(Math::Vector2 scroll)
{
	// 移動量初期化
	m_move = { 0,0 };

	//==================== ダメージクールタイム処理 ====================
	if (m_dmgCool > 0)
	{
		m_dmgCool--;
	}

	//==================== ステート更新 ====================
	switch (m_state)
	{
	case Enemy3State::Spawn:
		SpawnUpdate();
		break;

	case Enemy3State::Search:
		SearchUpdate();
		break;

	case Enemy3State::Attack:
		AttackUpdate();
		break;

	case Enemy3State::Dead:
		DeadUpdate();
		break;
	}

	//==================== 移動処理 ====================
	// 座標確定
	m_pos += m_move;

	// 移動範囲制限
	if (m_pos.x >= m_posMax.x) m_pos.x = m_posMax.x;
	if (m_pos.x <= m_posMin.x) m_pos.x = m_posMin.x;
	if (m_pos.y >= m_posMax.y) m_pos.y = m_posMax.y;
	if (m_pos.y <= m_posMin.y) m_pos.y = m_posMin.y;

	//==================== 行列 ====================
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, 1.0f, 1.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - scroll.x, m_pos.y - scroll.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Enemy3::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, m_size.x, m_size.y), 1.0f);
}

void C_Enemy3::OnHit(int damage)
{
	// 無敵時間が終わってないなら処理なし
	if (m_dmgCool > 0) return;

	// 無敵時間開始
	m_dmgCool = m_maxDmgCool;

	// ダメージ処理
	Damage(damage);
}

void C_Enemy3::Damage(int damage)
{
	// ダメージ処理
	m_hp -= damage;

	// 死亡処理
	if (m_hp <= 0)
	{
		m_hp = 0;
		Dead();
	}
}

void C_Enemy3::Dead()
{
	//==================== 燃料ドロップ ====================
	std::shared_ptr<C_Energy> energy;
	energy = std::make_shared<C_Energy>();
	energy->Init(m_pos, 10);
	m_owner->AddObject(energy);

	m_aliveFlg = false;
}

void C_Enemy3::Relese()
{
}

float C_Enemy3::DisPlayerChk()
{
	// ロケット座標取得
	auto& list = m_owner->GetObjList();

	for (auto& obj : list)
	{
		if (obj->GetObjType() == C_BaseObject::ObjectType::Rocket)
		{
			Math::Vector2 v;
			v = obj->GetPos() - m_pos;

			return v.Length();
		}
	}

	return 99999.0f;
}

void C_Enemy3::StateChange(Enemy3State next)
{
	m_state = next;
	m_stateTimer = 0;
}

void C_Enemy3::SpawnUpdate()
{
	if (m_stateTimer <= 30)
	{
		m_stateTimer++;
	}
	else
	{
		// 捜索ステートに遷移
		StateChange(Enemy3State::Search);
	}
}

void C_Enemy3::SearchUpdate()
{
	//==================== ロケット座標取得 ====================
	auto& list = m_owner->GetObjList();
	for (size_t i = 0; i < list.size(); i++)
	{
		auto& obj = list[i];

		if (obj->GetObjType() == C_BaseObject::ObjectType::Rocket)
		{
			m_shotDir = obj->GetPos() - m_pos;
			m_shotDir.Normalize();
			break;
		}
	}

	//==================== 移動処理 ====================
	// プレイヤーとの距離が500以上なら追従
	if (DisPlayerChk() >= 600.0f)
	{
		m_move += (m_shotDir * 6.0f);
	}


	//==================== ステート遷移処理 ====================
	// プレイヤーが近づくと攻撃ステートに遷移
	if (DisPlayerChk() < 600.0f)
	{
		m_state = Enemy3State::Attack;
	}
}

void C_Enemy3::AttackUpdate()
{
	ShotCoolTime();		// 弾発射クールタイム計算

	//==================== ロケット座標取得 ====================
	auto& list = m_owner->GetObjList();
	for (size_t i = 0; i < list.size(); i++)
	{
		auto& obj = list[i];

		if (obj->GetObjType() == C_BaseObject::ObjectType::Rocket)
		{
			m_shotDir = obj->GetPos() - m_pos;
			m_shotDir.Normalize();
			break;
		}
	}

	//==================== 弾発射処理 ====================
	if (m_shotCool == m_shotCoolMax)
	{
		std::shared_ptr<C_Bullet> bullet;
		bullet = std::make_shared<C_Bullet>();
		bullet->Init(m_pos, m_shotDir, m_objType);
		m_owner->AddObject(bullet);
	}
}

void C_Enemy3::DeadUpdate()
{
}
