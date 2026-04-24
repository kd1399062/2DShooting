#include "Player.h"

void C_Player::Init()
{
	m_tex.Load("Texture/Player/Player.png");

	m_pos = { 0,0 };

	m_aliveFlg = true;

	// スクロール範囲
	m_scrollMax.x = WINDOW_WIDTH * 0.5;
	m_scrollMin.x = WINDOW_WIDTH * 0.5 * (-1);
	m_scrollMax.y = WINDOW_HIGHT * 0.5;
	m_scrollMin.y = WINDOW_HIGHT * 0.5 * (-1);

}

void C_Player::Update(Math::Vector2 pPos)
{
	//============================== 移動処理 ==============================
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pos.x -= 5;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pos.x += 5;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_pos.y += 5;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pos.y -= 5;
	}

	//============================== スクロール値計算 ==============================
	m_scroll = m_pos;

	if (m_scroll.x < m_scrollMin.x) m_scroll.x = m_scrollMin.x;
	if (m_scroll.x > m_scrollMax.x)m_scroll.x = m_scrollMax.x;
	if (m_scroll.y < m_scrollMin.y) m_scroll.y = m_scrollMin.y;
	if (m_scroll.y > m_scrollMax.y)m_scroll.y = m_scrollMax.y;

	//============================== 行列 ==============================
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, 1.0f, 1.0f);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x - pPos.x, m_pos.y - pPos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Player::Draw()
{
	Math::Rectangle rc;
	rc = { 0,0,64,64 };

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 64, 64), 1.0f);

	char str1[80];
	sprintf_s(str1, "m_scroll.x：%f", m_scroll.x);
	SHADER.m_spriteShader.DrawString(0, 300, str1, Math::Vector4(0, 1, 0, 1));
	char str2[80];
	sprintf_s(str2, "m_scroll.y：%f", m_scroll.y);
	SHADER.m_spriteShader.DrawString(0, 150, str2, Math::Vector4(0, 1, 0, 1));
	
}

void C_Player::Relese()
{
}
