#include "Mankara.h"
#include"DxLib.h"
#include"PadInput.h"
#include"GameSelect.h"
Mankara::Mankara()
{
	Board = LoadGraph("images/mancala/MancalaBoard.png");
	Background = LoadGraph("images/Mancala/BackGround02.png");

	// 0�F���I���@�P�F�I�������@�Q�F����̃^�[��
	PocketEnter = 0; 

	MyTurn = TRUE;
	InputFlg = 0;
	// ���̃t���O��TRUE�Ȃ�A���U���g�\��
	ResultFlg1 = FALSE;
	ResultFlg2 = FALSE;
	// TRUE�Ȃ�A���U���g�`��
	ResultDraw1 = FALSE;
	ResultDraw2 = FALSE;


	P1BigPocket = 0;
	P2BigPocket = 0;
	Pocket_cnt = 0;

	P1Pocket[0] = 1;
	P2Pocket[0] = 1;
	// ������
	InitialStone = 4;
	FullStone = 48;

	int tmp = 0;
	int tmp2 = 0;

	for (int y = 0; y < 6; y++) {
		P1Pocket[y] = 0;
	}

	for (int y = 0; y < 6; y++) {
		P2Pocket[y] = 0;
	}

	for (int pocket = 0; pocket < 6;) {
		P1StoneSave[pocket] = 4;
		P2StoneSave[pocket] = 4;
		pocket++;
	}
}

AbstractScene* Mankara::Update()
{

	if (ResultFlg1 == FALSE&&ResultFlg2 == FALSE) {
		// �����̃^�[���̑���
		if (MyTurn == TRUE) {
			// �|�P�b�g��I�������Ƃ��A�|�P�b�g�̒��̐΂��ړ�����
			if (PocketEnter == 0) {
				// �|�P�b�g�̑I��
				// �E�Ɉړ�
				if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
					Pocket_cnt++;
					if (Pocket_cnt > 5) {
						Pocket_cnt = 5;

					}
				} // ���Ɉړ�
				else if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
					Pocket_cnt--;
					if (Pocket_cnt < 0) {
						Pocket_cnt = 0;
					}
				}
			}
		}

		if (MyTurn == FALSE) {
			// �|�P�b�g��I�������Ƃ��A�|�P�b�g�̒��̐΂��ړ�����
			if (PocketEnter == 0) {
				// �|�P�b�g�̑I��
				// �E�Ɉړ�
				if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
					Pocket_cnt--;
					if (Pocket_cnt < 0) {
						Pocket_cnt = 5;

					}
				} // ���Ɉړ�
				else if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
					Pocket_cnt++;
					if (Pocket_cnt > 5) {
						Pocket_cnt = 0;
					}
				}
			}
		}
	}
	

	//1P�p�΂̈ړ�����
	if (MyTurn == TRUE) {
		if (Pocket_cnt == 0) {
			
				// A�{�^���Ō��肵�����ɑI�������|�P�b�g�ȊO��FALSE�ɂ��鏈��
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = TRUE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = FALSE;
		}
		else if (Pocket_cnt == 1) {
	
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = TRUE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = FALSE;
			
		}
		else if (Pocket_cnt == 2) {
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = TRUE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = FALSE;
			
		}
		else if (Pocket_cnt == 3) {
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = TRUE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = FALSE;
			
		}
		else if (Pocket_cnt == 4) {
			
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = TRUE;
				P1Pocket[5] = FALSE;
			
		}
		else if (Pocket_cnt == 5) {
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = TRUE;
		}
	}


	if (MyTurn == FALSE) {
		if (Pocket_cnt == 0) {
				// A�{�^���Ō��肵�����ɑI�������|�P�b�g�ȊO��FALSE�ɂ��鏈��
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = TRUE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = FALSE;
		}
		else if (Pocket_cnt == 1) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = TRUE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = FALSE;
		}
		else if (Pocket_cnt == 2) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = TRUE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = FALSE;
		}
		else if (Pocket_cnt == 3) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = TRUE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = FALSE;			
		}
		else if (Pocket_cnt == 4) {
			
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = TRUE;
				P2Pocket[5] = FALSE;		
		}
		else if (Pocket_cnt == 5) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = TRUE;
		}
	}

	

	MoveStone();

	if (P1StoneSave[0] == 0 && P1StoneSave[1] == 0 && P1StoneSave[2] == 0 && P1StoneSave[3] == 0
		&& P1StoneSave[4] == 0 && P1StoneSave[5] == 0) {

		ResultFlg1 = TRUE;
	}
	if (P2StoneSave[0] == 0 && P2StoneSave[1] == 0 && P2StoneSave[2] == 0 && P2StoneSave[3] == 0
		&& P2StoneSave[4] == 0 && P2StoneSave[5] == 0) {

		ResultFlg2 = TRUE;
	}

	return this;
}

void Mankara::Draw()const
{
	DrawGraph(0, 0, Background, TRUE);
	DrawGraph(30, 30, Board, TRUE);

	// 1P�^�[������ �|�P�b�g�ړ�
	if (MyTurn == TRUE) {
		if (Pocket_cnt == 0) {
			/*	DrawGraph(255, 385, P1PocketImg, FALSE);*/
			DrawBox(255, 385, 360, 600, GetColor(0, 0, 255), FALSE);
			DrawBox(256, 386, 361, 601, GetColor(0, 0, 255), FALSE);
			DrawBox(257, 387, 362, 602, GetColor(0, 0, 255), FALSE);
		}
		else if (Pocket_cnt == 1) {
			DrawBox(385, 385, 490, 600, GetColor(0, 0, 255), FALSE);
			DrawBox(386, 386, 491, 601, GetColor(0, 0, 255), FALSE);
			DrawBox(387, 387, 492, 602, GetColor(0, 0, 255), FALSE);
		}
		else if (Pocket_cnt == 2) {
			DrawBox(515, 385, 615, 600, GetColor(0, 0, 255), FALSE);
			DrawBox(516, 386, 616, 601, GetColor(0, 0, 255), FALSE);
			DrawBox(517, 387, 617, 602, GetColor(0, 0, 255), FALSE);
		}
		else if (Pocket_cnt == 3) {
			DrawBox(645, 385, 745, 600, GetColor(0, 0, 255), FALSE);
			DrawBox(646, 386, 746, 601, GetColor(0, 0, 255), FALSE);
			DrawBox(647, 387, 747, 602, GetColor(0, 0, 255), FALSE);
		}
		else if (Pocket_cnt == 4) {
			DrawBox(770, 385, 870, 600, GetColor(0, 0, 255), FALSE);
			DrawBox(771, 386, 871, 601, GetColor(0, 0, 255), FALSE);
			DrawBox(772, 387, 872, 602, GetColor(0, 0, 255), FALSE);
		}
		else if (Pocket_cnt == 5) {
			DrawBox(900, 385, 1000, 600, GetColor(0, 0, 255), FALSE);
			DrawBox(901, 386, 1001, 601, GetColor(0, 0, 255), FALSE);
			DrawBox(902, 387, 1002, 602, GetColor(0, 0, 255), FALSE);
		}
	}


	// 2P�^�[�����̃|�P�b�g�ړ�
	if (MyTurn == FALSE) {
		if (Pocket_cnt == 0) {
			DrawBox(900, 85, 1000, 300, GetColor(255, 0, 0), FALSE);
			DrawBox(901, 86, 1001, 301, GetColor(255, 0, 0), FALSE);
			DrawBox(902, 87, 1002, 302, GetColor(255, 0, 0), FALSE);
		}
		else if (Pocket_cnt == 1) {
			DrawBox(770, 85, 870, 300, GetColor(255, 0, 0), FALSE);
			DrawBox(771, 86, 871, 301, GetColor(255, 0, 0), FALSE);
			DrawBox(772, 87, 872, 302, GetColor(255, 0, 0), FALSE);
		}
		else if (Pocket_cnt == 2) {
			DrawBox(645, 85, 745, 300, GetColor(255, 0, 0), FALSE);
			DrawBox(646, 86, 746, 301, GetColor(255, 0, 0), FALSE);
			DrawBox(647, 87, 747, 302, GetColor(255, 0, 0), FALSE);
		}
		else if (Pocket_cnt == 3) {
			DrawBox(515, 85, 615, 300, GetColor(255, 0, 0), FALSE);
			DrawBox(516, 86, 616, 301, GetColor(255, 0, 0), FALSE);
			DrawBox(517, 87, 617, 302, GetColor(255, 0, 0), FALSE);
		}
		else if (Pocket_cnt == 4) {
			DrawBox(375, 85, 485, 300, GetColor(255, 0, 0), FALSE);
			DrawBox(376, 86, 486, 301, GetColor(255, 0, 0), FALSE);
			DrawBox(377, 87, 487, 302, GetColor(255, 0, 0), FALSE);
		}
		else if (Pocket_cnt == 5) {
			DrawBox(255, 85, 355, 300, GetColor(255, 0, 0), FALSE);
			DrawBox(256, 86, 356, 301, GetColor(255, 0, 0), FALSE);
			DrawBox(257, 87, 357, 302, GetColor(255, 0, 0), FALSE);
		}

	}

	SetFontSize(24);
	// �S�[���ɓ������΂̐�
	DrawBox(1110, 100, 1160, 150, GetColor(200, 200, 255), TRUE);
	DrawBox(1110, 100, 1160, 150, GetColor(0, 0, 255), FALSE);
	DrawFormatString(1135, 110, GetColor(0, 0, 0), "%d", P1BigPocket);
	DrawFormatString(1125, 70, GetColor(0, 0, 255), "1P");

	DrawBox(185, 615, 235, 670, GetColor(255, 200, 200), TRUE);
	DrawBox(185, 615, 235, 670, GetColor(255, 0, 0), FALSE);
	DrawFormatString(210, 630, GetColor(255, 0, 0), "%d", P2BigPocket);
	DrawFormatString(200, 570, GetColor(255, 0, 0), "2P");

	
	// �^�[���؂�ւ�
	if (MyTurn == FALSE) {
		DrawFormatString(100, 30, GetColor(255, 0, 0), "2P TURN");
	}

	if (MyTurn == TRUE) {
		DrawFormatString(100, 30, GetColor(0, 0, 255), "1P TURN");
	}
	
	SetFontSize(50);

	DrawFormatString(260, 585, GetColor(255, 255, 255), "%d", P1StoneSave[0]);
	DrawFormatString(260 + 125 * 1, 585, GetColor(255, 255, 255), "%d", P1StoneSave[1]);
	DrawFormatString(260 + 125 * 2, 585, GetColor(255, 255, 255), "%d", P1StoneSave[2]);
	DrawFormatString(260 + 125 * 3, 585, GetColor(255, 255, 255), "%d", P1StoneSave[3]);
	DrawFormatString(260 + 125 * 4, 585, GetColor(255, 255, 255), "%d", P1StoneSave[4]);
	DrawFormatString(260 + 125 * 5, 585, GetColor(255, 255, 255), "%d", P1StoneSave[5]);


	DrawFormatString(300, 85, GetColor(255, 255, 255), "%d", P2StoneSave[5]);
	DrawFormatString(300 + 125 * 1, 85, GetColor(255, 255, 255), "%d", P2StoneSave[4]);
	DrawFormatString(300 + 125 * 2, 85, GetColor(255, 255, 255), "%d", P2StoneSave[3]);
	DrawFormatString(300 + 125 * 3, 85, GetColor(255, 255, 255), "%d", P2StoneSave[2]);
	DrawFormatString(300 + 125 * 4, 85, GetColor(255, 255, 255), "%d", P2StoneSave[1]);
	DrawFormatString(300 + 125 * 5, 85, GetColor(255, 255, 255), "%d", P2StoneSave[0]);

	

	SetFontSize(24);
	if (ResultDraw1 == TRUE) {
		if (P1BigPocket < P2BigPocket) {
			DrawBox(480, 250, 700, 400, GetColor(255, 255, 255), TRUE);
			DrawFormatString(500, 300, GetColor(255, 0, 0), "2P  WIN");
			DrawFormatString(500, 350, GetColor(0, 0, 0), "ESC�F�Q�[���I��");
		}
		else if (P1BigPocket > P2BigPocket) {
			DrawBox(480, 250, 700, 400, GetColor(255, 255, 255), TRUE);
			DrawFormatString(500, 300, GetColor(0, 0, 255), "1P  WIN");
			DrawFormatString(500, 350, GetColor(0, 0, 0), "ESC�F�Q�[���I��");
		}
		else if (P1BigPocket == P2BigPocket) {
			DrawBox(480, 250, 700, 400, GetColor(255, 255, 255), TRUE);
			DrawFormatString(500, 300, GetColor(0, 0, 255), "DRAW");
			DrawFormatString(500, 350, GetColor(0, 0, 0), "ESC�F�Q�[���I��");
		}
	}

    if (ResultDraw2 == TRUE) {
		if (P1BigPocket < P2BigPocket) {
			DrawBox(480, 250, 700, 400, GetColor(255, 255, 255), TRUE);
			DrawFormatString(500, 300, GetColor(255, 0, 0), "2P  WIN");
			DrawFormatString(500, 350, GetColor(0, 0, 0), "ESC�F�Q�[���I��");
		}
		else if (P1BigPocket > P2BigPocket) {
			DrawBox(480, 250, 700, 400, GetColor(255, 255, 255), TRUE);
			DrawFormatString(500, 300, GetColor(0, 0, 255), "1P  WIN");
			DrawFormatString(500, 350, GetColor(0, 0, 0), "ESC�F�Q�[���I��");
		}
		else if (P1BigPocket == P2BigPocket) {
			DrawBox(480, 250, 700, 400, GetColor(255, 255, 255), TRUE);
			DrawFormatString(500, 300, GetColor(0, 0, 255), "DRAW");
			DrawFormatString(500, 350, GetColor(0, 0, 0), "ESC�F�Q�[���I��");
		}
	}

	// �v�Z��A�΂̑�����48����Ȃ���΃G���[�\��
	// ���ꂪ�o�Ȃ���ΐ���
	if (tmpflg == TRUE) {
		DrawFormatString(500, 300, GetColor(0, 0, 255), "�G���[");
	}
}

void Mankara::MoveStone()
{
	if (ResultFlg1 == FALSE&& ResultFlg2 == FALSE) {
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
			InputFlg = TRUE;
		}

		if (MyTurn == TRUE && PAD_INPUT::OnRelease(XINPUT_BUTTON_A) && InputFlg == TRUE) {
			PocketEnter = 1;
			InputFlg = FALSE;
		}

		if (MyTurn == FALSE && PAD_INPUT::OnRelease(XINPUT_BUTTON_A) && InputFlg == TRUE) {
			PocketEnter = 1;
			InputFlg = FALSE;
		}
	}

	

      /* �����̃^�[�����̏��� */
	if (MyTurn == TRUE && PocketEnter == 1&& P1Pocket[0] == TRUE) {
		tmp = P1StoneSave[0];
		// 1�Ԗڂ̃|�P�b�g�̒��̐��ɂȂ�܂ŁAi�𑫂�������
		for (int i = 0; i < tmp;) {
			i++;
			
			if (i < 6) { // �΂̐���6�����Ȃ�
				P1StoneSave[i] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
			if (i == 6) { // �΂̐����|�P�b�g��6�ɂȂ�����A
				P1BigPocket += 1;	// �S�[���Ƀv���X1
			}
			if (i > 6 && i < 13) {// �΂̐���6���ゾ������A
				P2StoneSave[i - 7] += 1; // ����̃|�P�b�g�ɓ����
			}
			if (i >= 13) { //�΂̐���13���ゾ������A
				P1StoneSave[i - 13] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
		}
	
		// �ړ����I������̂ŁA�΂̐����O�ɂ���B
		if (P1StoneSave[0] >= 13) {
			P1StoneSave[0] = 1;
		}
		else {
			P1StoneSave[0] = 0;
		}

		PocketEnter = 2;
	}
	else if (MyTurn == TRUE && PocketEnter == 1 && P1Pocket[1] == TRUE) {
		tmp = P1StoneSave[1];
		for (int i = 0; i < tmp;) {
			i++;

			if (i < 5) { // �΂̐���5�����Ȃ�
				P1StoneSave[i + 1] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
			if (i == 5) { // �΂̐����|�P�b�g��5�ɂȂ�����A
				P1BigPocket += 1;	// �S�[���Ƀv���X1
			}
			if (i > 5 && i < 12) { // �΂̐���5���ゾ������A
				P2StoneSave[i - 6] += 1; // ����̃|�P�b�g�ɓ����
			}
			if (i >= 12) { //�΂̐���12���ゾ������A
				P1StoneSave[i - 12] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
		}
		// �ړ����I������̂ŁA�΂̐����O�ɂ���B
		if (P1StoneSave[1] >= 13) {
			P1StoneSave[1] = 1;
		}
		else {
			P1StoneSave[1] = 0;
		}
		PocketEnter = 2;
	}
	else if (MyTurn == TRUE && PocketEnter == 1 && P1Pocket[2] == TRUE) {
		tmp = P1StoneSave[2];
		for (int i = 0; i < tmp;) {
			i++;

			if (i < 4) { // �΂̐���4�����Ȃ�
				P1StoneSave[i + 2] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
			if (i == 4) { // �΂̐����|�P�b�g��4�ɂȂ�����A
				P1BigPocket += 1;	// �S�[���Ƀv���X1
			}
			if (i > 4 && i < 11) { // �΂̐���4���ゾ������A
				P2StoneSave[i - 5] += 1; // ����̃|�P�b�g�ɓ����
			}
			if (i >= 11) { //�΂̐���11���ゾ������A
				P1StoneSave[i - 11] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
		}
		// �ړ����I������̂ŁA�΂̐����O�ɂ���B
		if (P1StoneSave[2] >= 13) {
			P1StoneSave[2] = 1;
		}
		else {
			P1StoneSave[2] = 0;
		}
		PocketEnter = 2;

	}
	else if (MyTurn == TRUE && PocketEnter == 1 && P1Pocket[3] == TRUE) {
		tmp = P1StoneSave[3];
		// 4�Ԗڂ̃|�P�b�g�̒��̐��ɂȂ�܂ŁAi�𑫂�������
		for (int i = 0; i < tmp;) {
			i++;

			if (i < 3) { // �΂̐���3�����Ȃ�
				P1StoneSave[i + 3] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
			if (i == 3) { // �΂̐����|�P�b�g��3�ɂȂ�����A
				P1BigPocket += 1;	// �S�[���Ƀv���X1
			}
			if (i > 3 && i < 10) { // �΂̐���3���ゾ������A
				P2StoneSave[i - 4] += 1; // ����̃|�P�b�g�ɓ����
			}
			if (i >= 10) { //�΂̐���10���ゾ������A
				P1StoneSave[i - 10] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
		}
		// �ړ����I������̂ŁA�΂̐����O�ɂ���B
		if (P1StoneSave[3] >= 13) {
			P1StoneSave[3] = 1;
		}
		else {
			P1StoneSave[3] = 0;
		}
		PocketEnter = 2;

	}
	else if (MyTurn == TRUE && PocketEnter == 1 && P1Pocket[4] == TRUE) {
		int tmp = P1StoneSave[4];
		// 5�Ԗڂ̃|�P�b�g�̒��̐��ɂȂ�܂ŁAi�𑫂�������
		for (int i = 0; i < tmp;) {
			i++;

			if (i < 2) { // �΂̐���2�����Ȃ�
				P1StoneSave[i + 4] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
			if (i == 2) { // �΂̐����|�P�b�g��2�ɂȂ�����A
				P1BigPocket += 1;	// �S�[���Ƀv���X1
			}
			if (i > 2 && i < 9) { // �΂̐���2���ゾ������A
				P2StoneSave[i - 3] += 1; // ����̃|�P�b�g�ɓ����
			}
			if (i >= 9) { //�΂̐���9���ゾ������A
				P1StoneSave[i - 9] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
		}
		// �ړ����I������̂ŁA�΂̐����O�ɂ���B
		if (P1StoneSave[4] >= 13) {
			P1StoneSave[4] = 1;
		}
		else {
			P1StoneSave[4] = 0;
		}
		PocketEnter = 2;

	}
	else if (MyTurn == TRUE && PocketEnter == 1 && P1Pocket[5] == TRUE) {
		tmp = P1StoneSave[5];
		for (int i = 0; i < tmp;) {
			i++;

			if (i < 1) { // �΂̐���1�����Ȃ�
				P1StoneSave[i + 5] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
			if (i == 1) { // �΂̐����|�P�b�g��1�ɂȂ�����A
				P1BigPocket += 1;	// �S�[���Ƀv���X1
			}
			if (i > 1 && i < 8) { // �΂̐���1���ゾ������A
				P2StoneSave[i - 2] += 1; // ����̃|�P�b�g�ɓ����
			}
			if (i >= 8) { //�΂̐���8���ゾ������A
				P1StoneSave[i - 8] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
		}
		// �ړ����I������̂ŁA�΂̐����O�ɂ���B
		if (P1StoneSave[5] >= 13) {
			P1StoneSave[5] = 1;
		}
		else {
			P1StoneSave[5] = 0;
		}
		PocketEnter = 2;
	}



        /* ����̃^�[�����̏��� */
	if (MyTurn == FALSE && PocketEnter == 1&& P2Pocket[0] == TRUE) {
		tmp2 = P2StoneSave[0];
		for (int i = 0; i < tmp2;) {
			i++;

			if (i < 6) { // �΂̐���6�����Ȃ�
				P2StoneSave[i] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
			if (i == 6) { // �΂̐����|�P�b�g��6�ɂȂ�����A
				P2BigPocket += 1;	// �S�[���Ƀv���X1
			}
			if (i > 6 && i < 13) { // �΂̐���6���ゾ������A
				P1StoneSave[i - 7] += 1; // ����̃|�P�b�g�ɓ����
			}
			if (i >= 13) { //�΂̐���13���ゾ������A
				P2StoneSave[i - 13] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
		}
		// �ړ����I������̂ŁA�΂̐����O�ɂ���B
		if (P2StoneSave[0] >= 13) {
			P2StoneSave[0] = 1;
		}
		else {
			P2StoneSave[0] = 0;
		}
		PocketEnter = 2;
	}
	else if (MyTurn == FALSE && PocketEnter == 1 && P2Pocket[1] == TRUE) {
		tmp2 = P2StoneSave[1];
		// 2�Ԗڂ̃|�P�b�g�̒��̐��ɂȂ�܂ŁAi�𑫂�������
		for (int i = 0; i < tmp2;) {
			i++;

			if (i < 5) { // �΂̐���5�����Ȃ�
				P2StoneSave[i + 1] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
			if (i == 5) { // �΂̐����|�P�b�g��5�ɂȂ�����A
				P2BigPocket += 1;	// �S�[���Ƀv���X1
			}
			if (i > 5 && i < 12) { // �΂̐������ゾ������A
				P1StoneSave[i - 6] += 1; // ����̃|�P�b�g�ɓ����
			}
			if (i >= 12) { //�΂̐���12���ゾ������A
				P1StoneSave[i - 12] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
		}
		// �ړ����I������̂ŁA�΂̐����O�ɂ���B
		if (P2StoneSave[1] >= 13) {
			P2StoneSave[1] = 1;
		}
		else {
			P2StoneSave[1] = 0;
		}
		PocketEnter = 2;
	}
	else if (MyTurn == FALSE && PocketEnter == 1 && P2Pocket[2] == TRUE) {
		tmp2 = P2StoneSave[2];
		for (int i = 0; i < tmp2;) {
			i++;

			if (i < 4) { // �΂̐���4�����Ȃ�
				P2StoneSave[i + 2] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
			if (i == 4) { // �΂̐����|�P�b�g��4�ɂȂ�����A
				P2BigPocket += 1;	// �S�[���Ƀv���X1
			}
			if (i > 4 && i < 11) { // �΂̐���4���ゾ������A
				P1StoneSave[i - 5] += 1; // ����̃|�P�b�g�ɓ����
			}
			if (i >= 11) { //�΂̐���11���ゾ������A
				P1StoneSave[i - 11] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
		}
		// �ړ����I������̂ŁA�΂̐����O�ɂ���B
		// �ړ����I������̂ŁA�΂̐����O�ɂ���B
		if (P2StoneSave[2] >= 13) {
			P2StoneSave[2] = 1;
		}
		else {
			P2StoneSave[2] = 0;
		}
		PocketEnter = 2;

	}
	else if (MyTurn == FALSE && PocketEnter == 1 && P2Pocket[3] == TRUE) {
		int tmp2 = P2StoneSave[3];
		for (int i = 0; i < tmp2;) {
			i++;

			if (i < 3) { // �΂̐���3�����Ȃ�
				P2StoneSave[i + 3] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
			if (i == 3) { // �΂̐����|�P�b�g��3�ɂȂ�����A
				P2BigPocket += 1;	// �S�[���Ƀv���X1
			}
			if (i > 3 && i < 10) { // �΂̐���3���ゾ������A
				P1StoneSave[i - 4] += 1; // ����̃|�P�b�g�ɓ����
			}
			if (i >= 10) { //�΂̐���10���ゾ������A
				P1StoneSave[i - 10] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
		}
		// �ړ����I������̂ŁA�΂̐����O�ɂ���B
		if (P2StoneSave[3] >= 13) {
			P2StoneSave[3] = 1;
		}
		else {
			P2StoneSave[3] = 0;
		}
		PocketEnter = 2;

	}
	else if (MyTurn == FALSE && PocketEnter == 1 && P2Pocket[4] == TRUE) {
		tmp2 = P2StoneSave[4];
		for (int i = 0; i < tmp2;) {
			i++;

			if (i < 2) { // �΂̐����Q�����Ȃ�
				P2StoneSave[i + 4] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
			if (i == 2) { // �΂̐����|�P�b�g���Q�ɂȂ�����A
				P2BigPocket += 1;	// �S�[���Ƀv���X1
			}
			if (i > 2 && i < 9) { // �΂̐����Q���ゾ������A
				P1StoneSave[i - 3] += 1; // ����̃|�P�b�g�ɓ����
			}
			if (i >= 9) { //�΂̐���9���ゾ������A
				P1StoneSave[i - 9] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
		}
		// �ړ����I������̂ŁA�΂̐����O�ɂ���B
		if (P2StoneSave[4] >= 13) {
			P2StoneSave[4] = 1;
		}
		else {
			P2StoneSave[4] = 0;
		}
		PocketEnter = 2;

	}
	else if (MyTurn == FALSE && PocketEnter == 1 && P2Pocket[5] == TRUE) {
		tmp2 = P2StoneSave[5];
		for (int i = 0; i < tmp2;) {
			i++;

			if (i < 1) { // �΂̐���1�����Ȃ�
				P2StoneSave[i + 5] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
			if (i == 1) { // �΂̐����|�P�b�g��1�ɂȂ�����A
				P2BigPocket += 1;	// �S�[���Ƀv���X1
			}
			if (i > 1 && i < 8) { // �΂̐���1���ゾ������A
				P1StoneSave[i - 2] += 1; // ����̃|�P�b�g�ɓ����
			}if (i >= 8) { //�΂̐���8���ゾ������A
				P1StoneSave[i - 8] += 1;  // �����̃|�P�b�g�ɐ΂����鏈��
			}
		}
		// �ړ����I������̂ŁA�΂̐����O�ɂ���B
		if (P2StoneSave[5] >= 13) {
			P2StoneSave[5] = 1;
		}
		else {
			P2StoneSave[5] = 0;
		}
		PocketEnter = 2;
	}


	// PocketEnter���Q�ɂȂ�A�^�[����؂�ւ���
	if ( PocketEnter == 2) {
		// �^�[���I�����A�΂̑������v�Z����
		tmp = P1StoneSave[0] + P1StoneSave[1] + P1StoneSave[2] + P1StoneSave[3] + P1StoneSave[4] + P1StoneSave[5]
			+ P2StoneSave[0] + P2StoneSave[1] + P2StoneSave[2] + P2StoneSave[3] + P2StoneSave[4] + P2StoneSave[5]
			+ P1BigPocket + P2BigPocket;
		// �v�Z��A�΂̑�����48����Ȃ���΃G���[�\��
		if (tmp != 48) {
			tmpflg = TRUE;
		}
		else {
			tmpflg = FALSE;
		}

		// �����̃^�[���Ȃ�AMyTurn��FALSE�ɂ���
		if (MyTurn == TRUE) {
			MyTurn = FALSE;
			PocketEnter = 0;
		}
		// ����̃^�[���Ȃ�AMyturn��TRUE�ɂ���
		else if(MyTurn == FALSE) {
			MyTurn = TRUE;
			PocketEnter = 0;
		}
	}


	// ���s���ʂ̕\��
	if (ResultFlg1== TRUE) {
		for (int i = 0; i < P2StoneSave[i]; i++) {
			P2BigPocket += P2StoneSave[i];
			P2StoneSave[i] = 0;
		}
		ResultDraw1 = TRUE;
	}
	else if (ResultFlg2 == TRUE) {
		for (int i = 0; i < P1StoneSave[i]; i++) {
			P1BigPocket += P1StoneSave[i];
			P1StoneSave[i] = 0;
		}
		ResultDraw2 = TRUE;
	}
	
	
	
	

}

