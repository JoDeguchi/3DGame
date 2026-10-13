#include "PlayerOne.h"
#include <cmath>

void PlayerOne::Init(const char* BasePath, const char* AnimPath)
{
    //  モデル読み込み
    base_model = MV1LoadModel(BasePath);
    anim_model = MV1LoadModel(AnimPath);

    //  アニメーションアタッチ
    animIndex = MV1AttachAnim(base_model, 0, anim_model, FALSE);
    animTotalTime = MV1GetAttachAnimTotalTime(base_model, animIndex);
    animTime = 0.0f;

    //  初期位置と回転
	pos.Set(0.0f, 0.0f, 0.0f);
	rot.Set(0.0f, DX_PI_F, 0.0f);

    MV1SetScale(base_model, VGet(0.01f, 0.01f, 0.01f));
}

void PlayerOne::Update()
{

    // 左右キーで向きを変える
    if (CheckHitKey(KEY_INPUT_A))
    {
        rot.y -= 0.05f;   // 左回転
    }
    if (CheckHitKey(KEY_INPUT_D))
    {
        rot.y += 0.05f;   // 右回転
    }

    // プレイヤー本体を前進させる
    if (CheckHitKey(KEY_INPUT_W))
    {
        animTime += 0.4f;
        // rot.y の向きに合わせて移動
        pos.x -= sinf(rot.y) * 0.1f;
        pos.z -= cosf(rot.y) * 0.1f;

    }

    // プレイヤー本体を前進させる
    if (CheckHitKey(KEY_INPUT_S))
    {
        animTime += 0.2f;
        // rot.y の向きに合わせて移動
        pos.x += sinf(rot.y) * 0.05f;
        pos.z += cosf(rot.y) * 0.05f;

    }

    // アニメーションループ
    if (animTotalTime > 0.0f)
    {
        while (animTime >= animTotalTime)
        {
            animTime -= animTotalTime;
        }
    }

    // アニメーション適用
    MV1SetAttachAnimTime(base_model, animIndex, animTime);

    // 位置更新
    pos.Set(pos.x, pos.y, pos.z);
    MV1SetPosition(base_model, pos.VGet());
    MV1SetRotationXYZ(base_model, rot.VGet());
}

void PlayerOne::Draw()
{
    if (base_model != -1)
        MV1DrawModel(base_model);
}

VECTOR PlayerOne::GetPos()
{
    return pos.VGet();
}

