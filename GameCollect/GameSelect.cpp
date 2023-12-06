#include "GameSelect.h"
#include "Title.h"
#include"PadInput.h"
#include "DxLib.h"
#include "takoyaki.h"
//#include"Hanafuda_GameMain.h"
//#include "sinkeisuijaku.h" エラー出るので、一旦コメントアウト中
#include"Hit&Blow.h"
//#include"Hanafuda_GameMain.h"
#include"Mankara.h"
#include "RabbitAndHounds.h"
#include "Hex_GameMain.h"
#include "SixBallPuzzle.h"
#include "Porker.h"
#include "Reversi.h"
#include "Checkermain.h"
#include<iostream>
#define SCREEN_WIDTH 1280
GameSelect::GameSelect()
{
	font_handle = CreateFontToHandle("HG明朝E", 27, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 3);
	now_menu = static_cast<int>(SELECT::Mankara);
	input_margin = 0;
}
GameSelect::~GameSelect()
{
}

AbstractScene* GameSelect::Update()
{
	// 操作間隔時間
	const int max_input_margin = 15;
	// スティックの感度
	const int stick_sensitivity = 20000;

	if (input_margin < max_input_margin) {
		input_margin++;
	}
	else {
		// スティックのY座標を取得
		int stick_y = PAD_INPUT::GetLStick().ThumbY;

		if (std::abs(stick_y) > stick_sensitivity) {
			//playsoundmem
			// スティックが上に移動した場合
			if (stick_y > 0) {
				// メニュー選択肢を一つ前に移動
				now_menu = (now_menu - 1 + static_cast<int>(SELECT::MENU_SIZE)) % static_cast<int>(SELECT::MENU_SIZE);
			}
			// スティックが下に移動した場合
			else if (stick_y < 0) {
				// メニュー選択肢を一つ前に移動
				now_menu = (now_menu + 1) % static_cast<int>(SELECT::MENU_SIZE);
			}
			input_margin = 0;
		}
		if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true))
		{
			input_margin = 0;
			SELECT current_selection = static_cast<SELECT>(now_menu);
			switch (current_selection)
			{
				/*case SELECT::sinnkeisuizyaku:
						return new sinkeisuijaku(); // エラー出るので、一旦コメントアウト中
						break;*/
			case SELECT::rabbiitdog:
				return new RabbitAndHounds();
				break;
				/*case SELECT::Hanafuda:
					return new Hanafuda();
					break;*/
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
			case SELECT::takoyaaki:
				return new Takoyaki();
				break;
			default:
				printfDx("未実装な機能です\n");
				break;
			}
		}
	}
	return this;
}

void GameSelect::Draw() const
{
	for (int i = 0; i < static_cast<int>(SELECT::MENU_SIZE); i++)
	{
		// 文字列の最小Y座標
		const int base_y = 0;

		// 文字列のY座標間隔
		const int margin_y = 50;

		// 文字色
		int color = 0xFFFFFF;
		// 文字外枠色
		int border_color = 0x000000;

		// カーソルが合っている場合、文字色と文字外枠色を反転させる
		if (now_menu == i) {
			color = ~color;
			border_color = ~border_color;
		}
		DrawStringToHandle(SCREEN_WIDTH / 2 - 100, i * margin_y + base_y, menu_items[i], color, font_handle, border_color);
	}

}