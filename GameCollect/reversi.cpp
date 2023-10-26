#include "Reversi.h"
#include<DxLib.h>
#include "PadInput.h"

Reversi::Reversi()
{
	/*R_Img = LoadGraph("images/Reversi/banmen.png");*/
	B_Rock_Img = LoadGraph("images/Reversi/osero(black).png");
	W_Rock_Img = LoadGraph("images/Reversi/osero(white).png");
	XOnce = TRUE;
	XOnce = TRUE;
	/*CursorPoint = { 0, 0 };*/

	K_Flg = FALSE;

	

}

Reversi::~Reversi()
{
}

void Reversi::board()
{

}



AbstractScene* Reversi::Update()
{

	disp();
	////�J�[�\������ړ�������
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP) || (PAD_INPUT::GetLStick().ThumbY > 10000 && YOnce == TRUE)) {

	//	//�A�����͂��Ȃ��悤�ɂ���
	//	YOnce = FALSE;

	//	//�J�[�\�����͂ݏo�Ȃ��悤�ɒ�������
	//	if (--CursorPoint.y < 0) {
	//		if (CursorPoint.x == 10) {
	//			CursorPoint.y = 3;
	//		}
	//		else {
	//			CursorPoint.y = 4;
	//		}
	//		if (CursorPoint.x == 12) {
	//			CursorPoint.x = 11;
	//		}
	//	}
	//}

	////�J�[�\�������ړ�������
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN) || (PAD_INPUT::GetLStick().ThumbY < -10000 && YOnce == TRUE)) {

	//	//�A�����͂��Ȃ��悤�ɂ���
	//	YOnce = FALSE;

	//	

	//	//�J�[�\�����͂ݏo�Ȃ��悤�ɒ�������
	//	if (++CursorPoint.y > 3 && CursorPoint.x == 10 || CursorPoint.y > 4) {
	//		CursorPoint.y = 0;
	//	}
	//	if (CursorPoint.y > 3 && CursorPoint.x == 12) {
	//		CursorPoint.x = 11;
	//	}

	//}

	////�J�[�\�����E�ړ�������
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT) || (PAD_INPUT::GetLStick().ThumbX > 10000 && XOnce == TRUE)) {

	//	//�A�����͂��Ȃ��悤�ɂ���
	//	XOnce = FALSE;

	//

	//	//�J�[�\�����͂ݏo�Ȃ��悤�ɒ�������
	//	if (++CursorPoint.x == 10 && CursorPoint.y > 3)
	//	{
	//		CursorPoint.x = 11;
	//	}
	//	if (CursorPoint.x > 11 && CursorPoint.y == 4) {
	//		CursorPoint.x = 0;
	//	}
	//	if (CursorPoint.x > 12) {
	//		CursorPoint.x = 0;
	//	}
	//}

	////�J�[�\�������ړ�������
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT) || (PAD_INPUT::GetLStick().ThumbX < -10000 && XOnce == TRUE)) {

	//	//�A�����͂��Ȃ��悤�ɂ���
	//	XOnce = FALSE;

	//	//�J�[�\�����͂ݏo�Ȃ��悤�ɒ�������
	//	if (--CursorPoint.x < 0) {
	//		if (CursorPoint.y > 3) {
	//			CursorPoint.x = 11;
	//		}
	//		else {
	//			CursorPoint.x = 12;
	//		}
	//	}
	//	if (CursorPoint.x == 10 && CursorPoint.y == 4)
	//	{
	//		CursorPoint.x = 9;
	//	}
	//}

	////A�{�^���������ꂽ��
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
	//}
	return this;
}

void Reversi::disp()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		K_Flg = TRUE;
		/*switch(order) 
		{
			case Order::First;
			DrawGraph(0, 0, B_Rock_Img, TRUE);
			break;

		}*/
	}
}

void Reversi::Draw() const
{
	DrawFormatString(0, 100, GetColor(255, 255, 255), " %d:button", K_Flg);
	//��̕`��
	if (K_Flg == TRUE)
	{
		DrawGraph(0, 0, W_Rock_Img, TRUE);
	}

	//�Ֆʂ̕`��
	DrawGraph(340, 50, R_Img, TRUE);


}

