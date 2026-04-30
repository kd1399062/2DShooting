#pragma once

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

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
