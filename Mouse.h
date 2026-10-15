#pragma once
#include "DxLib.h"
#include <cmath>

//	マウス
class Mouse
{
private:

	int center_x;
	int center_y;

	float deadZone = 2.0f;	//	揺れずれ補正
	float scale = 0.1f;		//	移動量補正

public:

	Mouse(){}
	//	コンストラクタ（マウス中心の初期化）
	Mouse(int cx, int cy,float arg_deadZone,float arg_scale)
		:center_x(cx),center_y(cy),deadZone(arg_deadZone),scale(arg_scale)
	{
		SetMousePoint(center_x, center_y);
	}

	//	ゲッター関数
	float GetMoveX()
	{
		//	マウス座標取得
		int mx, my;
		GetMousePoint(&mx, &my);
		//	現在のマウス座標から中心座標の差分を計算
		float moveX = (float)mx - (float)center_x;
		float moveY = (float)my - (float)center_y;

		// デッドゾーン（揺れ除去）ルートで距離を求める計算
		float len = std::sqrt(moveX * moveX + moveY * moveY);

		//	ある値になったらもとに戻す
		if (len < deadZone)
		{
			moveX = 0.0f;
			moveY = 0.0f;
		}
		//	感度調整（カメラの回転スピードがはやいため）
		moveX *= scale;
		moveY *= scale;

		//	カーソル中央に戻すように
		SetMousePoint(center_x, center_y);

		//	マウスX座標用を返す
		return moveX;
	}


};