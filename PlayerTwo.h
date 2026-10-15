#pragma once
#pragma once
#include "Base.h"
#include "PlayerOne.h"

//	2体目のプレイヤー
class PlayerTwo:public PlayerOne
{

private:
public:

	void Init(const char* BasePath, const char* AnimPath);
	void Update();
	void Draw();
	VECTOR GetPos();
	float GetRotY();

};