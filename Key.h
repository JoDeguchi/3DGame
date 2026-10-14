#pragma once
#pragma once
#include "DxLib.h"		// DxLib

/// <summary>
/// キーリーダークラス
/// </summary>
class KeyReader
{
	//	キーの状態配列
	char key_state_arr[256];
	char old_key_state_arr[256];
	//	キーが押されたか
	bool key_press = false;
public:
	//	コンストラクタ
	KeyReader();

	//	キー読み込み
	void Read();

	//	キーの状態確認
	bool CheckKey(int arg_key_code);

	// キーを離した瞬間
	bool CheckKeyRelease(int arg_key_code);

	//	キーが押されたか
	bool KeyPress();
};