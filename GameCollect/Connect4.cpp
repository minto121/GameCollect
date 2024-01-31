#include "Connect4.h"
#include"PadInput.h"

#define POINTX 132.5
int Turn = 1;		//���

Connect4::Connect4()
{
	if ((gStageImg = LoadGraph("images/SixBallPazzle/Board2.png")) == -1);				//�X�e�[�W�摜�Ǎ�
	if ((gCursorImg = LoadGraph("images/SixBallPazzle/Arrow.png")) == -1);				//���摜�Ǎ�
	if ((gRedCoinImg = LoadGraph("images/SixBallPazzle/RedCoin.png")) == -1);			//�{�[���̕����摜�Ǎ�
	if ((gYellowCoinImg = LoadGraph("images/SixBallPazzle/YellowCoin.png")) == -1);		//�{�[���̕����摜�Ǎ�
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

	Cursor = Num  * POINTX + 20;	//�J�[�\����X���W�𑝂₷

	/******** �{�^���ŐԐF�����F�ɐ؂�ւ��� *******/
	
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {
		clsDx();
		SetLogFontSize(32);
		switch (Turn)
		{
		case 1:
			printfDx("���F���� \n");
			for (int y = 5; y >= 0; y--) {	//���̏c�̗�ɉ��F��`�悳����
				if (Stage[Num - 1][y] == 0) {	//Num�͉��̍s�����Ă�
					Stage[Num - 1][y] = 1;

					for (int i = 0; i < 4; i++) {
						if (bool connect = CheckConnect(Num - 1, y, i) == true) {
							// �N���A
							printfDx("�N���A�I\n");
						}
					}
					break;
				}
			}
			Turn = 2;
			break;
		case 2:
			printfDx("�ԐF���� \n");
				for (int y = 5; y >= 0; y--) {	//���̏c�̗�ɉ��F��`�悳����
					if (Stage[Num - 1][y] == 0) {	//Num�͉��̍s�����Ă�;
						Stage[Num - 1][y] = 2;

						for (int i = 0; i < 4; i++) {
							if (bool connect = CheckConnect(Num - 1, y, i) == true) {
								// �N���A
								printfDx("�N���A�I\n");
							}
						}
						break;
					}
				}
				Turn = 1;
				break;
		}
	}
	return this;
}

void Connect4::Draw() const
{
	DrawGraph(0, 0, gStageImg, TRUE);		//�X�e�[�W�摜
	DrawGraph(Cursor, 0, gCursorImg, TRUE);	//�J�[�\���摜
	DrawFormatString(0, 100, 0xf0f0f0, "%d", Cursor);	//�J�[�\���̒l
	
	//�{�[���̕`��
	for (int x = 6; x >= 0; x--) {
		for (int y = 5; y >= 0; y--) {
			if (Stage[x][y] == 1) {
				DrawGraph((x * POINTX) + POINTX, y * 100 + 65, gYellowCoinImg, TRUE);
			}
			if (Stage[x][y] == 2) {
				DrawGraph((x * POINTX) + POINTX, y * 100 + 65, gRedCoinImg, TRUE);
			}
		}
	}
}

bool Connect4::CheckConnect(int x, int y, int type) {
	int min = CheckConnectMin(x, y, type, 0);
	switch (type) {

		// ��
	case 0:
		// 4����ł邩�m�F
		for (int i = 0; i < 4; i++) {
			// ���̍��W - ��ԍ��̍��W + i �����̍��W�ƈꏏ����Ȃ��ꍇfalse
			if (Stage[(x - min) + i][y] != Stage[x][y]) {
				return false;
			}
		}
		break;

		// �c
	case 1:
		// 4����ł邩�m�F
		for (int i = 0; i < 4; i++) {
			if (Stage[x][(y - min) + i] != Stage[x][y]) {
				return false;
			}
		}
		break;

		// �΂߉E���E����
	case 2:
		// 4����ł邩�m�F
		for (int i = 0; i < 4; i++) {
			if (Stage[(x - min) + i][(y - min) + i] != Stage[x][y]) {
				return false;
			}
		}
		break;

		// �΂߉E��E����
	case 3:
		// 4����ł邩�m�F
		for (int i = 0; i < 4; i++) {
			if (Stage[(x - min) + i][(y + min) - i] != Stage[x][y]) {
				return false;
			}
		}
		break;

	default:
		break;
	}

	// 4�񃋁[�v���čŌ�܂ōs�����ꍇtrue
	return true;
}


// ��ԍ����擾
int Connect4::CheckConnectMin(int x, int y, int type, int cnt)
{
	// 0����7�̊ԂȂ猩��
	if (x - 1 >= 0 && x + 1 <= 7) {
		if (y - 1 >= 0 && y + 1 <= 6) {

			switch (type) {
				//�����m�F
			case 0:
				if (Stage[x - 1][y] == Stage[x][y]) {
					cnt++;
					cnt = CheckConnectMin(x - 1, y, type, cnt);
				}
				break;
				//�c�̊m�F
			case 1:
				if (Stage[x][y] == Stage[x][y - 1]) {
					cnt++;
					cnt = CheckConnectMin(x, y - 1, type, cnt);
				}
				break;
				// �΂߉E���E����
			case 2:
				if (Stage[x - 1][y - 1] == Stage[x][y]) {
					cnt++;
					cnt = CheckConnectMin(x - 1, y - 1, type, cnt);
				}
				break;
				// �΂߉E��E����
			case 3:
				if (Stage[x - 1][y + 1] == Stage[x][y]) {
					cnt++;
					cnt = CheckConnectMin(x - 1, y + 1, type, cnt);
				}
				break;
			default:
				break;
			}
		}
	}
	return cnt;
}