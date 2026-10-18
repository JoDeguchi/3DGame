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
	//	歩くモデル
	int walk_model = -1;
	//	アニメモデル
	int anim_model;
	//	アニメーション関連
	int animIndex = 0;
	float animTotalTime = 0.0f;
	float animTime = 0.0f;

private:

	//	押すアニメーション用
	int push_model = -1;
	int pushAnimIndex = 0;
	float pushAnimTime = 0.0f;
	float pushAnimTotalTime = 0.0f;
	//	押すかどうか
	bool isPushing = false;

	int currentAnimIndex = -1;
	float currentAnimTime = 0.0f;
	float currentAnimTotalTime = 0.0f;

public:

	void Init();
	void Update(float speed,float anim_speed);
	//	歩くアニメアタッチ
	void AttachWalkAnim();
	//	押すアニメアタッチ
	void AttachPushAnim();
	void AddRotation(float add);
	//	押し戻す
	void PushBack();
	void SetPush(bool flag);
	void Draw();
	VECTOR GetPos();
	float GetRotY();
	bool GetPush();
	//	前進する
	void MoveForward(float speed);

	void SetPos(VECTOR newPos);
	
};