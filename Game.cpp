#include "Game.h"

//  初期化処理
void Game::Init()
{
    // ライト設定
    SetLightEnable(TRUE);
    SetLightDirection(VGet(0.0f, -1.0f, 1.0f));

    //  カメラ初期化
    camera = Camera(VGet(0.0f, 50.5f, -5.5f), VGet(0.0f, 0.0f, 0.0f));

    //  地面初期化
    ground = Ground("data/ground.mv1",0.0f,0.0f,0.0f);
    //  プレイヤー1体目
    playerOne. Init("data/BigMan.mv1", "data/BigManWalk.mv1");
    playerTwo.Init("data/human.mv1", "data/Running.mv1");
}

//  入力処理
void Game::Input()
{
    //  キー読み込み
    key.Read();
}

//  更新処理
void Game::Update()
{
    //----------------------------------
    //  Rキーでチェンジ
    //-----------------------------------
    if (key.CheckKeyRelease(KEY_INPUT_R))
        Change = !Change;

    if (Change) {
        playerOne.Update();
    }
    else {
        playerTwo.Update();
    }
    //------------------------------------------------------
    //  カメラの位置を調整（プレイヤーそれぞれのすぐ後ろに）
    //-----------------------------------------------------
    VECTOR p = Change ? playerOne.GetPos() : playerTwo.GetPos();

    VECTOR targetPos = VGet(p.x, p.y + 5.0f, p.z - 15.0f);
    VECTOR targetLook = VGet(p.x, p.y + 5.0f, p.z);

    camera.Update(targetPos, targetLook);
    camera.Apply();
}

//  描画処理
void Game::Draw()
{
    ground.Draw();      //  地面
    playerOne.Draw();   //  デブ
    playerTwo.Draw();   //  ガリ
}

void Game::Release()
{
    
}