#pragma once
#include "Base.h"

class Cube
{
protected:

	Base pos;
	Base rot;

	//	静止モデル
	int base_model = -1;

private:
public:

	void Init(const char* BasePath);
	void Update();
	void Draw();

	//	位置取得
	VECTOR GetPos();

	//	位置を変える
	void SetPos(VECTOR newPos);
};