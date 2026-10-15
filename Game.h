#pragma once
#include "DxLib.h"
#include "Ground.h"
#include "PlayerOne.h"
#include "PlayerTwo.h"
#include "Base.h"
#include "Key.h"
#include "Camera.h"
#include "Mouse.h"

class Game
{
private:
   
    //  地面モデル
    Ground ground;

    PlayerOne playerOne;
    PlayerTwo playerTwo;

    KeyReader key;
    Mouse* mouse;

    Camera camera;

    //  人間切り替え
    bool Change = true;

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