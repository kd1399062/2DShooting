#include "Player.h"
#include "../Bullet/BulletManager.h"
#include "../../../../main.h"

void C_Player::Init()
{
	m_tex.Load("Texture/Player/Player.png");

	m_aliveFlg	= true;
	m_size		= { 64,64 };
	m_pos		= { 0,0 };
	m_speed		= 10;

	m_mouse.x = 0;
	m_mouse.y = 0;

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

	// 弾
	m_shot = std::make_shared<C_BulletManager>();
	m_shot->Init();

}

void C_Player::Update(Math::Vector2 scroll)
{
	//マウス座標関数
	GetMousePos(&m_mouse);

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

	if (m_scroll.x < m_scrollMin.x) m_scroll.x = m_scrollMin.x;
	if (m_scroll.x > m_scrollMax.x)m_scroll.x = m_scrollMax.x;
	if (m_scroll.y < m_scrollMin.y) m_scroll.y = m_scrollMin.y;
	if (m_scroll.y > m_scrollMax.y)m_scroll.y = m_scrollMax.y;

	//==================== 弾発射処理 ====================
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		// ワールド座標変更
		Math::Vector2 mouseWorld;

		mouseWorld.x = m_mouse.x + m_scroll.x;
		mouseWorld.y = m_mouse.y + m_scroll.y;

		m_shotDir = mouseWorld - m_pos;
		m_shotDir.Normalize();

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

void C_Player::GetMousePos(POINT* mousePos)
{
	GetCursorPos(mousePos);
	ScreenToClient(APP.m_window.GetWndHandle(), mousePos);
	mousePos->x -= WINDOW_WIDTH / 2;
	mousePos->y -= WINDOW_HIGHT / 2;
	mousePos->y *= -1;
}


