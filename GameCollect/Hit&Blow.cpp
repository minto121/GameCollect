#include"Hit&Blow.h"
#include"DxLib.h"
#include"PadInput.h"
#include"GameSelect.h"
#include"Title.h"
#include"FpsController.h"
#include<stdlib.h>
#include<time.h>
#define WAITTIME 180 // ��ʑJ�ڂ���ҋ@���ԁi�Œ�p�j

HitAndBlow::HitAndBlow()
{
	/* �摜�ǂݍ��� */
	TableBgImg = LoadGraph("images/HitAndBlow/BackGround02.png");

	BoardImg = LoadGraph("images/HitAndBlow/HitBlowBoard.png");

	LoadDivGraph("images/HitAndBlow/ColorBall.png", 6, 6, 1, 64, 64, ColorImg);
	LoadDivGraph("images/HitAndBlow/HitBlowPin.png", 2, 2, 1, 32, 32, HitBlowImg);

	/* BGM�ESE�ǂݍ��� */
	PutPinSE = LoadSoundMem("../sound/SE/PutPin.wav");
	HitPinSE = LoadSoundMem("../sound/SE/HitPin.wav");
	BlowPinSE = LoadSoundMem("../sound/SE/BlowPin.wav");

	DecisionFlg = TRUE; // ��������񂾂����߂�t���O��TRUE�ɂ���
	TurnFlg = TRUE;

	WarpPosition = 0;
	SidePosition = 0;

	Turns = 0;

	ArrayInit();

	SaveColor = 0; // �Z�[�u�J���[������

	Hit = 0;  // �q�b�g�̐���������
	Blow = 0;  // �u���[�̐���������

	Count = 0; // �J�E���g�̏�����

	MoveFlg = -1; // ��U��U�ł���U�ł��Ȃ��l������

	ChangeColor = -1; // �ꏊ�����ς���ϐ���������

	FirstMoveFlg = -1;

	/* �f�o�b�N�p */
	Covering = 0;
	CoveringFlg = FALSE;

	DescriptionFlg = TRUE;
	OperationFlg = TRUE;

	WinLoseDrawFlg = -1;
}

HitAndBlow::~HitAndBlow()
{
	/* �������e�ʌy�����邽�߁A���y�t�@�C�������Ă��� */
	DeleteSoundMem(PutPinSE);
	DeleteSoundMem(HitPinSE);
	DeleteSoundMem(BlowPinSE);
}

AbstractScene* HitAndBlow::Update()
{
	RandomDecision(); // �����̔z��������_���ɐݒ肷��

	FontSize = GetFontSize();

	if (DescriptionFlg == TRUE) { // ������ʂɂ����
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
			//if (Count < 60) { // 1�b�����ĂȂ�������A
			//	Count++; // 1�t���[������
			//}
			//else { // �{�^���������āA1�b��������
			//	Count = 0; // �J�E���g�����Z�b�g���āA
			//	DescriptionFlg = FALSE; // ������ʂ����
			//}
			DescriptionFlg = FALSE; // ������ʂ����
			OperationFlg = TRUE; // ���������ʂɓ���
		}
		/* �����Ɏ�����������鏈�������� */
	}
	else if (OperationFlg == TRUE) {
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
			OperationFlg = FALSE; // ���������ʂ����
		}
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {
			OperationFlg = FALSE; // ���������ʂ����
			DescriptionFlg = TRUE; // ������ʂɖ߂�
		}
	}else if (DescriptionFlg == FALSE && OperationFlg == FALSE && WinLoseDrawFlg == -1 && Turns < 8 && SaveHit[Turns - 1] != 4) {
	
		//�\���L�[������
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
		{
			WarpPosition--;
			if (WarpPosition < 0) WarpPosition = 3; // �ʒu��0�����Ȃ�A0�ɂ���
		}

		// �\���L�[������
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
		{
			WarpPosition++;
			if (WarpPosition > 3) WarpPosition = 0; // �ʒu��3�𒴂�����A3�ɂ���
		}

		// �\���L�[������
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT))
		{
			Color[SidePosition--];
			if (SidePosition < 0) SidePosition = 5; // �ʒu��0�����ɂȂ�����A5�ɂ���
		}

		//�\���L�[������
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT))
		{
			Color[SidePosition++];
			if (SidePosition > 5) SidePosition = 0; // �ʒu��5�𒴂�����A0�ɖ߂�
		}

		if (MoveFlg == 0) { // �G����鏈��		
			ERandomChoice(); // �K���ɐF������

			Judgment(); // �W���b�W�����Ă�

			/* ����炷���� */
			PlaySoundSE();

			/* �v���C���[�^�[���ɍs���O�ɐF�����Z�b�g */
			ResetColor();
			MoveFlg = 1; // �����̃^�[���Ɉړ�
		}
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_X) && Reasoning[0] != -1 && Reasoning[1] != -1 && Reasoning[2] != -1 && Reasoning[3] != -1) // �F�������Ă��鎞
		{
			Judgment(); // �W���b�W�������Ă�

			/* ����炷���� */
			PlaySoundSE();

			/* �G�l�~�[�^�[���ɍs���O�ɐF�����Z�b�g */
			ResetColor();
			MoveFlg = 0; // �G�̃^�[���Ɉړ�
		}
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) // �F�����鏈��
		{
			Reasoning[WarpPosition] = SidePosition;  // �F���ꏊ�ɔz�u
			WarpPosition++; // �F��I������J�[�\���̈ʒu������炷
			PlaySoundMem(PutPinSE, DX_PLAYTYPE_NORMAL, TRUE);
			if (WarpPosition > 3) WarpPosition = 0; // �ʒu��3�𒴂�����A��ԏ�ɂ���
		}
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) { // �F���O������
			Reasoning[WarpPosition] = -1;
		}
	}
	else {
		/* ���b���҂�������� */
		if (SaveHit[Turns - 1] == 4) {
			if (Count < WAITTIME) {
				Count++;
			}
			else if (MoveFlg == 0) {
				Count = 0; // �J�E���g�����Z�b�g
				WinLoseDrawFlg = 1; // ���s�t���O��������Ԃɂ���
			}
			else {
				Count = 0; // �J�E���g�����Z�b�g
				WinLoseDrawFlg = 2; // ���s�t���O�𕉂���Ԃɂ���
			}
		}
		else {
			if (Count < WAITTIME) {
				Count++;
			}
			else {
				Count = 0; // �J�E���g�����Z�b�g
				WinLoseDrawFlg = 0; // ���s�t���O������������Ԃɂ���
			}
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && WinLoseDrawFlg != -1) {
			SetFontSize(FontSize); // �t�H���g�T�C�Y�����ɖ߂�
			return new GameSelect();// �Q�[���Z���N�g��ʂɑJ��
		}
	}



	
	return this;
}

void HitAndBlow::Draw() const
{
	DrawGraph(0, 0, TableBgImg, FALSE); // �w�i�摜�\��(����OFF)

	if (DescriptionFlg == TRUE) { // �Q�[���̗V�ѕ��E���s�ɂ���
		SetFontSize(40);
		DrawFormatString(500, 0, 0xffffff, "���Q�[���̗V�ѕ���");
		DrawFormatString(500, 480, 0xffffff, "���Q�[���̏��s��");

		SetFontSize(30);
		/* �Q�[���̗V�ѕ� */
		DrawFormatString(0, 50, 0xffffff, "���U�F�̐F�i�ԁA�A�΁A���A���A���j���烉���_���ɑI�΂��");
		DrawFormatString(0, 80, 0xffffff, "�S�F�̐F�ƈʒu�𓖂Ă�Q�[��!");
		DrawFormatString(0, 110, 0xffffff, "���v���C���[����ёΐ푊��́A�S�F�̐F�ƈʒu��\�z����B");
		DrawFormatString(0, 140, 0xff0000, "���q���g�Ƃ��āA�F�ƈʒu���������Ă���u�q�b�g�v�ƁA");
		DrawFormatString(0, 170, 0xff0000, "�F�����������Ă���u�o�C�g�v�������邩�A");
		DrawFormatString(0, 200, 0xff0000, "���ꂼ�ꋳ���Ă��炦��B�������A");
		DrawFormatString(0, 230, 0xff0000, "�ǂ����q�b�g���Ă��āA�ǂ̐F���o�C�g���Ă��邩�܂ł͋����Ă��炦�Ȃ��B");
		DrawFormatString(0, 260, 0x00ff00, "��j�ݒ肳�ꂽ�F�����E���E�ԁE�����Ƃ��āA");
		DrawFormatString(0, 290, 0x00ff00, "�v���C���[���E�ԁE�΁E���Ɨ\�z�����ꍇ�A");
		DrawFormatString(0, 320, 0x00ff00, "�v���C���[�̃q���g�Ƃ��āA1�q�b�g1�u���[");
		DrawFormatString(0, 350, 0x00ff00, "�i���͐F�ƈʒu�������Ă�̂�1�q�b�g�A�Ԃ͐F���������Ă�̂�1�u���[�j");
		DrawFormatString(0, 380, 0x00ff00, "�Ƃ�����񂪗^������B");
		DrawFormatString(0, 410, 0xffffff, "��������J��Ԃ��āA���4�q�b�g");
		DrawFormatString(0, 440, 0xffffff, "�i�܂�A4�̐F�ƈʒu���S�ē������Ă����ԁj����Ώ����ƂȂ�B");

		/* �Q�[���̏��s */
		DrawFormatString(0, 520, 0xffffff, "�������_���Ɍ��܂��Ă���F�Əꏊ��S�ē��Ă��i4�q�b�g�����j���̏����I");
		DrawFormatString(0, 550, 0xffffff, "�������Ƒΐ푊�肪���v8�^�[���ȓ��ɐF�Əꏊ��S�ē��Ă��Ȃ������ꍇ�́A");
		DrawFormatString(0, 580, 0xffffff, "���������ƂȂ�B");

		/* �J�ڂ������镶��*/
		SetFontSize(60);
		DrawFormatString(300, 620, 0xffffff, "A�{�^���ő�����@��ʂ�");
	}
	else if (OperationFlg == TRUE) {
		SetFontSize(40);
		DrawFormatString(500, 0, 0xffffff, "��������@��");
		DrawFormatString(500, 240, 0xffffff, "�����[����");


		SetFontSize(30);
		DrawFormatString(0, 50, 0xffffff, "���\���L�[�́��A���ŐF��I������J�[�\���������B");
		DrawFormatString(0, 80, 0xffffff, "���\���L�[�́��A���ŐF��u���ꏊ�̃J�[�\���������B");
		DrawFormatString(0, 110, 0xffffff, "��A�{�^���ŐF��u�����Ƃ��o����B");
		DrawFormatString(0, 140, 0xffffff, "��B�{�^���Œu���Ă����F����邱�Ƃ��o����B");
		DrawFormatString(0, 170, 0xffffff, "��4�S�Ēu������ԂŁAX�{�^���������ƁA");
		DrawFormatString(0, 200, 0xffffff, "�u���Ă���F���m�肷��B");
		/* �q�b�g�s���̉摜�Ɛ��� */
		DrawFormatString(0, 280, 0xffffff, "��");
		DrawGraph(30, 280, HitBlowImg[1], TRUE);
		DrawFormatString(70, 280, 0xffffff, "�q�b�g�s���F�F�Əꏊ�������Ă���");
		/* �u���[�s���̉摜�Ɛ��� */
		DrawFormatString(0, 310, 0xffffff, "��");
		DrawGraph(30, 310, HitBlowImg[0], TRUE);
		DrawFormatString(70, 310, 0xffffff, "�u���[�s���F�F�݂̂������Ă���");
		DrawFormatString(0, 340, 0xffffff, "����U�E��U�̓����_���Ō��߂���B");
		DrawFormatString(0, 370, 0xffffff, "���v���C���[�̃^�[���̏ꏊ�́A");
		DrawFormatString(480, 370, 0xff0000, "P");
		DrawFormatString(0, 400, 0xffffff, "������̃^�[���̏ꏊ�́A");
		DrawFormatString(390, 400, 0x00ffff, "E");
		DrawFormatString(420, 400, 0xffffff, "�Ə�ɕ\�������B");

		SetFontSize(60);
		DrawFormatString(300, 560, 0xffffff, "A�{�^���ŃQ�[���X�^�[�g");
		DrawFormatString(300, 620, 0xffffff, "B�{�^���ŃQ�[���̗V�ѕ���ʂ�");


	}
	else if (WinLoseDrawFlg == 0 || WinLoseDrawFlg == 1 || WinLoseDrawFlg == 2) {
		switch (WinLoseDrawFlg) {
		case 0:
			SetFontSize(60);
			DrawFormatString(300, 360, 0x00ff00, "���������ł��B");
			DrawFormatString(300, 500, 0xffffff, "A�{�^���ŃQ�[�������N�g��ʂ�");
			break;
		case 1:
			SetFontSize(60);
			DrawFormatString(300, 360, 0xff0000, "���Ȃ��̏����ł��I�I");
			DrawFormatString(300, 500, 0xffffff, "A�{�^���ŃQ�[�������N�g��ʂ�");
			break;
		case 2:
			SetFontSize(60);
			DrawFormatString(300, 360, 0x0000ff, "���Ȃ��̕����ł��E�E�E");
			DrawFormatString(300, 500, 0xffffff, "A�{�^���ŃQ�[�������N�g��ʂ�");
			break;
		}
	}
	else { // �Q�[�����C���摜����
		DrawGraph(0, 0, BoardImg, TRUE); // �{�[�h�摜�\��

		for (int i = 0; i < 6; i++) { // ���\��
			DrawGraph(350 + i * 100, 600, ColorImg[i], TRUE); // ���ꂼ��̐F�̋��\��(�ʒu�͌���)
		}
		if (Turns < 8 && SaveHit[Turns - 1] != 4) {
			DrawBox(350 + SidePosition * 100, 595, 420 + SidePosition * 100, 665, 0xff0000, FALSE); // �F�𖄂߂�ꏊ���ǂ��ɂ��邩��������{�b�N�X
			DrawBox(80 + Turns * 130, 210 + WarpPosition * 80, 160 + Turns * 130, 290 + WarpPosition * 80, 0x00ff00, FALSE); // �ǂ��̏ꏊ�𖄂߂悤�Ƃ��Ă��邩�\��
		}

		//DrawFormatString(100, 600, 0xffffff, "Turns��%d", CoveringFlg); // �f�o�b�N�p
		//DrawFormatString(100, 700, 0xffffff, "Covering��%d", Covering); // �f�o�b�N�p
		/* �\�z�����J���[��\������ */
		if (Reasoning[WarpPosition % 4] >= 0) {
			DrawGraph(90 + Turns * 130, 220 + WarpPosition * 80, ColorImg[Reasoning[WarpPosition % 4]], TRUE); // �\�z���摜�ŕ\��
		}

		if (Reasoning[(WarpPosition + 1) % 4] >= 0) {
			DrawGraph(90 + Turns * 130, 220 + (WarpPosition + 1) % 4 * 80, ColorImg[Reasoning[(WarpPosition + 1) % 4]], TRUE); // �\�z���摜�ŕ\��
		}

		if (Reasoning[(WarpPosition + 2) % 4] >= 0) {
			DrawGraph(90 + Turns * 130, 220 + (WarpPosition + 2) % 4 * 80, ColorImg[Reasoning[(WarpPosition + 2) % 4]], TRUE); // �\�z���摜�ŕ\��
		}

		if (Reasoning[(WarpPosition + 3) % 4] >= 0) {
			DrawGraph(90 + Turns * 130, 220 + (WarpPosition + 3) % 4 * 80, ColorImg[Reasoning[(WarpPosition + 3) % 4]], TRUE); // �\�z���摜�ŕ\��
		}


		for (int i = 0; i < 4; i++) {
			if (SaveHit[Turns - 1] == 4 || Turns == 8) { // 8�^�[���o�߂��A4�q�b�g������\��
				DrawGraph(1125, 220 + i * 80, ColorImg[Answer[i]], TRUE); // �������摜�ŕ\��
			}
		}

		for (int i = 0; i < Turns; i++) {
			/* �ߋ��ɓ��ꂽ�F��\�� */
			DrawGraph(90 + i * 130, 220, ColorImg[SaveReasoning[i][0]], TRUE);
			DrawGraph(90 + i * 130, 220 + 1 * 80, ColorImg[SaveReasoning[i][1]], TRUE);
			DrawGraph(90 + i * 130, 220 + 2 * 80, ColorImg[SaveReasoning[i][2]], TRUE);
			DrawGraph(90 + i * 130, 220 + 3 * 80, ColorImg[SaveReasoning[i][3]], TRUE);

			/* �W���b�W�p�̕`�揈�������� */
			for (int j = 0; j < SaveHit[i]; j++) {
				DrawGraph(80 + (j % 2) * 35 + i * 130, 100 + (j / 2) * 40, HitBlowImg[1], TRUE);
			}
			for (int k = 0; k < SaveBlow[i]; k++) {
				DrawGraph(80 + ((SaveHit[i] + k) % 2) * 35 + i * 130, 100 + ((SaveHit[i] + k) / 2) * 40, HitBlowImg[0], TRUE);
			}
		}
		for (int i = 0; i < 8; i++) {
			SetFontSize(32);
			if (FirstMoveFlg == TRUE) {
				if (i % 2 == 0) {
					DrawFormatString(110 + (i / 2) * 260, 50, 0xff0000, "P"); // �v���C���[�̏��Ԃ���ɕ\��
				}
				else {
					DrawFormatString(240 + (i / 2) * 260, 50, 0x00ffff, "E"); // �G�l�~�[�̏��Ԃ���ɕ\��
				}
			}
			else if (i % 2 == 0) {
				DrawFormatString(110 + (i / 2) * 260, 50, 0x00ffff, "E"); // �G�l�~�[�̏��Ԃ���ɕ\��
			}
			else {
				DrawFormatString(240 + (i / 2) * 260, 50, 0xff0000, "P"); // �v���C���[�̏��Ԃ���ɕ\��
			}

		}

	}

}

void HitAndBlow::RandomDecision()
{
	/* �����̔z��������_���ɐݒ肷�� */
	srand((unsigned int)time(NULL));

	if (DecisionFlg == TRUE) {
		for (int i = 0; i < 4; i++) {
			Answer[i] = GetRand(5);
			if (Answer[i] == Answer[(i + 1) % 4] || Answer[i] == Answer[(i + 2) % 4] || Answer[i] == Answer[(i + 3) % 4]) { // �F���d�Ȃ�����
				i--; // �I�ʂ���蒼��
			}
		}
		DecisionFlg = FALSE;
	}
	/* ��U�E��U�������_���Ɍ��߂� */
	if (TurnFlg == TRUE) {
		MoveFlg = GetRand(1);
		TurnFlg = FALSE;
		FirstMoveFlg = MoveFlg; // ��U����U�����o���Ă��炤�i�`�揈���ŕK�v�j
	}
	
}

void HitAndBlow::ERandomChoice()
{
	/* �����̔z��������_���ɐݒ肷�� */
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 4; i++) {
		if (SaveHit[Turns - 1] + SaveBlow[Turns - 1] == 4) {// �O�̃^�[���Ńq�b�g�ƃu���[�̍��v�̐����S�ɂȂ�����
			Reasoning[i] = SaveReasoning[Turns - 1][GetRand(3)]; // �ꏊ�����ς���
			if (Reasoning[i] == Reasoning[(i + 1) % 4] || Reasoning[i] == Reasoning[(i + 2) % 4] || Reasoning[i] == Reasoning[(i + 3) % 4]) { // ���Ԕ���Ă���
				i--; // i�̒��I��蒼��
			}
			/* �S�������F�A���ԂɂȂ��ĂȂ����m���߂鏈�� */
			if (Turns != 0 && i == 3) {
				CheckCovered();
				if (CoveringFlg == TRUE) { // �����A����Ă�����
					i = -1; // 0��������3�����������Ȃ��̂ŁA�C���N�������g����0�ɂȂ�-1����
				}
			}
		}
		else if (SaveHit[Turns - 2] + SaveBlow[Turns - 2]) {// �O�̎����̃^�[���Ńq�b�g�ƃu���[�̍��v�̐����S�ɂȂ�����
			Reasoning[i] = SaveReasoning[Turns - 2][GetRand(3)]; // �ꏊ�����ς���
			if (Reasoning[i] == Reasoning[(i + 1) % 4] || Reasoning[i] == Reasoning[(i + 2) % 4] || Reasoning[i] == Reasoning[(i + 3) % 4]) { // ���Ԕ���Ă���
				i--; // i�̒��I��蒼��
			}
			/* �S�������F�A���ԂɂȂ��ĂȂ����m���߂鏈�� */
			if (Turns != 0 && i == 3) {
				CheckCovered(); // ���Ȃ����m�F
				if (CoveringFlg == TRUE) {
					i = -1; // 0��������3�����������Ȃ��̂ŁA�C���N�������g����0�ɂȂ�-1����
				}
			}
		}
		else {
			Reasoning[i] = rand() % 6;

			if (Reasoning[i] == Reasoning[(i + 1) % 4] || Reasoning[i] == Reasoning[(i + 2) % 4] || Reasoning[i] == Reasoning[(i + 3) % 4]) { // �F���d�Ȃ�����
				i--; // �I�ʂ���蒼��
			}

			/* �S�������F�A���ԂɂȂ��ĂȂ����m���߂鏈�� */
			if (Turns != 0 && i == 3) {	
				CheckCovered(); // ���Ȃ����m�F
				if (CoveringFlg == TRUE) {
					i = -1; // 0��������3�����������Ȃ��̂ŁA�C���N�������g����0�ɂȂ�-1����
				}
			}			
			// 1�^�[���ڂɓ�����̂�j�~
			if (Turns / 2 == 0 && Reasoning[0] == Answer[0] && Reasoning[1] == Answer[1] && Reasoning[2] == Answer[2] && Reasoning[3] == Answer[3]) {
				i = -1; // i���ŏ��ɖ߂�(0��������3�����������Ȃ��̂ŁA�C���N�������g����0�ɂȂ�-1����)
			}
		}
	}
}

void HitAndBlow::Judgment()
{
	for (int i = 0; i < 4; i++) {
		if (Reasoning[i] == Answer[i]) {
			Hit++; // hit�ɂP�𑫂�
		}
		else if (Reasoning[i] == Answer[(i + 1) % 4] || Reasoning[i] == Answer[(i + 2) % 4] || Reasoning[i] == Answer[(i + 3) % 4]) { // �F�������������Ă���Ƃ��A
			/* �F���ǂ����������Ă������̏��� */
			if (Reasoning[i] == Reasoning[(i + 1) % 4] || Reasoning[i] == Reasoning[(i + 2) % 4] || Reasoning[i] == Reasoning[(i + 3) % 4]) {	
				if (Reasoning[i] == Reasoning[(i + 1) % 4] && Reasoning[(i + 1) % 4] != Answer[(i + 1) % 4]) {// ����Ă���ꏊ�̐F���q�b�g���Ă��Ȃ����m�F	
					if (Reasoning[(i + 1) % 4] != Reasoning[(i + 2) % 4] && Reasoning[(i + 1) % 4] != Reasoning[(i + 3) % 4]) {// 2�d�ɔ��肵�Ă��Ȃ����m�F
						if ((i + 1) / 4 == 0) {// �u���[���Q�d�ɉ��Z����Ă��Ȃ���΁A
							Blow++; // blow�ɂP�𑫂�
						}
					}
				}
				// ���̏ꏊ�̐F���q�b�g���Ă��Ȃ��āA�u���[���Q�d�ɉ��Z����Ă��Ȃ���΁A
				if (Reasoning[i] == Reasoning[(i + 2) % 4] && Reasoning[(i + 2) % 4] != Answer[(i + 2) % 4]) {
					if (Reasoning[(i + 2) % 4] != Reasoning[(i + 3) % 4]) { // 2�d�ɔ��肵�Ă��Ȃ����m�F
						if ((i + 2) / 4 == 0) {// �u���[���Q�d�ɉ��Z����Ă��Ȃ���΁A
							Blow++; // blow�ɂP�𑫂�
						}
					}
				}
				// ���̏ꏊ�̐F���q�b�g���Ă��Ȃ��āA�u���[���Q�d�ɉ��Z����Ă��Ȃ���΁A
				if (Reasoning[i] == Reasoning[(i + 3) % 4] && Reasoning[(i + 3) % 4] != Answer[(i + 3) % 4] 
					&& Reasoning[(i + 2) % 4] != Answer[(i + 2) % 4] && Reasoning[(i + 1) % 4] != Answer[(i + 1) % 4]) {
					if ((i + 3) / 4 == 0) {// �u���[���Q�d�ɉ��Z����Ă��Ȃ���΁A
						Blow++; // blow�ɂP�𑫂�
					}	
				}
			}
			else { // ���̐F����Ă��Ȃ����
				Blow++; // blow�ɂP�𑫂�
			}
		}
	}
	SaveHit[Turns] = Hit; // ���̃^�[���̃q�b�g���������i�[
	SaveBlow[Turns] = Blow; // ���̃^�[���̃u���[���������i�[

}

void HitAndBlow::ResetColor() 
{
	/* �F�̃f�[�^�����p�� */
	SaveReasoning[SaveColor][0] = Reasoning[0];
	SaveReasoning[SaveColor][1] = Reasoning[1];
	SaveReasoning[SaveColor][2] = Reasoning[2];
	SaveReasoning[SaveColor][3] = Reasoning[3];

	SaveColor++; // �`���1�ǉ�
	Turns++; // �^�[����1����

	for (int i = 0; i < 4; i++) {
		/* �F�����Z�b�g */
		Reasoning[i] = -1;
	}

	WarpPosition = 0;

	Hit = 0;
	Blow = 0;

}

void HitAndBlow::ArrayInit()
{
	for (int i = 0; i < 4; i++) {
		Reasoning[i] = -1;// ���g�S����ɂ���
		Answer[i] = -1;
	}

	for (int j = 0; j < 8; j++) {
		SaveHit[j] = 0;
		SaveBlow[j] = 0;
		for (int k = 0; k < 4; k++) {
			SaveReasoning[j][k] = 0;
		}
	}

	for (int m = 0; m < 6; m++) {
		Color[m] = 0;
	}
}

void HitAndBlow::CheckCovered()
{
	for (Covering = 0; Covering < Turns; Covering++) {
		if (Reasoning[0] == SaveReasoning[Covering][0]
			&& Reasoning[1] == SaveReasoning[Covering][1]
			&& Reasoning[2] == SaveReasoning[Covering][2]
			&& Reasoning[3] == SaveReasoning[Covering][3]) { // �O���ꂽ�z�ƑS��������������
			
			CoveringFlg = TRUE; // ����Ă����ƒm�点��

			Reasoning[0] = -1;// ���g�S����ɂ���
			Reasoning[1] = -1;// ���g�S����ɂ���
			Reasoning[2] = -1;// ���g�S����ɂ���
			Reasoning[3] = -1;// ���g�S����ɂ���

			break; // ��肪���邩���ׂ����̂ŁA��x������烋�[�v�𔲂���

		}
		else {
			CoveringFlg = FALSE; // ����Ă��Ȃ��ƒm�点��
		}

	}
}

void HitAndBlow::PlaySoundSE() 
{
	/* ����炷���� */
	for (int i = 0; i < SaveHit[Turns]; i++) {
		if (CheckSoundMem(HitPinSE) == 0) { // �Đ������Ă��Ȃ�������
			if (CheckSoundMem(BlowPinSE) == 0) {
				PlaySoundMem(HitPinSE, DX_PLAYTYPE_BACK, TRUE); // �Đ�����
				Count = 0; // �J�E���g���Ԃ����Z�b�g
			}
			else {
				i--;
			}
		}
		else {
			Count++;
			i--;
		}
		Count = 0;// �J�E���g���Ԃ����Z�b�g
	}
	Count = 0; // �J�E���g���Ԃ����Z�b�g
	for (int i = 0; i < SaveBlow[Turns] + 1; i++) {
		if (CheckSoundMem(BlowPinSE) == 0) { // �Đ������Ă��Ȃ�������
			if (CheckSoundMem(HitPinSE) == 0) {
				PlaySoundMem(BlowPinSE, DX_PLAYTYPE_BACK, TRUE); // �Đ�����
				Count = 0; // �J�E���g���Ԃ����Z�b�g
			}
			else {
				i--;
			}	
		}
		else {
			Count++;
			i--;
		}
	}
	StopSoundMem(BlowPinSE);
	Count = 0;// �J�E���g���Ԃ����Z�b�g
}
