#include "GameSelect.h"
#include "Title.h"
#include"PadInput.h"
#include "DxLib.h"
#include"RabbitAndHounds.h"

GameSelect::GameSelect()
{
	Select = 0;
	Once = TRUE;

}

GameSelect::~GameSelect()
{
}

AbstractScene* GameSelect::Update()
{
	//十字キー↑入力
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
	{
		Select--;
		if (Select < 0)Select = 3;
	}
	//十字キー↓入力
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		Select++;
		if (Select > 3)Select = 0;
	}

	//Lスティック上入力
	if (PAD_INPUT::GetLStick().ThumbY > 10000 && Once == TRUE)
	{
		Select--;
		if (Select < 0)Select = 3;
		Once = FALSE;
	}

	//Lスティック下入力
	if (PAD_INPUT::GetLStick().ThumbY < -10000 && Once == TRUE)
	{
		Select++;
		if (Select > 3)Select = 0;
		Once = FALSE;
	}

	//Lスティックが元に戻されたらOnceをリセット
	if (Once == FALSE && PAD_INPUT::GetLStick().ThumbY < 10000 && PAD_INPUT::GetLStick().ThumbY > -10000)
	{
		Once = TRUE;
	}

	

	return this;
}

void GameSelect::Draw() const
{
	DrawString(70, 240, "Select", 0xffffff);
}
