#pragma once

class C_BaseScene;

// 各シーン名まとめ
enum SCENENAME
{
	S_TITLE,      // タイトル
	S_GAME,       // ゲーム中
	S_GAMEOVER,   // ゲームオーバー
	S_GAMECLEAR   // ゲームクリア
};

class Scene
{
public:

	void Init();
	void Draw2D();
	void Update();
	void Release();

	void ImGuiUpdate();

private:
	Scene() {}

	std::shared_ptr<C_BaseScene> m_nowScene;

	int test = 0;

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
