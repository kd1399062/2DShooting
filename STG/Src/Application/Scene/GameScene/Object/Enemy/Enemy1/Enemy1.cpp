#include "Enemy1.h"
#include "../../../../../Scene/GameScene/GameScene.h"
#include "../../../Object/Player/Player.h"
#include "../../Bullet/Bullet.h"

void C_Enemy1::Init()
{
	m_tex.Load("Texture/Enemy/Enemy1.png");

	m_objType   = ObjectType::Enemy1;
	m_aliveFlg	= true;
	m_size		= { 64,64 };
	m_pos		= { 0,100 };
	m_speed		= 10;
	m_radius = 32.0f;
	m_shotCoolMax = 3;
	m_shotCool = m_shotCoolMax;

	// 移動範囲設定
	m_posMax.x = MAP_WIDTH * 0.5 - m_size.x * 0.5;
	m_posMin.x = MAP_WIDTH * 0.5 * (-1) + m_size.x * 0.5;
	m_posMax.y = MAP_HIGHT * 0.5 - m_size.y * 0.5;
	m_posMin.y = MAP_HIGHT * 0.5 * (-1) + m_size.y * 0.5;
}

void C_Enemy1::Update(Math::Vector2 scroll)
{
	// 移動量初期化
	m_move = { 0,0 };

	switch (m_state)
	{
	case EnemyState::Spawn:
		SpawnUpdate();
		break;

	case EnemyState::Search:
		SearchUpdate();
		break;

	case EnemyState::Attack:
		AttackUpdate();
		break;

	case EnemyState::Dead:
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

void C_Enemy1::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, m_size.x, m_size.y), 1.0f);
}

void C_Enemy1::OnHit()
{
	m_aliveFlg = false;
}

void C_Enemy1::Relese()
{
}

float C_Enemy1::DisPlayerChk()
{
	// プレイヤー座標取得
	auto& list = m_owner->GetObjList();

	for (auto& obj : list)
	{
		if (obj->GetObjType() == C_BaseObject::ObjectType::Player)
		{
			Math::Vector2 v;
			v = obj->GetPos() - m_pos;

			return v.Length();
		}
	}

	return 99999.0f;
}

void C_Enemy1::StateChange(EnemyState next)
{
	m_state = next;
	m_stateTimer = 0;
}

void C_Enemy1::SpawnUpdate()
{
	if (m_stateTimer <= 30)
	{
		m_stateTimer++;
	}
	else
	{
		// 捜索ステートに遷移
		StateChange(EnemyState::Search);
	}
}

void C_Enemy1::SearchUpdate()
{
	// 仮移動処理
	if (m_pos.x >= m_posMax.x) i = true;
	if (m_pos.x <= m_posMin.x) i = false;
	if (i)
	{
		//m_move.x -= m_speed;
	}
	else
	{
		//m_move.x += m_speed;
	}

	//==================== ステート遷移処理 ====================
	// プレイヤーが近づくと攻撃ステートに遷移
	if (DisPlayerChk() < 800.0f)
	{
		m_state = EnemyState::Attack;
	}
}

void C_Enemy1::AttackUpdate()
{
	ShotCoolTime();

	// プレイヤー座標取得
	auto& list = m_owner->GetObjList();
	for (size_t i = 0; i < list.size(); i++)
	{
		auto& obj = list[i];

		if (obj->GetObjType() == C_BaseObject::ObjectType::Player)
		{
			m_shotDir = obj->GetPos() - m_pos;
			m_shotDir.Normalize();
			break;
		}
	}


	m_move += (m_shotDir * 3);

	//==================== 弾発射処理 ====================
	if (m_shotCool == m_shotCoolMax)
	{
		std::shared_ptr<C_Bullet> bullet;
		bullet = std::make_shared<C_Bullet>();
		bullet->Init(m_pos, m_shotDir, m_objType);
		m_owner->AddObject(bullet);
	}


	//==================== ステート遷移処理 ====================
	// プレイヤーが離れると捜索ステートに遷移
	if (DisPlayerChk() >= 800.0f)
	{
		m_state = EnemyState::Search;
	}
}

void C_Enemy1::DeadUpdate()
{
}
