#pragma once

class C_BaseScene;

class C_SceneManager
{
public:
	// シーン情報
	enum SceneType
	{
		Title,		// タイトル
		Game,		// ゲーム
		Result		// リザルト
	};

	void PreUpdate();
	void Update();
	void Draw();

	// 次のシーンをセット
	void SetNextScene(SceneType _nextScene)
	{
		m_nextSceneType = _nextScene;
	}

	// 現在のシーンを取得
	SceneType GetCurrentScene() const
	{
		return m_currentSceneType;
	}
private:
	void Init();
	void Release();
	void ChangeScene(SceneType _SceneType);

	// 現在のシーン
	std::shared_ptr<C_BaseScene> m_CurrrentScene;

	// ゲーム開始時のシーンを設定
	SceneType m_currentSceneType = SceneType::Game;

	// 次のシーン
	SceneType m_nextSceneType = m_currentSceneType;


// シングルトン化
private:
	C_SceneManager() { Init(); }
	~C_SceneManager() { Release(); }

public:
	static C_SceneManager& Instance()
	{
		static C_SceneManager instance;
		return instance;
	}

};