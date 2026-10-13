#include "DxLib.h"
#include "Game.h"
#include <windows.h>
#include <time.h>
#include <math.h>

#include <algorithm>
#include <d3d9.h>

using namespace std;

#pragma warning (disable : 4819)

int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR ipCmdLine,
    _In_ int nCmdShow)
{
    ChangeWindowMode(TRUE);
    SetGraphMode(1800, 1000, 32);

    if (DxLib_Init() == -1)
        return -1;

    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);

    SetDrawScreen(DX_SCREEN_BACK);

    // 奥行設定 ON
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);

    // 背景色
    SetBackgroundColor(200, 200, 200);

    Game game;          //  ゲームインスタンス
    game.Init();        //  初期化処理

    while (ProcessMessage() == 0)
    {
        ClearDrawScreen();   // 画面を消す
        game.Update();       // 更新
        game.Draw();         // 描画
        ScreenFlip();        // 表示
    }


    game.Release();
    DxLib_End();
    return 0;
}