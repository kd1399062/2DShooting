#include "Player.h"
#include "../Bullet/BulletManager.h"

void C_Player::Init()
{
	m_tex.Load("Texture/Player/Player.png");

	m_pos = { 0,0 };

	m_aliveFlg = true;

	m_speed = 10;

	// 移動範囲
	m_pPosMax.x = MAP_WIDTH * 0.5 - PLAYER_SIZE.x * 0.5;
	m_pPosMin.x = MAP_WIDTH * 0.5 * (-1) + PLAYER_SIZE.x * 0.5;
	m_pPosMax.y = MAP_HIGHT * 0.5 - PLAYER_SIZE.y * 0.5;
	m_pPosMin.y = MAP_HIGHT * 0.5 * (-1) + PLAYER_SIZE.y * 0.5;

	// スクロール範囲
	m_scrollMax.x = WINDOW_WIDTH * 0.5;
	m_scrollMin.x = WINDOW_WIDTH * 0.5 * (-1);
	m_scrollMax.y = WINDOW_HIGHT * 0.5;
	m_scrollMin.y = WINDOW_HIGHT * 0.5 * (-1);

	// 弾
	m_shot = std::make_shared<C_BulletManager>();
	m_shot->Init();

}

void C_Player::Update(Math::Vector2 scroll)
{
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
	if (m_pos.x > m_pPosMax.x) m_pos.x = m_pPosMax.x;
	if (m_pos.x < m_pPosMin.x) m_pos.x = m_pPosMin.x;
	if (m_pos.y > m_pPosMax.y) m_pos.y = m_pPosMax.y;
	if (m_pos.y < m_pPosMin.y) m_pos.y = m_pPosMin.y;

	//==================== スクロール値計算 ====================
	m_scroll = m_pos;

	if (m_scroll.x < m_scrollMin.x) m_scroll.x = m_scrollMin.x;
	if (m_scroll.x > m_scrollMax.x)m_scroll.x = m_scrollMax.x;
	if (m_scroll.y < m_scrollMin.y) m_scroll.y = m_scrollMin.y;
	if (m_scroll.y > m_scrollMax.y)m_scroll.y = m_scrollMax.y;

	//==================== 弾発射処理 ====================
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_shot->CreateBullet(m_pos - m_scroll, m_shotDir);
	}


	// 弾
	m_shot->Update();


	//==================== 行列 ====================
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, 1.0f, 1.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - scroll.x, m_pos.y - scroll.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Player::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 64, 64), 1.0f);

	// 弾
	m_shot->Draw();
}

void C_Player::Relese()
{
}
