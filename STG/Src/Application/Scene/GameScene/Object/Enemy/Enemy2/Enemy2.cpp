#include "Enemy2.h"
#include "../../../../../Scene/GameScene/GameScene.h"
#include "../../../Object/Player/Player.h"
#include "../../Bullet/Bullet.h"
#include "../../Item/Energy/Energy.h"

void C_Enemy2::EnemyInit(Math::Vector2 pos)
{
	m_tex.Load("Texture/Enemy/Enemy2.png");

	m_objType = ObjectType::Enemy2;
	m_aliveFlg = true;
	m_maxHp = 5;
	m_hp = m_maxHp;
	m_size = { 96,96 };
	m_pos = pos;
	m_speed = 10;
	m_radius = 48.0f;
	m_maxDmgCool = 10;
	m_dmgCool = m_maxDmgCool;
	m_shotCoolMax = 80;
	m_shotCool = m_shotCoolMax;

	// 移動範囲設定
	m_posMax.x = MAP_WIDTH * 0.5 - m_size.x * 0.5;
	m_posMin.x = MAP_WIDTH * 0.5 * (-1) + m_size.x * 0.5;
	m_posMax.y = MAP_HIGHT * 0.5 - m_size.y * 0.5;
	m_posMin.y = MAP_HIGHT * 0.5 * (-1) + m_size.y * 0.5;
}

void C_Enemy2::Update(Math::Vector2 scroll)
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
	case Enemy2State::Spawn:
		SpawnUpdate();
		break;

	case Enemy2State::Search:
		SearchUpdate();
		break;

	case Enemy2State::Attack:
		AttackUpdate();
		break;

	case Enemy2State::Dead:
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

void C_Enemy2::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, m_size.x, m_size.y), 1.0f);
}

void C_Enemy2::OnHit(int damage)
{
	// 無敵時間が終わってないなら処理なし
	if (m_dmgCool > 0) return;

	// 無敵時間開始
	m_dmgCool = m_maxDmgCool;

	// ダメージ処理
	Damage(damage);
}

void C_Enemy2::Damage(int damage)
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

void C_Enemy2::Dead()
{
	//==================== 燃料ドロップ ====================
	std::shared_ptr<C_Energy> energy;
	energy = std::make_shared<C_Energy>();
	energy->Init(m_pos, 20);
	m_owner->AddObject(energy);

	m_aliveFlg = false;
}

void C_Enemy2::Relese()
{
}

float C_Enemy2::DisPlayerChk()
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

void C_Enemy2::StateChange(Enemy2State next)
{
	m_state = next;
	m_stateTimer = 0;
}

void C_Enemy2::SpawnUpdate()
{
	if (m_stateTimer <= 30)
	{
		m_stateTimer++;
	}
	else
	{
		// 捜索ステートに遷移
		StateChange(Enemy2State::Search);
	}
}

void C_Enemy2::SearchUpdate()
{
	// タイマー減少
	m_stateTimer--;

	//==================== 移動処理 ====================
	if (m_stateTimer <= 0)
	{
		// タイマーリセット
		m_stateTimer = 45;

		int randX = rand() % 3 - 1;
		int randY = rand() % 3 - 1;

		m_searchDir = { (float)randX, (float)randY };

		// 正規化
		if (m_searchDir.LengthSquared() > 0)
		{
			m_searchDir.Normalize();
		}
	}

	// 移動量確定
	m_move = m_searchDir * 3.0f;

	//==================== ステート遷移処理 ====================
	// プレイヤーが近づくと攻撃ステートに遷移
	if (DisPlayerChk() < 600.0f)
	{
		m_state = Enemy2State::Attack;
	}
}

void C_Enemy2::AttackUpdate()
{
	ShotCoolTime();		// 弾発射クールタイム計算

	//==================== プレイヤー座標取得 ====================
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

	//==================== 移動処理 ====================
	// プレイヤーとの距離が300以上なら追従
	if (DisPlayerChk() >= 400.0f)
	{
		m_move += (m_shotDir * 6.0f);
	}


	//==================== 弾発射処理 ====================
	if (m_shotCool == m_shotCoolMax)
	{
		// プレイヤー座標取得
		auto& list = m_owner->GetObjList();
		for (size_t i = 0; i < list.size(); i++)
		{
			auto& player = list[i];

			if (player->GetObjType() == C_BaseObject::ObjectType::Player)
			{
				m_shotDir = player->GetPos() - m_pos;
				m_shotDir.Normalize();
				break;
			}
		}

		// 真ん中
		Math::Vector2 centerDir = m_shotDir;

		// 左右方向作成
		Math::Vector2 leftDir;
		Math::Vector2 rightDir;

		// 左右弾の角度をラジアンに変更
		float angle = 15.0f * 3.141592f / 180.0f;

		// 左回転
		leftDir.x = centerDir.x * cosf(-angle) - centerDir.y * sinf(-angle);
		leftDir.y = centerDir.x * sinf(-angle) + centerDir.y * cosf(-angle);

		// 右回転
		rightDir.x = centerDir.x * cosf(angle) - centerDir.y * sinf(angle);
		rightDir.y = centerDir.x * sinf(angle) + centerDir.y * cosf(angle);

		//==================== 弾生成 ====================

		// 真ん中
		std::shared_ptr<C_Bullet> bulletCenter;
		bulletCenter = std::make_shared<C_Bullet>();
		bulletCenter->Init(m_pos, centerDir, m_objType);
		m_owner->AddObject(bulletCenter);

		// 左
		std::shared_ptr<C_Bullet> bulletLeft;
		bulletLeft = std::make_shared<C_Bullet>();
		bulletLeft->Init(m_pos, leftDir, m_objType);
		m_owner->AddObject(bulletLeft);

		// 右
		std::shared_ptr<C_Bullet> bulletRight;
		bulletRight = std::make_shared<C_Bullet>();
		bulletRight->Init(m_pos, rightDir, m_objType);
		m_owner->AddObject(bulletRight);
	}


	//==================== ステート遷移処理 ====================
	// プレイヤーが離れると捜索ステートに遷移
	if (DisPlayerChk() >= 600.0f)
	{
		m_state = Enemy2State::Search;
	}
}

void C_Enemy2::DeadUpdate()
{
}
