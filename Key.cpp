#include "Key.h"

KeyReader::KeyReader()
{
	// キー状態配列を初期化
	for (int cnt = 0; cnt < 256; cnt++)
	{
		this->key_state_arr[cnt] = 0;
		old_key_state_arr[cnt] = 0;
	}
	key_press = false;
}

void KeyReader::Read()
{
	for (int cnt = 0; cnt < 256; cnt++)
	{
		old_key_state_arr[cnt] = key_state_arr[cnt];
	}

	GetHitKeyStateAll(this->key_state_arr);

	key_press = false;
	for (int cnt = 0; cnt < 256; cnt++)
	{
		if (key_state_arr[cnt] != 0)
		{
			key_press = true;
			break;
		}
	}
}

bool KeyReader::CheckKey(int arg_key_code)
{
	// 指定されたキーの状態をチェック
	if (this->key_state_arr[arg_key_code] == 1 && old_key_state_arr[arg_key_code] == 0)
	{
		// 押されていればtrueを返す
		return true;
	}
	// 押されていなければfalseを返す
	return false;
}

// キーを離した瞬間
bool KeyReader::CheckKeyRelease(int arg_key_code)
{
	return key_state_arr[arg_key_code] == 0
		&& old_key_state_arr[arg_key_code] != 0;
}

bool KeyReader::KeyPress()
{
	return this->key_press;
}