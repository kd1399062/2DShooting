#include "BulletManager.h"
#include "Bullet.h"

void C_BulletManager::Init()
{

}

void C_BulletManager::Update()
{
    for (int i = 0; i < MAX_BULLET; i++)
    {
        if (m_bullets[i])
        {
            m_bullets[i]->Update();

            // Ž€‚ñ‚¾’e‚ðíœ
            if (!m_bullets[i]->IsAlive())
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
    for (int i = 0; i < MAX_BULLET; i++)
    {
        // ”z—ñ‚Ì’†g‚ªnull‚È‚çV‹K’e¶¬
        if (!m_bullets[i])
        {
            m_bullets[i] = std::make_shared<C_Bullet>();
            m_bullets[i]->Init(pos, dir);
            break;
        }
    }
}
