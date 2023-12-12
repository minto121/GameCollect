#include "Mankara.h"
#include"DxLib.h"
#include"PadInput.h"
Mankara::Mankara()
{
	StoneImg[6] = LoadDivGraph("images/Mancala/MancalaStone.png", 6, 6, 1, 32, 32, StoneImg);
	Board = LoadGraph("images/mancala/MancalaBoard.png");
	Background = LoadGraph("images/Mancala/BackGround02.png");
	//P1PocketImg = LoadGraph("images/Mancala/1PPocket.png");
	//P2PocketImg = LoadGraph("images/Mancala/2PPocket.png");

	P1BigPocket = 0;
	P2BigPocket = 0;

	Pocket_cnt = 0;

	P1Pocket[0] = 1;
	P2Pocket[0] = 1;
	// ������
	InitialStone = 4;
	Stone_cnt = 1;
	movePocket = 0;
	// �҂�����S�[���p�ϐ�
	JustGoal = 0;

	for (int y = 0; y < 6; y++) {
		P1Pocket[y] += 1;
	}

	for (int y = 0; y < 6; y++) {
		P2Pocket[y] += 1;
	}

	// �΂̉摜����(�|�P�b�g)
	for (int i = 0; i < 6; i++) {
		for (int y = 0; y < 6; y++) {
			gStone[y][i].img = StoneImg[y];//�|�P�b�g�P
			gStone2[y][i].img = StoneImg[y];//�|�P�b�g�P
		}
	}

	// �΂̉摜����(�S�[��)
	for (int i = 0; i < 30; i++) {
		for (int y = 0; y < 6; y++) {
			gGoal[y][i].img = StoneImg[y];//�|�P�b�g�P
			
		}
	}


	for (int i = 0; i < 7; i++) {
		StonePocket[0][i] = InitialStone; // 1P�i[1]�j�̃|�P�b�g�i[6]�j�̒���Stone_cnt�̏����l�i4�j���i�[
		StonePocket[1][i] = InitialStone; // 2P�i[1]�j�̃|�P�b�g�i[6]�j�̒���Stone_cnt�̏����l�i4�j���i�[
	}

	for (int pocket = 0; pocket < 6;) {
		P1StoneSave[pocket] = 4;
		P2StoneSave[pocket] = 4;
		pocket++;
	}

	for (int i = 4; i < 16; i++) {
		gStone[i][0].img = FALSE ;
		gStone[i][1].img = FALSE ;
		gStone[i][2].img = FALSE ;
		gStone[i][3].img = FALSE ;
		gStone[i][4].img = FALSE ;
		gStone[i][5].img = FALSE ;
	}
	for (int i = 4; i < 16; i++) {
		gStone2[i][0].img = FALSE;
		gStone2[i][1].img = FALSE;
		gStone2[i][2].img = FALSE;
		gStone2[i][3].img = FALSE;
		gStone2[i][4].img = FALSE;
		gStone2[i][5].img = FALSE;
	}
	for (int i = 0; i < 30; i++) {
		gGoal[0][i].img = FALSE ;
		gGoal[1][i].img = FALSE ;
		
	}

}

AbstractScene* Mankara::Update()
{
	// ����̃^�[���̓v���C���[�͓����Ȃ�
	if (P2Turn == 1) {
		P1Turn = 0;
	}

	// �^�[���؂�ւ�
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_X)) {
		P2Turn = 1;
		P1Turn = 0;
	}

	// �v���C���[�̃^�[���͑���͓����Ȃ�
	if (P1Turn == 1) {
		P2Turn = 0;
	}

	// �^�[���؂�ւ�
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y)) {
		P1Turn = 1;
		P2Turn = 0;
	}


	if (P1Turn == 1) {
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

	if (P2Turn == 1) {
		// �|�P�b�g�̑I��
		// �E�Ɉړ�
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
			Pocket_cnt--;
			if (Pocket_cnt < 0) {
				Pocket_cnt = 0;
			}
		} // ���Ɉړ�
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
			Pocket_cnt++;
			if (Pocket_cnt > 5) {
				Pocket_cnt = 5;
			}
		}
	}

	MoveStone();
	WinLose();

	//1P�p�΂̈ړ�����
	if (P1Turn == 1) {
		if (Pocket_cnt == 0) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				// A�{�^���Ō��肵�����ɑI�������|�P�b�g�ȊO��FALSE�ɂ��鏈��
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = TRUE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = FALSE;

			}
		}
		else if (Pocket_cnt == 1) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = TRUE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = FALSE;
			}
		}
		else if (Pocket_cnt == 2) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = TRUE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = FALSE;
			}
		}
		else if (Pocket_cnt == 3) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = TRUE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = FALSE;
			}
		}
		else if (Pocket_cnt == 4) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = TRUE;
				P1Pocket[5] = FALSE;
			}
		}
		else if (Pocket_cnt == 5) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = TRUE;
			}
		}
	}


	//2P�p�΂̈ړ�����
	if (P2Turn == 1) {
		if (Pocket_cnt == 0) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = TRUE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = FALSE;

			}
		}
		else if (Pocket_cnt == 1) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = TRUE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = FALSE;
			}
		}
		else if (Pocket_cnt == 2) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = TRUE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = FALSE;
			}
		}
		else if (Pocket_cnt == 3) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = TRUE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = FALSE;
			}
		}
		else if (Pocket_cnt == 4) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = TRUE;
				P2Pocket[5] = FALSE;
			}
		}
		else if (Pocket_cnt == 5) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = TRUE;
			}
		}
	}

	return this;
}

void Mankara::Draw()const
{
	DrawGraph(0, 0, Background, TRUE);
	DrawGraph(30, 30, Board, TRUE);

	// -----------��������΂̏����z�u--------------

	// �΁i�|�P�b�g�P�j�̏����z�u
	for (int i = 0; i < 8; i++) {
		DrawGraph(340, 440 + i * 20, gStone[i][0].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(370, 280 + i * 20, gStone[i][0].img, TRUE);
	}
	// �΁i�|�P�b�g�Q�j�̏����z�u
	for (int i = 0; i < 8; i++) {
		DrawGraph(460, 440 + i * 20, gStone[i][1].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(490, 280 + i * 20, gStone[i][1].img, TRUE);
	}
	// �΁i�|�P�b�g�R�j�̏����z�u
	for (int i = 0; i < 8; i++) {
		DrawGraph(590, 440 + i * 20, gStone[i][2].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(620, 280 + i * 20, gStone[i][2].img, TRUE);
	}
	// �΁i�|�P�b�g�S�j�̏����z�u
	for (int i = 0; i < 8; i++) {
		DrawGraph(715, 440 + i * 20, gStone[i][3].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(745, 280 + i * 20, gStone[i][3].img, TRUE);
	}
	// �΁i�|�P�b�g�T�j�̏����z�u
	for (int i = 0; i < 8; i++) {
		DrawGraph(840, 440 + i * 20, gStone[i][4].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(870, 280 + i * 20, gStone[i][4].img, TRUE);
	}
	// �΁i�|�P�b�g�U�j�̏����z�u
	for (int i = 0; i < 8; i++) {
		DrawGraph(965, 440 + i * 20, gStone[i][5].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(995, 280 + i * 20, gStone[i][5].img, TRUE);
	}

	//// 2P�΂̏����z�u
	// -----------��������΂̏����z�u--------------

	// �΁i�|�P�b�g�P�j�̏����z�u
	for (int i = 0; i < 8; i++) {
		DrawGraph(965, 200 + i * 20, gStone[i][0].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(995, 40 + i * 20, gStone[i][0].img, TRUE);
	}
	// �΁i�|�P�b�g�Q�j�̏����z�u
	for (int i = 0; i < 8; i++) {
		DrawGraph(840, 200 + i * 20, gStone[i][1].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(870, 40 + i * 20, gStone[i][1].img, TRUE);
	}
	// �΁i�|�P�b�g�R�j�̏����z�u
	for (int i = 0; i < 8; i++) {
		DrawGraph(715, 200 + i * 20, gStone[i][2].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(745, 40 + i * 20, gStone[i][2].img, TRUE);
	}
	// �΁i�|�P�b�g�S�j�̏����z�u
	for (int i = 0; i < 8; i++) {
		DrawGraph(590, 200 + i * 20, gStone[i][3].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(620, 40 + i * 20, gStone[i][3].img, TRUE);
	}
	// �΁i�|�P�b�g�T�j�̏����z�u
	for (int i = 0; i < 8; i++) {
		DrawGraph(460, 200 + i * 20, gStone[i][4].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(430, 40 + i * 20, gStone[i][4].img, TRUE);
	}
	// �΁i�|�P�b�g�U�j�̏����z�u
	for (int i = 0; i < 8; i++) {
		DrawGraph(340, 200 + i * 20, gStone[i][5].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(370, 40 + i * 20, gStone[i][5].img, TRUE);
	}


	// �΁i�S�[���j�̏����z�u
	//for (int y = 0; y < 1; y++) {
	for (int i = 0; i < 15; i++) {
		DrawGraph(1100 /*+ y * 30*/, 170 + i * 20, gGoal[0][i].img, TRUE);
	}
	// }


	//------------- �����܂�-----------------


	// 1P�^�[������ �|�P�b�g�ړ�
	if (P1Turn == 1) {
		if (Pocket_cnt == 0) {
			/*	DrawGraph(255, 385, P1PocketImg, FALSE);*/
			DrawBox(295, 425, 400, 640, GetColor(0, 0, 255), FALSE);
			DrawBox(296, 426, 401, 641, GetColor(0, 0, 255), FALSE);
			DrawBox(297, 427, 402, 642, GetColor(0, 0, 255), FALSE);
		}
		else if (Pocket_cnt == 1) {
			DrawBox(425, 425, 530, 640, GetColor(0, 0, 255), FALSE);
			DrawBox(426, 426, 531, 641, GetColor(0, 0, 255), FALSE);
			DrawBox(427, 427, 532, 642, GetColor(0, 0, 255), FALSE);

		}
		else if (Pocket_cnt == 2) {
			DrawBox(555, 425, 655, 640, GetColor(0, 0, 255), FALSE);
			DrawBox(556, 426, 656, 641, GetColor(0, 0, 255), FALSE);
			DrawBox(557, 427, 657, 642, GetColor(0, 0, 255), FALSE);

		}
		else if (Pocket_cnt == 3) {
			DrawBox(685, 425, 785, 640, GetColor(0, 0, 255), FALSE);
			DrawBox(686, 426, 786, 641, GetColor(0, 0, 255), FALSE);
			DrawBox(687, 427, 787, 642, GetColor(0, 0, 255), FALSE);

		}
		else if (Pocket_cnt == 4) {
			DrawBox(810, 415, 910, 640, GetColor(0, 0, 255), FALSE);
			DrawBox(811, 416, 911, 641, GetColor(0, 0, 255), FALSE);
			DrawBox(812, 417, 912, 642, GetColor(0, 0, 255), FALSE);

		}
		else if (Pocket_cnt == 5) {
			DrawBox(940, 415, 1040, 640, GetColor(0, 0, 255), FALSE);
			DrawBox(941, 416, 1041, 641, GetColor(0, 0, 255), FALSE);
			DrawBox(942, 417, 1042, 642, GetColor(0, 0, 255), FALSE);
		}

	}


	// 2P�^�[�����̃|�P�b�g�ړ�
	if (P2Turn == 1) {
		if (Pocket_cnt == 0) {
			DrawBox(940, 125, 1040, 340, GetColor(255, 0, 0), FALSE);
			DrawBox(941, 126, 1041, 341, GetColor(255, 0, 0), FALSE);
			DrawBox(942, 127, 1042, 342, GetColor(255, 0, 0), FALSE);
		}
		else if (Pocket_cnt == 1) {
			DrawBox(810, 125, 910, 340, GetColor(255, 0, 0), FALSE);
			DrawBox(811, 126, 911, 341, GetColor(255, 0, 0), FALSE);
			DrawBox(812, 127, 912, 342, GetColor(255, 0, 0), FALSE);
		}
		else if (Pocket_cnt == 2) {
			DrawBox(685, 125, 785, 340, GetColor(255, 0, 0), FALSE);
			DrawBox(686, 126, 786, 341, GetColor(255, 0, 0), FALSE);
			DrawBox(687, 127, 787, 342, GetColor(255, 0, 0), FALSE);
		}
		else if (Pocket_cnt == 3) {
			DrawBox(555, 125, 655, 340, GetColor(255, 0, 0), FALSE);
			DrawBox(556, 126, 656, 341, GetColor(255, 0, 0), FALSE);
			DrawBox(557, 127, 657, 342, GetColor(255, 0, 0), FALSE);

		}
		else if (Pocket_cnt == 4) {
		
			DrawBox(415, 125, 525, 340, GetColor(255, 0, 0), FALSE);
			DrawBox(416, 126, 526, 341, GetColor(255, 0, 0), FALSE);
			DrawBox(417, 127, 527, 342, GetColor(255, 0, 0), FALSE);

		}
		else if (Pocket_cnt == 5) {
		
			DrawBox(295, 125, 395, 340, GetColor(255, 0, 0), FALSE);
			DrawBox(296, 126, 396, 341, GetColor(255, 0, 0), FALSE);
			DrawBox(297, 127, 397, 342, GetColor(255, 0, 0), FALSE);
		}

	}

	////�|�P�b�g�̒��ɒl�������Ă��邩
	//for (int i = 0; i < 6; i++) {
	//	DrawFormatString(300 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", P1Pocket[i]);
	//	DrawFormatString(500 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", P2Pocket[i]);
	//}

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
	if (P2Turn == 1) {
		DrawFormatString(100, 30, GetColor(255, 0, 0), "2P TURN");
	}

	if (P1Turn == 1) {
		DrawFormatString(100, 30, GetColor(0, 0, 255), "1P TURN");
	}
	

	DrawFormatString(340, 625, GetColor(255, 255, 255), "%d", P1StoneSave[0]);
	DrawFormatString(340 + 125 * 1, 625, GetColor(255, 255, 255), "%d", P1StoneSave[1]);
	DrawFormatString(340 + 125 * 2, 625, GetColor(255, 255, 255), "%d", P1StoneSave[2]);
	DrawFormatString(340 + 125 * 3, 625, GetColor(255, 255, 255), "%d", P1StoneSave[3]);
	DrawFormatString(340 + 125 * 4, 625, GetColor(255, 255, 255), "%d", P1StoneSave[4]);
	DrawFormatString(340 + 125 * 5, 625, GetColor(255, 255, 255), "%d", P1StoneSave[5]);


	DrawFormatString(340, 125, GetColor(255, 255, 255), "%d", P2StoneSave[5]);
	DrawFormatString(340 + 125 * 1, 125, GetColor(255, 255, 255), "%d", P2StoneSave[4]);
	DrawFormatString(340 + 125 * 2, 125, GetColor(255, 255, 255), "%d", P2StoneSave[3]);
	DrawFormatString(340 + 125 * 3, 125, GetColor(255, 255, 255), "%d", P2StoneSave[2]);
	DrawFormatString(340 + 125 * 4, 125, GetColor(255, 255, 255), "%d", P2StoneSave[1]);
	DrawFormatString(340 + 125 * 5, 125, GetColor(255, 255, 255), "%d", P2StoneSave[0]);
}

void Mankara::MoveStone()
{
	//�@�摜�ړ����̐��I����
	if (P1Turn == 1) {

		// �|�P�b�g�O
		// �|�P�b�g��I��
		if (PlayerPocket == 0) {
			// �|�P�b�g�̒��g��ʂ̃|�P�b�g�̒��ɂ����
			for (int i = 0; i < P1StoneSave[PlayerPocket]; i++) {
				// �҂�����S�[���p����
				if (P1StoneSave[PlayerPocket] > 6) {
					P1BigPocket += 1;
					// �|�P�b�g�𒴉߂������A2P�|�P�b�g�ɓ����
					for (int h = 7; h < (P1StoneSave[PlayerPocket] -= 7); h++) {
						P2StoneSave[i] += 1;
					}
				}

				P1StoneSave[PlayerPocket + i] += 1;

				for (int t = 0; t < 5; t++) {
					gStone[i][t].img = TRUE;

				}
			}
			// �҂�����S�[���ȊO�Ő΂̈ړ����ς񂾎��A2P�^�[���ɐ؂�ւ��
			if (P1StoneSave[PlayerPocket] == 6) {
				P1Turn = 1;
				P2Turn = 0;
			}
			else {
				P2Turn = 1;
				P1Turn = 0;
			}
			// �΂��ړ������|�P�b�g�̒��g���O�ɂ���
			P1StoneSave[PlayerPocket] = 0;
			for (int y = 0; y < 16; y++) {
				gStone[y][PlayerPocket].img = FALSE;
			}
			

		}

		// �|�P�b�g�P
		else if (PlayerPocket == 1) {
			for (int i = 0; i < P1StoneSave[PlayerPocket]; i++) {
				if (P1StoneSave[PlayerPocket] > 5) {
					P1BigPocket += 1;
					for (int h = 6; h < (P1StoneSave[PlayerPocket] -= 6); h++) {
						P2StoneSave[i] += 1;
					}
				}
				//
				P1StoneSave[PlayerPocket + i] += 1;
				for (int t = 0; t < 4; t++) {
					gStone[i][t].img = TRUE;

				}
			}
			if (P1StoneSave[PlayerPocket] == 5) {
				P1Turn = 1;
				P2Turn = 0;
			}
			else {
				P2Turn = 1;
				P1Turn = 0;
			}
			P1StoneSave[PlayerPocket] = 0;
			for (int y = 0; y < 16; y++) {
				gStone[y][PlayerPocket].img = FALSE;
			}
		}
		// �|�P�b�g�Q
		else if (PlayerPocket == 2) {
			for (int i = 0; i < P1StoneSave[PlayerPocket]; i++) {
				if (P1StoneSave[PlayerPocket] > 4) {
					P1BigPocket += 1;
					for (int h = 5; h < (P1StoneSave[PlayerPocket] -= 5); h++) {
						P2StoneSave[i] += 1;
					}
				}
				P1StoneSave[PlayerPocket + i] += 1;
				for (int t = 0; t < 3; t++) {
					gStone[i][t].img = TRUE;

				}
			}
			if (P1StoneSave[PlayerPocket] == 4) {
				P2Turn = 0;
				P1Turn = 1;
			}
			else {
				P2Turn = 1;
				P1Turn = 0;
			}
			P1StoneSave[PlayerPocket] = 0;
			for (int y = 0; y < 16; y++) {
				gStone[y][PlayerPocket].img = FALSE;
			}
		}
		// �|�P�b�g�R
		else if (PlayerPocket == 3) {
			for (int i = 0; i < P1StoneSave[PlayerPocket]; i++) {
				if (P1StoneSave[PlayerPocket] > 3) {
					P1BigPocket += 1;
					for (int h = 4; h < (P1StoneSave[PlayerPocket] -= 4); h++) {
						P2StoneSave[i] += 1;
					}
				}
				P1StoneSave[PlayerPocket + i] += 1;
				for (int t = 0; t < 2; t++) {
					gStone[i][t].img = TRUE;

				}
			}
			if (P1StoneSave[PlayerPocket] == 3) {
				P1Turn = 1;
				P2Turn = 0;
			}
			else {
				P2Turn = 1;
				P1Turn = 0;
			}
			P1StoneSave[PlayerPocket] = 0;
			for (int y = 0; y < 16; y++) {
				gStone[y][PlayerPocket].img = FALSE;
			}
		}
		// �|�P�b�g�S
		else if (PlayerPocket == 4) {
			for (int i = 0; i < P1StoneSave[PlayerPocket]; i++) {
				if (P1StoneSave[PlayerPocket] > 2) {
					P1BigPocket += 1;
					for (int h = 3; h < (P1StoneSave[1] -= 4); h++) {
						P2StoneSave[i] += 1;
					}
				}
				P1StoneSave[PlayerPocket + i] += 1;
				for (int t = 0; t < 1; t++) {
					gStone[i][t].img = TRUE;

				}
			}
			if (P1StoneSave[PlayerPocket] == 2) {
				P1Turn = 1;
				P2Turn = 0;
			}
			else {
				P1Turn = 0;
				P2Turn = 1;
			}
			P1StoneSave[PlayerPocket] = 0;
			for (int y = 0; y < 16; y++) {
				gStone[y][PlayerPocket].img = FALSE;
			}
		}
		// �|�P�b�g�T
		else if (PlayerPocket == 5) {
			for (int i = 0; i < P1StoneSave[PlayerPocket]; i++) {
				if (P1StoneSave[PlayerPocket] > 2) {
					P1BigPocket += 1;
					for (int h = 5; h < (P1StoneSave[PlayerPocket] -= 5); h++) {
						P2StoneSave[i] += 1;
					}
				}
				P1StoneSave[PlayerPocket + i] += 1;
				for (int t = 0; t < 0; t++) {
					gStone[i][t].img = TRUE;

				}
			}
			if (P1StoneSave[PlayerPocket] == 1) {
				P1Turn = 1;
				P2Turn = 0;
			}
			else {
				P1Turn = 0;
				P2Turn = 1;
			}
			P1StoneSave[PlayerPocket] = 0;
			for (int y = 0; y < 16; y++) {
				gStone[y][PlayerPocket].img = FALSE;
			}
		}
	}
	if (P2Turn == 1) {


		// �|�P�b�g��I��
		if (PartnerPocket == 0) {
			for (int i = 0; i < P2StoneSave[PartnerPocket]; i++) {
				if (P2StoneSave[PartnerPocket] > 6) {
					P2BigPocket += 1;
					for (int h = 7; h < (P2StoneSave[PartnerPocket] -= 7); h++) {
						P1StoneSave[i] += 1;
					}
				}
				P2StoneSave[PartnerPocket + i] += 1;

			}
			if (P2StoneSave[PartnerPocket] == 6) {
				P2Turn = 1;
				P1Turn = 0;
			}
			else {
				P1Turn = 1;
				P2Turn = 0;
			}
			P2StoneSave[PartnerPocket] = 0;

		}
		else if (PartnerPocket == 1) {
			for (int i = 0; i < P2StoneSave[PartnerPocket]; i++) {
				if (P2StoneSave[PartnerPocket] > 5) {
					P2BigPocket += 1;
					for (int h = 6; h < (P2StoneSave[PartnerPocket] -= 6); h++) {
						P1StoneSave[i] += 1;
					}
				}
				P2StoneSave[PartnerPocket + i] += 1;
			}
			if (P2StoneSave[PartnerPocket] == 5) {
				P2Turn = 1;
				P1Turn = 0;
			}
			else {
				P1Turn = 1;
				P2Turn = 0;
			}
			P2StoneSave[PartnerPocket] = 0;
		}
		else if (PartnerPocket == 2) {
			for (int i = 0; i < P2StoneSave[PartnerPocket]; i++) {
				if (P2StoneSave[PartnerPocket] > 4) {
					P2BigPocket += 1;
					for (int h = 5; h < (P2StoneSave[PartnerPocket] -= 5); h++) {
						P1StoneSave[i] += 1;
					}
				}
				P2StoneSave[PartnerPocket + i] += 1;
			}
			if (P2StoneSave[PartnerPocket] == 4) {
				P2Turn = 1;
				P1Turn = 0;
			}
			else {
				P1Turn = 1;
				P2Turn = 0;
			}
			P2StoneSave[PartnerPocket] = 0;
		}
		else if (PartnerPocket == 3) {
			for (int i = 0; i < P2StoneSave[PartnerPocket]; i++) {
				if (P2StoneSave[PartnerPocket] > 3) {
					P2BigPocket += 1;
					for (int h = 4; h < (P2StoneSave[PartnerPocket] -= 4); h++) {
						P1StoneSave[i] += 1;
					}
				}
				P2StoneSave[PartnerPocket + i] += 1;
			}
			if (P2StoneSave[PartnerPocket] == 3) {
				P2Turn = 1;
				P1Turn = 0;
			}
			else {
				P1Turn = 1;
				P2Turn = 0;
			}
			P2StoneSave[PartnerPocket] = 0;
		}
		else if (PartnerPocket == 4) {
			for (int i = 0; i < P2StoneSave[PartnerPocket]; i++) {
				if (P2StoneSave[PartnerPocket] > 3) {
					P2BigPocket += 1;
					for (int h = 4; h < (P2StoneSave[PartnerPocket] -= 4); h++) {
						P1StoneSave[i] += 1;
					}
				}
				P2StoneSave[PartnerPocket + i] += 1;
			}
			if (P2StoneSave[PartnerPocket] == 2) {
				P2Turn = 1;
				P1Turn = 0;
			}
			else {
				P1Turn = 1;
				P2Turn = 0;
			}
			P2StoneSave[PartnerPocket] = 0;
		}
		else if (PartnerPocket == 5) {
			for (int i = 0; i < P2StoneSave[PartnerPocket]; i++) {
				if (P2StoneSave[PartnerPocket] > 2) {
					P2BigPocket += 1;
					for (int h = 5; h < (P2StoneSave[PartnerPocket] -= 5); h++) {
						P1StoneSave[i] += 1;

					}
				}
				P2StoneSave[PartnerPocket + i] += 1;
			}
			if (P2StoneSave[PartnerPocket] == 1) {
				P2Turn = 1;
				P1Turn = 0;
			}
			else {
				P1Turn = 1;
				P2Turn = 0;
			}
			P2StoneSave[PartnerPocket] = 0;
		}
	}
}

void Mankara::WinLose()
{
	if (P1BigPocket >= 25) {
		DrawFormatString(500, 500, GetColor(255, 255, 255), "1P  WIN");
		DrawFormatString(500, 600, GetColor(255, 255, 255), "2P  LOSE");
	}
		
	if (P2BigPocket >= 25) {
		DrawFormatString(500, 500, GetColor(255, 255, 255), "2P  WIN");
		DrawFormatString(500, 600, GetColor(255, 255, 255), "1P  LOSE");

	}
		
		/*DrawFormatString(500, 500, GetColor(255, 255, 255), "DRAW");*/
	
}
