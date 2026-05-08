#include "Enemy1.h"
#include "../../../../../Scene/GameScene/GameScene.h"
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
	//==================== 移動処理 ====================
	// 移動量初期化
	m_move = { 0,0 };

	// 仮移動処理
	if (m_pos.x >= m_posMax.x) i = true;
	if (m_pos.x <= m_posMin.x) i = false;
	if (i)
	{
		m_move.x -= m_speed;
	}
	else
	{
		m_move.x += m_speed;
	}
	
	// 座標確定
	m_pos += m_move;

	// 移動範囲制限
	if (m_pos.x >= m_posMax.x) m_pos.x = m_posMax.x;
	if (m_pos.x <= m_posMin.x) m_pos.x = m_posMin.x;
	if (m_pos.y >= m_posMax.y) m_pos.y = m_posMax.y;
	if (m_pos.y <= m_posMin.y) m_pos.y = m_posMin.y;

	//==================== 弾発射処理 ====================
	ShotCoolTime();

	if (m_shotCool == m_shotCoolMax)
	{
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

		std::shared_ptr<C_Bullet> bullet;
		bullet = std::make_shared<C_Bullet>();
		bullet->Init(m_pos, m_shotDir, m_objType);
		m_owner->AddObject(bullet);
	}


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