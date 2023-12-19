#pragma once
#include"DxLib.h"

#define BUTTONS 16

//
struct Stick
{
	short ThumbX;	//
	short ThumbY;	//
};

class PAD_INPUT
{
private:
	static char NowKey[BUTTONS]; //
	static char OldKey[BUTTONS]; //
	static XINPUT_STATE Input; //
	static Stick Rstick; //
	static Stick Lstick; //
private:
	//
	PAD_INPUT() = default;
public:
	//
	static void UpdateKey()
	{
		// 
		GetJoypadXInputState(DX_INPUT_KEY_PAD1, &Input);
		for (int i = 0; i < BUTTONS; i++)
		{
			OldKey[i] = NowKey[i];
			NowKey[i] = Input.Buttons[i];
		}

		//
		Rstick.ThumbX = Input.ThumbRX;
		Rstick.ThumbY = Input.ThumbRY;

		//
		Lstick.ThumbX = Input.ThumbLX;
		Lstick.ThumbY = Input.ThumbLY;
	}

	//
	static bool OnButton(int button)
	{
		bool ret = (NowKey[button] == 1 && OldKey[button] == 0);
		return ret;
	}

	//
	static bool OnPressed(int button)
	{
		bool ret = (NowKey[button] == 1);
		return ret;
	}

	//
	static bool OnRelease(int button)
	{
		bool ret = (NowKey[button] == 0 && OldKey[button] == 1);
		return ret;
	}

	//
	static Stick GetRStick()
	{
		return Rstick;
	}

	//
	static Stick GetLStick()
	{
		return Lstick;
	}
	static char GetNowKey(const int i)
	{
		return NowKey[i];
	}
	static  char GetOldKey(const int i)
	{
		return OldKey[i];
	}
};

