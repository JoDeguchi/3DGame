#pragma once
#include "Base.h"

//	一体目のプレイヤー
class PlayerOne
{
protected:

	Base pos;
	Base rot;

	//	静止モデル
	int base_model = -1;
	//	アニメモデル
	int anim_model;
	//	アニメーション関連
	int animIndex = 0;
	float animTotalTime = 0.0f;
	float animTime = 0.0f;

private:
public:

	void Init(const char* BasePath, const char* AnimPath);
	void Update();
	void AddRotation(float add);
	void Draw();
	VECTOR GetPos();
	float GetRotY();
	
};