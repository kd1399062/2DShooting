#include "Player.h"
#include "../Bullet/Bullet.h"
#include "../../../../main.h"
#include "../../../../Scene/GameScene/GameScene.h"

void C_Player::Init()
{
	m_tex.Load("Texture/Player/Player.png");

	m_objType		= ObjectType::Player;
	m_maxHp			= 10;
	m_hp			= m_maxHp;
	m_aliveFlg		= true;
	m_size			= { 64,64 };
	m_pos			= { 0,0 };
	m_speed			= 10.0f;
	m_maxDmgCool	= 10;
	m_dmgCool		= 0;
	m_shotCoolMax	= 3;
	m_shotCool		= m_shotCoolMax;
	m_radius		= 32.0f;
	m_mouse.x		= 0;
	m_mouse.y		= 0;
	m_energy		= 10;

	
	// 移動範囲設定
	m_posMax.x = MAP_WIDTH * 0.5 - m_size.x * 0.5;
	m_posMin.x = MAP_WIDTH * 0.5 * (-1) + m_size.x * 0.5;
	m_posMax.y = MAP_HIGHT * 0.5 - m_size.y * 0.5;
	m_posMin.y = MAP_HIGHT * 0.5 * (-1) + m_size.y * 0.5;

	// スクロール範囲設定
	m_scrollMax.x = WINDOW_WIDTH * 0.5;
	m_scrollMin.x = WINDOW_WIDTH * 0.5 * (-1);
	m_scrollMax.y = WINDOW_HIGHT * 0.5;
	m_scrollMin.y = WINDOW_HIGHT * 0.5 * (-1);
}

void C_Player::Update(Math::Vector2 scroll)
{
	//マウス座標関数
	GetMousePos(&m_mouse);

	//仮
	if (m_energy <= 0)
	{
		m_aliveFlg = false;
	}

	//==================== ダメージクールタイム処理 ====================
	if (m_dmgCool > 0)
	{
		m_dmgCool--;
	}

	//==================== 移動処理 ====================
	// 移動量初期化
	m_move = { 0,0 };

	// キー移動
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_move.x -= m_speed;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_move.x += m_speed;
	}
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_move.y += m_speed;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_move.y -= m_speed;
	}

	// 座標確定
	m_pos += m_move;

	// 移動範囲制限
	if (m_pos.x > m_posMax.x) m_pos.x = m_posMax.x;
	if (m_pos.x < m_posMin.x) m_pos.x = m_posMin.x;
	if (m_pos.y > m_posMax.y) m_pos.y = m_posMax.y;
	if (m_pos.y < m_posMin.y) m_pos.y = m_posMin.y;

	//==================== スクロール値計算 ====================
	m_scroll = m_pos;

	// スクロール範囲制限
	if (m_scroll.x < m_scrollMin.x) m_scroll.x = m_scrollMin.x;
	if (m_scroll.x > m_scrollMax.x)m_scroll.x = m_scrollMax.x;
	if (m_scroll.y < m_scrollMin.y) m_scroll.y = m_scrollMin.y;
	if (m_scroll.y > m_scrollMax.y)m_scroll.y = m_scrollMax.y;

	//==================== 弾発射処理 ====================
	ShotCoolTime();

	if (m_shotCool == m_shotCoolMax)
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			// ワールド座標変更
			Math::Vector2 mouseWorld;

			mouseWorld.x = m_mouse.x + m_scroll.x;
			mouseWorld.y = m_mouse.y + m_scroll.y;

			m_shotDir = mouseWorld - m_pos;
			m_shotDir.Normalize();

			std::shared_ptr<C_Bullet> bullet;
			bullet = std::make_shared<C_Bullet>();		// 生成
			bullet->Init(m_pos, m_shotDir,m_objType);	// 初期化
			m_owner->AddObject(bullet);					// シーンのオブジェクトリストへ追加
		}

	}

	//==================== 行列 ====================
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, 1.0f, 1.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - scroll.x, m_pos.y - scroll.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Player::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, m_size.x, m_size.y), 1.0f);
}

void C_Player::OnHit(int damage)
{
	// 無敵時間が終わってないなら処理なし
	if (m_dmgCool > 0) return;

	// 無敵時間開始
	m_dmgCool = m_maxDmgCool;

	// ダメージ処理
	//Damage(damage);
}

void C_Player::Damage(int damage)
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

void C_Player::Dead()
{
	m_aliveFlg = false;
}

void C_Player::Relese()
{
}

void C_Player::GetMousePos(POINT* mousePos)
{
	GetCursorPos(mousePos);
	ScreenToClient(APP.m_window.GetWndHandle(), mousePos);
	mousePos->x -= WINDOW_WIDTH / 2;
	mousePos->y -= WINDOW_HIGHT / 2;
	mousePos->y *= -1;
}

void C_Player::SetEnergy(int energyNum)
{
	m_energy += energyNum;
}

void C_Player::UseEnergy(int energyNum)
{
	m_energy -= energyNum;
}

