#pragma once
#include "DxLib.h"
#include "Base.h"

class Camera
{
private:
    Base pos;      // カメラ位置
    Base look;     // 注視点
    float lerpSpeed = 0.08f;    //  プレイヤー切り替わるスピード

public:

    //  初期化
    void Init(const VECTOR& initPos,const VECTOR& initLook,float nearClip = 0.1f,
        float farClip = 3000.0f,float fovDeg = 45.0f)
    {
        pos.Set(initPos.x, initPos.y, initPos.z);
        look.Set(initLook.x, initLook.y, initLook.z);

        SetCameraNearFar(nearClip, farClip);
        SetupCamera_Perspective(fovDeg * DX_PI_F / 180.0f);
    }

    //  プレイヤー切り替わるときのカメラスピード（補間速度）
    void SetLerpSpeed(float speed)
    {
        lerpSpeed = speed;
    }

    // 追従更新
    void Update(const VECTOR& targetPos, const VECTOR& targetLook)
    {
        pos.x += (targetPos.x - pos.x) * lerpSpeed;
        pos.y += (targetPos.y - pos.y) * lerpSpeed;
        pos.z += (targetPos.z - pos.z) * lerpSpeed;

        look.x += (targetLook.x - look.x) * lerpSpeed;
        look.y += (targetLook.y - look.y) * lerpSpeed;
        look.z += (targetLook.z - look.z) * lerpSpeed;
    }

    //  カメラ設定
    void Apply()
    {
        SetCameraPositionAndTarget_UpVecY(pos.VGet(), look.VGet());
    }

    //  ゲッター関数（カメラ座標と見る座標）
    VECTOR GetPos() const { return pos.VGet(); }
    VECTOR GetLook() const { return look.VGet(); }
};