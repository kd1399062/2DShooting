#include "Rocket.h"

void C_Rocket::Init()
{
	m_tex.Load("Texture/Rocket/Rocket1.png");

	m_objType = ObjectType::Rocket;
	m_aliveFlg = true;
	m_radius = 128.0f;
	m_size = { 256,256 };
	m_maxHp = 100;
	m_hp = m_maxHp;
	m_pos = { 0,-600+120 };
	m_speed = 10.0f;
	m_maxDmgCool = 10;
	m_dmgCool = 0;
	m_energy = 0;
}


void C_Rocket::Update(Math::Vector2 scroll)
{
	// HP最小値設定
	if (m_hp < 30)
	{
		m_hp = 30;
	}

	//==================== ダメージクールタイム処理 ====================
	if (m_dmgCool > 0)
	{
		m_dmgCool--;
	}
	if (m_dmgCool < 0)
	{
		m_dmgCool = 0;
	}

	if (m_energy > 0)
	{
		m_aliveFlg = false;
	}

	//==================== 行列 ====================
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, 1.0f, 1.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - scroll.x, m_pos.y - scroll.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Rocket::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, m_size.x, m_size.y), 1.0f);
}

void C_Rocket::AddCharge(int energy)
{
	m_energy += energy;

	if (m_energy >= m_energyMax)
	{
		// 最大燃料数で固定
		m_energy = m_energyMax;

		// クリア
		m_clearFlg = true;
	}
}

bool C_Rocket::GetClearFlg()
{
	return m_clearFlg;
}

void C_Rocket::OnHit(int damage)
{
	// 無敵時間が終わってないなら処理なし
	if (m_dmgCool > 0) return;

	// 無敵時間開始
	m_dmgCool = m_maxDmgCool;

	// ダメージ処理
	Damage(damage);
}

void C_Rocket::Damage(int damage)
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

void C_Rocket::Dead()
{
	m_aliveFlg = false;
}

void C_Rocket::Relese()
{
}
