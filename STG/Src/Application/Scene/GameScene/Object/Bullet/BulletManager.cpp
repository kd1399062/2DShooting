#include "BulletManager.h"
#include "Bullet.h"

void C_BulletManager::Init()
{
    m_coolTime = MAX_COOLTIME;
}

void C_BulletManager::Update()
{
    // 発射クールタイム設定
    if (m_coolTime > 0)
    {
        m_coolTime--;
    }
    else
    {
        m_coolTime = MAX_COOLTIME;
    }

    // 弾更新
    for (int i = 0; i < MAX_BULLET; i++)
    {
        if (m_bullets[i])
        {
            //m_bullets[i]->Update();

            // 死んだ弾を削除
            if (!m_bullets[i]->GetAliveFlg())
            {
                m_bullets[i] = nullptr;
            }
        }
    }
}

void C_BulletManager::Draw()
{
    for (int i = 0; i < MAX_BULLET; i++)
    {
        if (m_bullets[i])
        {
            m_bullets[i]->Draw();
        }
    }
}

void C_BulletManager::CreateBullet(Math::Vector2 pos, Math::Vector2 dir)
{
    if (m_coolTime > 0)return;

    for (int i = 0; i < MAX_BULLET; i++)
    {
        // 配列の中身がnullなら新規弾生成
        if (!m_bullets[i])
        {
            m_bullets[i] = std::make_shared<C_Bullet>();
            m_bullets[i]->Init(pos, dir);
            break;
        }
    }
}
