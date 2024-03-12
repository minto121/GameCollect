#include "GameSelect.h"
#include "Title.h"
#include"PadInput.h"
#include "DxLib.h"
#include "sinkeisuijaku.h" �E�G�E��E��E�[�E�o�E��E�̂ŁA�E��E�U�E�R�E��E��E��E��E�g�E�A�E�E�E�g�E��E�
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
	font_handle = CreateFontToHandle("HG�E��E��E��E�E", 27, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 3);
	now_menu = static_cast<int>(SELECT::Mankara);
	input_margin = 0;
}

GameSelect::~GameSelect()
{
}

AbstractScene* GameSelect::Update()
{
// �E��E��E��E�Ԋu�E��E��E��E�
const int max_input_margin = 15;
// �E�X�E�e�E�B�E�b�E�N�E�̊��E�x
const int stick_sensitivity = 20000;

if (input_margin < max_input_margin) {
	input_margin++;
}
else {
	// �E�X�E�e�E�B�E�b�E�N�E��E�Y�E��E��E�W�E��E��E�擾
	int stick_y = PAD_INPUT::GetLStick().ThumbY;

	if (std::abs(stick_y) > stick_sensitivity) {
		//playsoundmem
		// �E�X�E�e�E�B�E�b�E�N�E��E��E��E�Ɉړ��E��E��E��E��E�ꍁE
		if (stick_y > 0) {
			// �E��E��E�j�E��E��E�[�E�I�E��E��E��E��E��E��E��E�O�E�Ɉړ�
			now_menu = (now_menu - 1 + static_cast<int>(SELECT::MENU_SIZE)) % static_cast<int>(SELECT::MENU_SIZE);
		}
		// �E�X�E�e�E�B�E�b�E�N�E��E��E��E��E�Ɉړ��E��E��E��E��E�ꍁE
		else if (stick_y < 0) {
			// �E��E��E�j�E��E��E�[�E�I�E��E��E��E��E��E��E��E���E�Ɉړ�
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
			return new sinkeisuijaku(); // �E�G�E��E��E�[�E�o�E��E�̂ŁA�E��E�U�E�R�E��E��E��E��E�g�E�A�E�E�E�g�E��E�
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
		// ��U���Œu���Ă܂��B�ܖڕ��גS���҂͕ύX������ΕύX���Ă��������B
		return new gomokuTitle(); 
		break;
	case SELECT::Dotbox:
		return new GameMain();
		break;

	default:
		printfDx("�E��E��E��E��E��E��E�ȋ@�E�\�E�ł��E�B\n");
		break;
	}
}

return this;
}


void GameSelect::Draw() const
{
	for (int i = 0; i < static_cast<int>(SELECT::MENU_SIZE); i++)
	{
		// �E��E��E��E��E��E�̍ŏ�Y�E��E��E�W
		const int base_y = 0;

		// �E��E��E��E��E��E��E�Y�E��E��E�W�E�Ԋu
		const int margin_y = 50;

		// �E��E��E��E��E�F
		int color = 0xFFFFFF;
		// �E��E��E��E��E�O�E�g�E�F
		int border_color = 0x000000;

		// �E�J�E�[�E�\�E��E��E��E��E��E��E��E��E�Ă��E��E�ꍁE��A�E��E��E��E��E�F�E�ƕ��E��E��E�O�E�g�E�F�E�𔽓]�E��E��E��E��E��E�
		if (now_menu == i) {
			color = ~color;
			border_color = ~border_color;
		}
		DrawStringToHandle(SCREEN_WIDTH / 2 - 100, i * margin_y + base_y, menu_items[i], color, font_handle, border_color);
	}

}