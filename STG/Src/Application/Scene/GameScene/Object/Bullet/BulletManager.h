#pragma once

class C_Bullet;

class C_BulletManager
{
public:
    void Init();
    void Update();
    void Draw();

    // íeê∂ê¨
    void CreateBullet(Math::Vector2 pos, Math::Vector2 dir);

private:
    static const int MAX_BULLET = 100;

    std::shared_ptr<C_Bullet> m_bullets[MAX_BULLET];
};