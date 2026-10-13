#include "Game.h"

void Game::Init()
{
    // ライト設定
    SetLightEnable(TRUE);
    SetLightDirection(VGet(0.0f, -1.0f, 1.0f));

    // カメラ初期化
    camera.Init(
        VGet(0.0f, 50.5f, -5.5f),   // 初期位置
        VGet(0.0f, 0.0f, 0.0f),     // 初期注視点
        0.1f,
        3000.0f,
        45.0f
    );

    //  地面初期化
    ground = Ground("data/ground.mv1",0.0f,0.0f,0.0f);
    //  プレイヤー1体目
    playerOne. Init("data/BigMan.mv1", "data/BigManWalk.mv1");
    playerTwo.Init("data/human.mv1", "data/Running.mv1");
}

void Game::Input()
{
    //key.Read();
}

void Game::Update()
{
    key.Read();

    if (key.CheckKeyRelease(KEY_INPUT_R))
        Change = !Change;

    if (Change)
        playerOne.Update();
    else
        playerTwo.Update();

    VECTOR p = Change ? playerOne.GetPos() : playerTwo.GetPos();

    VECTOR targetPos = VGet(p.x, p.y + 5.0f, p.z - 15.0f);
    VECTOR targetLook = VGet(p.x, p.y + 5.0f, p.z);

    camera.Update(targetPos, targetLook);
}

void Game::Draw()
{
    camera.Apply();
    ground.Draw();

    playerOne.Draw();
    playerTwo.Draw();
}

void Game::Release()
{
    
}