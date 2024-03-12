#include "GameSelect.h"
#include "Title.h"
#include"PadInput.h"
#include "DxLib.h"
#include "sinkeisuijaku.h" ・ｽG・ｽ・ｽ・ｽ[・ｽo・ｽ・ｽﾌで、・ｽ・ｽU・ｽR・ｽ・ｽ・ｽ・ｽ・ｽg・ｽA・ｽE・ｽg・ｽ・ｽ
#include"Hit&Blow.h"
//#include"Hanafuda_GameMain.h"
#include "RabbitAndHounds.h"
#include "Hex_GameMain.h"
#include "Connect4.h"
=======
#include "sinkeisuijaku.h"
#include"Hit&Blow.h"
#include"Hanafuda_GameMain.h"
#include"Mankara.h"
#include "RabbitAndHounds.h"
#include "Hex_GameMain.h"
#include "SixBallPuzzle.h"
#include "Porker.h"
#include "Reversi.h"
#include "Checkermain.h"
#include "LastCard.h"
#include "takoyaki.h"
#include"gomoku_TitleScene.h"
#include "GameMain.h"
#include<iostream>
#define SCREEN_WIDTH 1280
GameSelect::GameSelect()
{
	font_handle = CreateFontToHandle("HG・ｽ・ｽ・ｽ・ｽE", 27, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 3);
	now_menu = static_cast<int>(SELECT::Mankara);
	input_margin = 0;
}

GameSelect::~GameSelect()
{
}

AbstractScene* GameSelect::Update()
{
// ・ｽ・ｽ・ｽ・ｽﾔ隔・ｽ・ｽ・ｽ・ｽ
const int max_input_margin = 15;
// ・ｽX・ｽe・ｽB・ｽb・ｽN・ｽﾌ奇ｿｽ・ｽx
const int stick_sensitivity = 20000;

if (input_margin < max_input_margin) {
	input_margin++;
}
else {
	// ・ｽX・ｽe・ｽB・ｽb・ｽN・ｽ・ｽY・ｽ・ｽ・ｽW・ｽ・ｽ・ｽ謫ｾ
	int stick_y = PAD_INPUT::GetLStick().ThumbY;

	if (std::abs(stick_y) > stick_sensitivity) {
		//playsoundmem
		// ・ｽX・ｽe・ｽB・ｽb・ｽN・ｽ・ｽ・ｽ・ｽﾉ移難ｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ鼾・
		if (stick_y > 0) {
			// ・ｽ・ｽ・ｽj・ｽ・ｽ・ｽ[・ｽI・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾂ前・ｽﾉ移難ｿｽ
			now_menu = (now_menu - 1 + static_cast<int>(SELECT::MENU_SIZE)) % static_cast<int>(SELECT::MENU_SIZE);
		}
		// ・ｽX・ｽe・ｽB・ｽb・ｽN・ｽ・ｽ・ｽ・ｽ・ｽﾉ移難ｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ鼾・
		else if (stick_y < 0) {
			// ・ｽ・ｽ・ｽj・ｽ・ｽ・ｽ[・ｽI・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾂ趣ｿｽ・ｽﾉ移難ｿｽ
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
	case SELECT::sinnkeisuizyaku:
			return new sinkeisuijaku(); // ・ｽG・ｽ・ｽ・ｽ[・ｽo・ｽ・ｽﾌで、・ｽ・ｽU・ｽR・ｽ・ｽ・ｽ・ｽ・ｽg・ｽA・ｽE・ｽg・ｽ・ｽ
			break;
			return new sinkeisuijaku();
			break; 
	case SELECT::rabbiitdog:
			return new RabbitAndHounds();
			break;
	case SELECT::Hanafuda:
		return new Hanafuda();
		break;
	/*case LEVEL::NORMAL:
	{
		return new GameMain(current_selection);
		break;
	}
	case LEVEL::HARD:
		return new GameMain(current_selection);
		break;*/
	case SELECT::Hitblow:
		return new HitAndBlow();
		break;
	case SELECT::Hekusu:
		return new Hex();
		break;
	case SELECT::sixballpuzzle:
		return new Connect4();
		break;

		return new SixBallPuzzle();
		break;
	case SELECT::Mankara:
		return new Mankara();
		break;
	case SELECT::poker:
		return new Porker();
		break;
	case SELECT::Osero:
		return new Reversi();
		break;
	case SELECT::Checker:
		return new Checkermain();
		break;
	case SELECT::lastcard:
		return new LastCard();
		break;
	case SELECT::takoyaaki:
		return new Takoyaki();
		break;
	case SELECT::Gomoku:
		// 一旦仮で置いてます。五目並べ担当者は変更があれば変更してください。
		return new gomokuTitle(); 
		break;
	case SELECT::Dotbox:
		return new GameMain();
		break;

	default:
		printfDx("・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾈ機・ｽ\・ｽﾅゑｿｽ・ｽB\n");
		break;
	}
}

return this;
}


void GameSelect::Draw() const
{
	for (int i = 0; i < static_cast<int>(SELECT::MENU_SIZE); i++)
	{
		// ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾌ最擾ｿｽY・ｽ・ｽ・ｽW
		const int base_y = 0;

		// ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽY・ｽ・ｽ・ｽW・ｽﾔ隔
		const int margin_y = 50;

		// ・ｽ・ｽ・ｽ・ｽ・ｽF
		int color = 0xFFFFFF;
		// ・ｽ・ｽ・ｽ・ｽ・ｽO・ｽg・ｽF
		int border_color = 0x000000;

		// ・ｽJ・ｽ[・ｽ\・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ鼾・ｿｽA・ｽ・ｽ・ｽ・ｽ・ｽF・ｽﾆ包ｿｽ・ｽ・ｽ・ｽO・ｽg・ｽF・ｽｽ転・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
		if (now_menu == i) {
			color = ~color;
			border_color = ~border_color;
		}
		DrawStringToHandle(SCREEN_WIDTH / 2 - 100, i * margin_y + base_y, menu_items[i], color, font_handle, border_color);
	}

}