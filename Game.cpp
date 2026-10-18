#include "Game.h"

//  初期化処理
void Game::Init()
{
    SetLightEnable(TRUE);
    // ライト設定
    // 拡散光を強くする（1.0以上でもOK）
    SetLightDifColor(GetColorF(1.2f, 1.2f, 1.2f,1.0f));

    // 反射光なし
    SetLightSpcColor(GetColorF(0.0f, 0.0f, 0.0f,1.0f));

    // 真上から照らす（影が真下に落ちて見えなくなる）
    SetLightDirection(VGet(0.0f, -1.0f, 0.0f));

    //  カメラ初期化
    camera = Camera(VGet(0.0f, 50.5f, -5.5f), VGet(0.0f, 0.0f, 0.0f));
    camera.SetLerpSpeed(0.08f);
    //  マウス初期化（中心X、中心Y、デッドライン、感度（回転速度抑制））
    if (mouse == nullptr)
        mouse = new Mouse(900, 500, 2.0f, 0.1f);
    //  地面初期化
    ground = Ground("data/object/ground.mv1",0.0f,0.0f,0.0f);
    //  プレイヤー1体目
    playerOne. Init();
    playerTwo.Init("data/gari/human.mv1", "data/gari/Running.mv1");

    cube.Init("data/object/cube.mv1");

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

    //  各プレイヤーがどういう動作をするか別々にする
    PlayerOne* activePlayer = Change ? &playerOne : &playerTwo;

    //-------------------------------------------------------
    //  マウスでプレイヤーを回転させる
    //------------------------------------------------------

    //  マウスX座標の処理呼び出し
    float moveX = mouse->GetMoveX();

    // プレイヤーの横回転
    float mouseSpeed = 0.003f;
    float rotAdd = moveX * mouseSpeed;
    activePlayer->AddRotation(rotAdd);

    //------------------------------------------------
    // プレイヤーとCubeの判定
    //------------------------------------------------

    VECTOR p = activePlayer->GetPos();
    VECTOR c = cube.GetPos();

    float dx = c.x - p.x;
    float dz = c.z - p.z;
    float dist = sqrtf(dx * dx + dz * dz);

    const float hitRange = 4.5f;

    //------------------------------------------------
    // Eキーを押した瞬間に家具を押し始める
    //------------------------------------------------

    if (!isPushingCube &&
        key.CheckKeyRelease(KEY_INPUT_E) &&
        dist <= hitRange)
    {
        // プレイヤーが向いている方向
        float rotY = activePlayer->GetRotY();

        float forwardX = -sinf(rotY);
        float forwardZ = -cosf(rotY);

        // プレイヤーからCubeへの方向を正規化
        float toCubeX = dx / (dist > 0.001f ? dist : 1.0f);
        float toCubeZ = dz / (dist > 0.001f ? dist : 1.0f);

        // Cubeがプレイヤーの前方にあるか確認
        float dot = forwardX * toCubeX
            + forwardZ * toCubeZ;

        if (dot > 0.5f)
        {
            isPushingCube = true;

            pushRemaining = pushDistance;

            pushDirX = forwardX;
            pushDirZ = forwardZ;

            activePlayer->SetPush(true);
        }
    }

    //------------------------------------------------
    // 家具を一定距離だけ押す
    //------------------------------------------------

    if (isPushingCube)
    {
        const float moveSpeed = 0.08f;

        // 最後のフレームで押す距離を超えないようにする
        float step = (pushRemaining < moveSpeed)
            ? pushRemaining
            : moveSpeed;

        // プレイヤーを前進させる
        VECTOR playerPos = activePlayer->GetPos();

        playerPos.x += pushDirX * step;
        playerPos.z += pushDirZ * step;

        activePlayer->SetPos(playerPos);

        // Cubeも同じ距離だけ移動
        VECTOR cubePos = cube.GetPos();

        cubePos.x += pushDirX * step;
        cubePos.z += pushDirZ * step;

        cube.SetPos(cubePos);

        // 残りの距離を減らす
        pushRemaining -= step;

        // 一定距離を押し終えたら停止
        if (pushRemaining <= 0.001f)
        {
            pushRemaining = 0.0f;
            isPushingCube = false;

            activePlayer->SetPush(false);
        }
    }


    //-----------------------------------------------------
    //  プレイヤーの更新
    //----------------------------------------------------
    if (Change)
        playerOne.Update(0.1f, 0.4f);
    else
        playerTwo.Update(0.1f, 0.4f);


    //------------------------------------------------
    // 押すアニメーション中はプレイヤーとCubeを移動
    //------------------------------------------------

    if (activePlayer->GetPush())
    {
        float cubeSpeed = 0.08f;

        float rotY = activePlayer->GetRotY();

        // プレイヤーの前進方向
        float moveX = -sinf(rotY);
        float moveZ = -cosf(rotY);

        // Cubeの現在位置
        VECTOR cubePos = cube.GetPos();

        // Cubeを移動
        cubePos.x += moveX * cubeSpeed;
        cubePos.z += moveZ * cubeSpeed;

        cube.SetPos(cubePos);

        // PlayerとCubeの距離を一定に保つ
        // Cubeの中心からPlayerまでの距離
        float keepDistance = 5.0f;

        // Playerの位置をCubeの位置から計算
        VECTOR playerPos = VGet(
            cubePos.x - moveX * keepDistance,
            p.y,
            cubePos.z - moveZ * keepDistance
        );

        activePlayer->SetPos(playerPos);
    }

    //------------------------------------------------
   // 通常歩行時のCube貫通防止
   //------------------------------------------------

    if (!isPushingCube)
    {
        VECTOR playerPos = activePlayer->GetPos();
        VECTOR cubePos = cube.GetPos();

        float dx = playerPos.x - cubePos.x;
        float dz = playerPos.z - cubePos.z;

        float dist = sqrtf(dx * dx + dz * dz);

        if (dist < collisionDistance)
        {
            // CubeからPlayerに向かう方向を求める
            if (dist > 0.001f)
            {
                float dirX = dx / dist;
                float dirZ = dz / dist;

                // PlayerをCubeの外側へ押し戻す
                playerPos.x = cubePos.x + dirX * collisionDistance;
                playerPos.z = cubePos.z + dirZ * collisionDistance;

                activePlayer->SetPos(playerPos);
            }
        }
    }

    //------------------------------------------------------
    //  カメラの位置を調整（プレイヤーそれぞれのすぐ後ろに）
    //-----------------------------------------------------
    
     // 移動後のプレイヤー位置を取得する
    p = activePlayer->GetPos();

    //  カメラ用の位置と向き
    float rotY = activePlayer->GetRotY();

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
    cube.Draw();
}

void Game::Release()
{
    if (mouse != nullptr)
    {
        delete mouse;
        mouse = nullptr;
    }
}