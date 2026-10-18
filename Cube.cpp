#include "Cube.h"

void Cube::Init(const char* BathPath)
{
	//	画像読み込む
	base_model = MV1LoadModel(BathPath);
	
	//	描画位置
	pos.Set(-20.0f, 0.0f, 4.0f);
	rot.Set(0.0f, 0.0f, 0.0f);
	MV1SetPosition(base_model, VGet(pos.x, pos.y, pos.z));

	//	モデルスケール調整
	MV1SetScale(base_model, VGet(0.01f, 0.01f, 0.01f));
	
}

void Cube::Update()
{

}

void Cube::Draw()
{
	if (base_model != -1)
		MV1DrawModel(base_model);
}

VECTOR Cube::GetPos()
{
	return pos.VGet();
}

void Cube::SetPos(VECTOR newPos)
{
	// Cubeの座標を更新
	pos.Set(newPos.x, newPos.y, newPos.z);

	// モデルの表示位置を更新
	if (base_model != -1)
	{
		MV1SetPosition(base_model, newPos);
	}
}
