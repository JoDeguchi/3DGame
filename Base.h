#pragma once
#include "Dxlib.h"

/// <summary>
/// 基盤
/// </summary>
class Base
{
public:
	float x, y, z;

	//	値セット
	void Set(float arg_x, float arg_y, float arg_z)
	{
		x = arg_x;
		y = arg_y;
		z = arg_z;
	}

	VECTOR VGet() const
	{
		VECTOR v;
		v.x = x;
		v.y = y;
		v.z = z;
		return v;
	}

	/*VECTOR Get() const
	{
		return VGet(x, y, z);
	}*/
};