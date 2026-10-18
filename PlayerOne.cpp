#include "PlayerOne.h"
#include <cmath>

void PlayerOne::Init()
{
    //  各モデル読み込み
    base_model = MV1LoadModel("data/debu/BigMan.mv1");
    walk_model = MV1LoadModel("data/debu/BigManWalk.mv1");
    push_model = MV1LoadModel("data/debu/push.mv1");

    // 初期位置
    pos.Set(0.0f, 0.0f, 0.0f);
    rot.Set(0.0f, DX_PI_F, 0.0f);
    //  スケール調整
    MV1SetScale(base_model, VGet(0.03f, 0.03f, 0.03f));

    // 最初は歩きアニメをアタッチ
    AttachWalkAnim();
}

//  更新処理（引数：歩くスピード,アニメスピード）
void PlayerOne::Update(float speed, float anim_speed)
{
    bool isMoveKey = false;

    // 押すアニメーション中は移動しない
    if (!isPushing)
    {
        if (CheckHitKey(KEY_INPUT_W))
        {
            isMoveKey = true;
            pos.x -= sinf(rot.y) * speed;
            pos.z -= cosf(rot.y) * speed;
        }

        if (CheckHitKey(KEY_INPUT_S))
        {
            isMoveKey = true;
            pos.x += sinf(rot.y) * speed;
            pos.z += cosf(rot.y) * speed;
        }
    }

    // アニメーション時間の更新
    if (isPushing || isMoveKey)
    {
        currentAnimTime += anim_speed;

        while (currentAnimTime >= currentAnimTotalTime)
            currentAnimTime -= currentAnimTotalTime;
    }
    else
    {
        // 止まっている場合は先頭フレームで静止
        currentAnimTime = 0.0f;
    }

    MV1SetAttachAnimTime(base_model, currentAnimIndex, currentAnimTime);

    // モデル位置反映
    MV1SetPosition(base_model, pos.VGet());
    MV1SetRotationXYZ(base_model, rot.VGet());
}


//  歩きアニメをアタッチ
void PlayerOne::AttachWalkAnim()
{
    if (currentAnimIndex != -1)
        MV1DetachAnim(base_model, currentAnimIndex);

    currentAnimIndex = MV1AttachAnim(base_model, 0, walk_model, FALSE);

    currentAnimTotalTime = MV1GetAttachAnimTotalTime(base_model, currentAnimIndex);
    currentAnimTime = 0.0f;
}

//   押しアニメをアタッチ
void PlayerOne::AttachPushAnim()
{
    if (currentAnimIndex != -1)
        MV1DetachAnim(base_model, currentAnimIndex);

    currentAnimIndex = MV1AttachAnim(base_model, 0, push_model, FALSE);

    currentAnimTotalTime = MV1GetAttachAnimTotalTime(base_model, currentAnimIndex);
    currentAnimTime = 0.0f;
}

void PlayerOne::AddRotation(float add)
{
    rot.y += add;
}

void PlayerOne::PushBack()
{
    // rot.y の逆方向に少し戻す
    pos.x += sinf(rot.y) * 0.01f;
    pos.z += cosf(rot.y) * 0.01f;

    MV1SetPosition(base_model, pos.VGet());
}

void PlayerOne::SetPush(bool flag)
{
    if (flag == isPushing) return; // 状態が変わらないなら何もしない

    isPushing = flag;

    if (isPushing)
        AttachPushAnim();
    else
        AttachWalkAnim();
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

float PlayerOne::GetRotY()
{
    return rot.y;
}

bool PlayerOne::GetPush()
{
    return isPushing;
}

// 向いている方向に前進する
void PlayerOne::MoveForward(float speed)
{
    pos.x -= sinf(rot.y) * speed;
    pos.z -= cosf(rot.y) * speed;

    MV1SetPosition(base_model, pos.VGet());
}

void PlayerOne::SetPos(VECTOR newPos)
{
    pos.Set(newPos.x, newPos.y, newPos.z);

    if (base_model != -1)
    {
        MV1SetPosition(base_model, newPos);
    }
}