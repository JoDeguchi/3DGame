#pragma once
#include "DxLib.h"
#include "Base.h"

/// <summary>
/// カメラクラス
/// </summary>
class Camera
{
private:
    Base pos;      // カメラ位置
    Base look;     // 注視点
    float lerpSpeed = 0.08f;    //  プレイヤー切り替わるスピード

public:
    Camera(){}
    //  コンストラクタ
    Camera(const VECTOR& initPos, const VECTOR& initLook)
    {
        pos.Set(initPos.x, initPos.y, initPos.z);
        look.Set(initLook.x, initLook.y, initLook.z);
    }
   
    //  プレイヤー切り替わるときのカメラスピード（補間速度）
    void SetLerpSpeed(float speed)
    {
        lerpSpeed = speed;
    }

    // 追従更新
    void Update(const VECTOR& targetPos, const VECTOR& targetLook)
    {
        pos.Set(targetPos.x, targetPos.y, targetPos.z);
        look.Set(targetLook.x, targetLook.y, targetLook.z);
    }

    //  カメラ設置
    void Apply()
    {
        SetCameraPositionAndTarget_UpVecY(pos.VGet(), look.VGet());
    }

    //  ゲッター関数（カメラ座標と見る座標）
    VECTOR GetPos() const { return pos.VGet(); }
    VECTOR GetLook() const { return look.VGet(); }
};