#pragma once

//class C_BaseScene;
class SceneManager;

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

	//std::shared_ptr<C_BaseScene> m_nowScene;

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
