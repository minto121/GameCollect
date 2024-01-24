#include "Connect4.h"
#include"PadInput.h"

Connect4::Connect4()
{
	if ((gStageImg = LoadGraph("images/SixBallPazzle/Board2.png")) == -1);	//�X�e�[�W�摜�Ǎ�
	if ((gCursorImg = LoadGraph("images/SixBallPazzle/Arrow.png")) == -1);	//���摜�Ǎ�
	//if ((gBallImg = LoadGraph("images/SixBallPazzle/ball.png")) == -1);		//�{�[���̕����摜�Ǎ�

	//�z��̏�����
	/*for (int x; x < 6; x++) {
		for (int y; y < 7; y++) {
			Stage[x][y] = 0;
		}
	}*/

}

Connect4::~Connect4()
{
}

AbstractScene* Connect4::Update()
{
	/****** �J�[�\���̈ړ����� *******/
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		if (++Num > 7) Num = 1;	//�E��
	}

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		if (--Num < 1) Num = 7;	//����
	}

	Cursor = Num * 130;	//�J�[�\����X���W�𑝂₷
	
	/******** A�{�^���ŐԐF�����F�ɐ؂�ւ�� *******/
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {
		
	}

	return this;
}

void Connect4::Draw() const
{
	DrawGraph(0, 0, gStageImg, TRUE);		//�X�e�[�W�摜
	DrawGraph(Cursor, 0, gCursorImg, TRUE);	//�J�[�\���摜

	DrawFormatString(0, 100, 0xf0f0f0, "%d", Cursor);
	DrawFormatString(0, 200, 0xf0f0f0, "%c", Notation);
	//DrawFormatString(0, 300, 0xf0f0f0, "%d", Cursor);
	//DrawFormatString(0, 400, 0xf0f0f0, "%d", Cursor);

}
	
