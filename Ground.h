#pragma once
#include <string>
#include "DxLib.h"

//	地面
class Ground
{
protected:

	//	モデルハンドル
	int model_handle = -1;
	//	ファイルパス名
	std::string file_path = "";

public:
	//	デフォルトコンストラクタ
	Ground(){}
	//　コンストラクタ
	Ground(std::string arg_file_path, float arg_x, float arg_y, float arg_z)
	{
		Load_Model(arg_file_path);
		SetPos(arg_x, arg_y, arg_z);
	}
	//	モデル読み込み
	void Load_Model(std::string arg_file_path)
	{
		file_path = arg_file_path;
		model_handle = MV1LoadModel(file_path.c_str()); 
	}
	//	座標
	void SetPos(float arg_x,float arg_y,float arg_z)
	{
		MV1SetPosition(model_handle, VGet(arg_x, arg_y, arg_z));
	}
	//	描画
	virtual void Draw()
	{
		MV1DrawModel(model_handle);
	}
		

};