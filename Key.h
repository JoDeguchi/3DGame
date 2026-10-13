#pragma once
#pragma once
#include "DxLib.h"		// DxLib

/// <summary>
/// キーリーダークラス
/// </summary>
class KeyReader
{
	/// <summary>
	/// キーの状態配列
	/// </summary>
	char key_state_arr[256];
	char old_key_state_arr[256];
	/// <summary>
	/// キーが押されたか
	/// </summary>
	bool key_press = false;
public:

	/// <summary>
	/// コンストラクター
	/// </summary>
	KeyReader();

	/// <summary>
	/// キー読込（一括）
	/// </summary>
	void Read();

	/// <summary>
	/// キーの状態確認
	/// </summary>
	/// <param name="arg_key_code">確認するキーのコード</param>
	/// <returns>キーの状態</returns>
	bool CheckKey(int arg_key_code);

	// キーを離した瞬間
	bool CheckKeyRelease(int arg_key_code);

	/// <summary>
	/// キーが押されたかのチェック
	/// </summary>
	/// <returns>状態</returns>
	bool KeyPress();
};