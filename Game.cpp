#include "Game.h"

void Game::Init()
{
    // ライト設定
    SetLightEnable(TRUE);
    SetLightDirection(VGet(0.0f, -1.0f, 1.0f));

    camera_pos.Set(0.0f, 50.5f, -5.5f);
    camera_look.Set(0.0f, 0.0f, 0.0f);

    //  カメラの遠近感を出す（大事）
    SetCameraNearFar(0.1f, 3000.0f);
    SetupCamera_Perspective(TO_RADIAN(45.0f));

    //  地面初期化
    ground = Ground("data/ground.mv1",0.0f,0.0f,0.0f);
    //  プレイヤー1体目
    playerOne. Init("data/BigMan.mv1", "data/BigManWalk.mv1");
    playerTwo.Init("data/human.mv1", "data/Running.mv1");
}

void Game::Input()
{
    key.Read();
}

void Game::Update()
{
    key.Read();

    // Rキーを離した瞬間にプレイヤーを切り替える
    if (key.CheckKeyRelease(KEY_INPUT_R))
    {
        Change = !Change;
    }

    // 操作するプレイヤーを更新
    if (Change)
    {
        playerOne.Update();
    }
    else
    {
        playerTwo.Update();
    }

    // カメラの追随先を切り替える
    VECTOR p;

    if (Change)
    {
        p = playerOne.GetPos();
    }
    else
    {
        p = playerTwo.GetPos();
    }

    // カメラをプレイヤーの後ろに配置
    camera_pos.Set(
        p.x,
        p.y + 5.0f,
        p.z - 15.0f
    );

    // 見る座標
    camera_look.Set(
        p.x,
        p.y + 5.0f,
        p.z
    );
   
}

void Game::Draw()
{
    SetCameraPositionAndTarget_UpVecY(camera_pos.VGet(), camera_look.VGet());

    ground.Draw();

    playerOne.Draw();
    playerTwo.Draw();
}

void Game::Release()
{
    
}