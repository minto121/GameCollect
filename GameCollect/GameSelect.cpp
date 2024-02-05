#include "GameSelect.h"
#include "Title.h"
#include"PadInput.h"
#include "DxLib.h"
#include "sinkeisuijaku.h" �G���[�o��̂ŁA��U�R�����g�A�E�g��
#include"Hit&Blow.h"
//#include"Hanafuda_GameMain.h"
#include "RabbitAndHounds.h"
#include "Hex_GameMain.h"
#include "Connect4.h"
#include<iostream>
#define SCREEN_WIDTH 1280
GameSelect::GameSelect()
{
	font_handle = CreateFontToHandle("HG����E", 27, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 3);
	now_menu = static_cast<int>(SELECT::Mankara);
	input_margin = 0;
}

GameSelect::~GameSelect()
{
}

AbstractScene* GameSelect::Update()
{
// ����Ԋu����
const int max_input_margin = 15;
// �X�e�B�b�N�̊��x
const int stick_sensitivity = 20000;

if (input_margin < max_input_margin) {
	input_margin++;
}
else {
	// �X�e�B�b�N��Y���W���擾
	int stick_y = PAD_INPUT::GetLStick().ThumbY;

	if (std::abs(stick_y) > stick_sensitivity) {
		//playsoundmem
		// �X�e�B�b�N����Ɉړ������ꍇ
		if (stick_y > 0) {
			// ���j���[�I��������O�Ɉړ�
			now_menu = (now_menu - 1 + static_cast<int>(SELECT::MENU_SIZE)) % static_cast<int>(SELECT::MENU_SIZE);
		}
		// �X�e�B�b�N�����Ɉړ������ꍇ
		else if (stick_y < 0) {
			// ���j���[�I����������Ɉړ�
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
			return new sinkeisuijaku(); // �G���[�o��̂ŁA��U�R�����g�A�E�g��
			break;
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
		return new Connect4();
		break;
	default:
		printfDx("�������ȋ@�\�ł��B\n");
		break;
	}
}

return this;
}


void GameSelect::Draw() const
{
	for (int i = 0; i < static_cast<int>(SELECT::MENU_SIZE); i++)
	{
		// ������̍ŏ�Y���W
		const int base_y = 0;

		// �������Y���W�Ԋu
		const int margin_y = 50;

		// �����F
		int color = 0xFFFFFF;
		// �����O�g�F
		int border_color = 0x000000;

		// �J�[�\���������Ă���ꍇ�A�����F�ƕ����O�g�F�𔽓]������
		if (now_menu == i) {
			color = ~color;
			border_color = ~border_color;
		}
		DrawStringToHandle(SCREEN_WIDTH / 2 - 100, i * margin_y + base_y, menu_items[i], color, font_handle, border_color);
	}

}