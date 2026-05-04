#pragma once
#include "../BaseScene.h"

//==================== 前方宣言 ====================
class C_BaseObject;
class C_Player;

class C_GameScene : public C_BaseScene
{
public:
	C_GameScene() {}
	~C_GameScene() { Release(); }

	void Init()		override;
	void Draw()		override;
	void Update()	override;

	// 全オブジェクトの情報を取得する
	std::vector<std::shared_ptr<C_BaseObject>> GetObjList()
	{
		return m_objList;
	}

	// オブジェクトリストにオブジェクトを追加する
	void AddObject(std::shared_ptr<C_BaseObject> _obj)
	{
		// リストの末尾に渡された要素を追加
		m_objList.push_back(_obj);
	}
	
private:
	void Release()	override;

	//==================== クラスポインタ宣言 ====================
	// 
	// 全オブジェクトを可変長配列で管理する
	std::vector<std::shared_ptr<C_BaseObject>> m_objList;

	std::shared_ptr<C_Player> m_player;
};