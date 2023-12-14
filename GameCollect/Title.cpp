#include "DxLib.h"
#include "Title.h"
#include "PadInput.h"
#include"GameSelect.h"
#include<iostream>
#define SCREEN_WIDTH 1280

Title::Title()
{

	//�t�H���g�̒ǉ�
	MenuFont = CreateFontToHandle("HG�n�p�p�߯�ߑ�", 64, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 3);
	now_menu = static_cast<int>(TITLE_MENU::GAME_START);
	input_margin = 0;

	////�^�C�g���摜�̓ǂݍ���
	//if ((TitleImg = LoadGraph("Resource/Images/mori.png")) == -1)
	//{
	//	throw "Resource/Images/mori.png";
	//}
	//// �J�[�\���摜�̓ǂݍ���
	//if ((CursorImg = LoadGraph("Resource/Images/Apple_Red.png")) == -1)
	//{
	//	throw "Resource/Images/apple.png";
	//}
	////BGM�̓ǂݍ���
	//if ((TitleBGM = LoadSoundMem("Resource/sounds/BGM/yonhonnorecorder.wav")) == -1)
	//{
	//	throw "Resource/sounds/BGM/yonhonnorecorder.wav";
	//}
	////BGM�̉��ʕύX
	//ChangeVolumeSoundMem(140, TitleBGM);

	////SE�̓ǂݍ���
	//if ((MenuSE = LoadSoundMem("Resource/sounds/SE/select01.wav")) == -1) //�I��SE
	//{
	//	throw "Resource/sounds/SE/select01.wav";
	//}
	////SE�̉��ʕύX
	//ChangeVolumeSoundMem(110, MenuSE);

	////BGM�̍Đ�
	//if (CheckSoundMem(TitleBGM) == 0)
	//{
	//	PlaySoundMem(TitleBGM, DX_PLAYTYPE_LOOP);
	//}
}

Title::~Title()
{
	
}

AbstractScene* Title::Update()
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
				now_menu = (now_menu - 1 + static_cast<int>(TITLE_MENU::TITLE_SIZE)) % static_cast<int>(TITLE_MENU::TITLE_SIZE);
			}
			// �X�e�B�b�N�����Ɉړ������ꍇ
			else if (stick_y < 0) {
				// ���j���[�I����������Ɉړ�
				now_menu = (now_menu + 1) % static_cast<int>(TITLE_MENU::TITLE_SIZE);
			}
			input_margin = 0;
		}
	}
	if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true))
	{
		input_margin = 0;
		TITLE_MENU current_select = static_cast<TITLE_MENU>(now_menu);
		switch (current_select)
		{
		case TITLE_MENU::GAME_START:
			return new GameSelect();
			break;
		case TITLE_MENU::GAME_END:
			return nullptr;
			break;
		default:
			printfDx("�������ȋ@�\�ł��B\n");
			break;
		}
	}

	return this;
}

void Title::Draw()const
{
	//�^�C�g���̕`��
	/*DrawGraph(0, 0, TitleImg, FALSE);*/

	for (int i = 0; i < static_cast<int>(TITLE_MENU::TITLE_SIZE); i++)
	{
		// ������̍ŏ�Y���W
		const int base_y = 200;

		// �������Y���W�Ԋu
		const int margin_y = 100;

		// �����F
		int color = 0xFFFFFF;
		// �����O�g�F
		int border_color = 0x000000;

		// �J�[�\���������Ă���ꍇ�A�����F�ƕ����O�g�F�𔽓]������
		if (now_menu == i) {
			color = ~color;
			border_color = ~border_color;
		}
		DrawStringToHandle(SCREEN_WIDTH / 2 - 100, i * margin_y + base_y, menu_items[i], color, MenuFont, border_color);
	}
	DrawStringToHandle(150, 100, "�Q�[����S", 0xffffff, MenuFont);

	////�J�[�\���̕`��
	//int select_y = 230 + Select * 80;
	//DrawGraph(650, select_y, CursorImg, TRUE);
}