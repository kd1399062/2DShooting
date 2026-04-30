#pragma once

class C_Bullet;

class C_BulletManager
{
public:
    void Init();
    void Update();
    void Draw();

    // 弾生成
    void CreateBullet(Math::Vector2 pos, Math::Vector2 dir);

private:
    //画面サイズの設定
    static const int WINDOW_WIDTH = 1080;   // 画面幅
    static const int WINDOW_HIGHT = 720;    // 画面高さ

    static const int MAX_BULLET = 100;      // 弾上限
    static const int MAX_COOLTIME = 5;      // 発射クールタイム上限
    int m_coolTime;                         // 発射クールタイム

    std::shared_ptr<C_Bullet> m_bullets[MAX_BULLET];
};