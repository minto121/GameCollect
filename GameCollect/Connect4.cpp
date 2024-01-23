#include "Connect4.h"
#include"PadInput.h"

Connect4::Connect4()
{
	if ((gStageImg = LoadGraph("images/SixBallPazzle/Board2.png")) == -1);
	if ((gCursorImg = LoadGraph("images/SixBallPazzle/Arrow.png")) == -1);

	//�z��̏�����
	/*for (int x; x < 6; x++) {
		for (int y; y < 7; y++) {
			 Board[x][y] = 0;
		}
	}*/

	
}

Connect4::~Connect4()
{
}

AbstractScene* Connect4::Update()
{
	gOldKey = gNowKey;
	gNowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	gKeyFlg = gNowKey & ~gOldKey;

	// �J�[�\���𓮂�������
	if (gKeyFlg & PAD_INPUT_RIGHT && cX < 6) {
		if (Key_Count >= 1) {
			//cX += 1;
		}
		if (gKeyFlg & PAD_INPUT_RIGHT && cX == 6) {
			//cX = 0;
		}
	}
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {

	//	if (++Num > 6) Num = 0;	//�E��
	//}

	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {

	//	if (--Num < 0) Num = 2;	//����
	//}

	CursorX = cX * 130;
	//Cursor = CursorX + Cursor;	//�ړ����鋗��

	return this;
}

void Connect4::Draw() const
{
	DrawGraph(0, 0, gStageImg, TRUE);	//�X�e�[�W�摜
	//DrawGraph(100, 210 + Cursor, 170, 230 + Cursor, 140, 250 + Cursor, 0xff0000, TRUE);	//�J�[�\���摜
	DrawGraph(CursorX, 0, gCursorImg, TRUE);	//�J�[�\���摜
	DrawFormatString(0, 100, 0xf0f0f0, "%d", cX);

}
