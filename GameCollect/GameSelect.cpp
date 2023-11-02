#include "GameSelect.h"
#include "Title.h"
#include"PadInput.h"
#include "DxLib.h"
#include"Hanafuda_GameMain.h"
#include"takoyaki.h"
#include<iostream>
#define SCREEN_WIDTH 1280
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

	if (std::abs(stick_y) > stick_sensitivity) {
		//playsoundmem
		// スティックが上に移動した場合
		if (stick_y > 0) {
			// メニュー選択肢を一つ前に移動
			now_menu = (now_menu - 1 + static_cast<int>(SELECT::MENU_SIZE)) % static_cast<int>(SELECT::MENU_SIZE);
		}
		// スティックが下に移動した場合
		else if (stick_y < 0) {
			// メニュー選択肢を一つ次に移動
			now_menu = (now_menu + 1) % static_cast<int>(SELECT::MENU_SIZE);
		}
		input_margin = 0;
	}
}
if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true))
{
	input_margin = 0;
	SELECT current_selection = static_cast<SELECT>(now_menu);
	switch (current_selection)
	{
	case SELECT::Hanafuda:
		return new Takoyaki();
		break;
	/*case LEVEL::NORMAL:
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
