#include "Game.h"

//  初期化処理
void Game::Init()
{
    // ライト設定
    SetLightEnable(TRUE);
    SetLightDirection(VGet(1.0f, -1.0f, 1.0f));
    
    //  カメラ初期化
    camera = Camera(VGet(0.0f, 50.5f, -5.5f), VGet(0.0f, 0.0f, 0.0f));
    //  マウス初期化（中心X、中心Y、デッドライン、感度（回転速度抑制））
    mouse = new Mouse(900, 500, 2.0f, 0.1f);

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

    //  マウスX座標の処理呼び出し
    float moveX = mouse->GetMoveX();

    // プレイヤーの横回転
    float mouseSpeed = 0.01f;
    float rotAdd = moveX * mouseSpeed;

    if (Change)
        playerOne.AddRotation(rotAdd);
    else
        playerTwo.AddRotation(rotAdd);

    //------------------------------------------------------
    //  カメラの位置を調整（プレイヤーそれぞれのすぐ後ろに）
    //-----------------------------------------------------
    VECTOR p = Change ? playerOne.GetPos() : playerTwo.GetPos();
    float rotY = Change ? playerOne.GetRotY() : playerTwo.GetRotY();

    float camDist = 30.0f;
    float camHeight = 10.0f;

    VECTOR camPos = VGet(
        p.x + sinf(rotY) * camDist,
        p.y + camHeight,
        p.z + cosf(rotY) * camDist
    );

    VECTOR camLook = VGet(p.x, p.y + 5.0f, p.z);

    camera.Update(camPos, camLook);
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