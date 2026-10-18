#pragma once
#include "DxLib.h"
#include "Ground.h"
#include "PlayerOne.h"
#include "PlayerTwo.h"
#include "Base.h"
#include "Key.h"
#include "Camera.h"
#include "Mouse.h"
#include "Cube.h"

class Game
{
private:
   
    //  地面モデル
    Ground ground;

    PlayerOne playerOne;
    PlayerTwo playerTwo;

    KeyReader key;
    Mouse* mouse = nullptr;

    Camera camera;

    Cube cube;

    //  人間切り替え
    bool Change = true;

    // 家具を押している最中か
    bool isPushingCube = false;

    // あと何メートル押すか
    float pushRemaining = 0.0f;

    // 押す方向
    float pushDirX = 0.0f;
    float pushDirZ = 0.0f;

    // 1回で押す距離
    const float pushDistance = 10.0f;
    //  衝突判定
    const float collisionDistance = 4.5f;

public:
    void Init();
    void Input();
    void Update();
    void Draw();
    void Release();

    float TO_RADIAN(float degree)
    {
        return degree * 3.14159265f / 180.0f;
    }
 
};