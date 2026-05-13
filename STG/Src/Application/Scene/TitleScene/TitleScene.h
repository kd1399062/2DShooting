#pragma once
#include "../BaseScene.h"


class C_TitleScene : public C_BaseScene
{
public:
	C_TitleScene() {}
	~C_TitleScene() {}

	void Init() override;
	void Draw() override;
	void Update() override;
	void Release() override;

private:
	KdTexture m_tex;
	Math::Matrix    m_scaleMat;						// 拡大行列
	Math::Matrix    m_transMat;						// 移動行列
	Math::Matrix    m_rotasionMat;					// 移動行列
	Math::Matrix    m_mat;							// 合成行列
	Math::Vector2	m_pos = { 0,0 };		// 座標
	Math::Vector2	m_size = { 1280,720 };		// 座標

};