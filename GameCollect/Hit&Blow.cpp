#include"Hit&Blow.h"
#include"DxLib.h"
#include"PadInput.h"
#include"GameSelect.h"
#include"Title.h"
#include"FpsController.h"
#include<stdlib.h>
#include<time.h>

HitAndBlow::HitAndBlow()
{
	TableBgImg = LoadGraph("../images/HitAndBlow/BackGround02.png");

	BoardImg = LoadGraph("../images/HitAndBlow/HitBlowBoard.png");

	LoadDivGraph("../images/HitAndBlow/ColorBall.png", 6, 6, 1, 64, 64, ColorImg);
	LoadDivGraph("../images/HitAndBlow/HitBlowPin.png", 2, 2, 1, 32, 32, HitBlowImg);

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
}

HitAndBlow::~HitAndBlow()
{

}

AbstractScene* HitAndBlow::Update()
{
	//FirstMove(); // ���Ԍ��ߊ֐�

	RandomDecision(); // �����̔z��������_���ɐݒ肷��

	//// �f�o�b�N�p
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER))
	//{
	//	Turns++;
	//	if (Turns > 7) {
	//		Turns = 7;
	//	}
	//}

	//// �f�o�b�N�p
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_LEFT_SHOULDER))
	//{
	//	Turns--;
	//	if (Turns < 0) {
	//		Turns = 0;
	//	}
	//}


	/* �����Ɏ�����������鏈�������� */
	if (Turns < 8 && SaveHit[Turns - 1] != 4)
	{
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
			ERandomChoice();
			Judgment();

			ResetColor();

			MoveFlg = 1;
		}
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_X) && Reasoning[0] != -1 && Reasoning[1] != -1 && Reasoning[2] != -1 && Reasoning[3] != -1) // �F�������Ă��鎞
		{
			/* �W���b�W���������� */
			Judgment();
			ResetColor();
			MoveFlg = 0;
		}
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) // �F�����鏈��
		{
			Reasoning[WarpPosition] = SidePosition;  // �F���ꏊ�ɔz�u
			WarpPosition++; // �F��I������J�[�\���̈ʒu������炷
			if (WarpPosition > 3) WarpPosition = 0; // �ʒu��3�𒴂�����A3�ɂ���
		}
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) { // �F���O������
			Reasoning[WarpPosition] = -1;
		}
	}
	else {
		/* ���b���҂�������� */
		if (SaveHit[Turns - 1] == 4) {
			if (Count < 300) {
				Count++;
			}
			else if(MoveFlg == 0){
				Count = 0; // �J�E���g�����Z�b�g
				return new Title();// �J�ڏꏊ�͈�U�u���Ă邾��(�v���C���[Win)
			}
			else {
				Count = 0; // �J�E���g�����Z�b�g
				return new Title();// �J�ڏꏊ�͈�U�u���Ă邾��(�v���C���[Lose)
			}
		}
		else {
			if (Count < 300) {
				Count++;
			}
			else {
				Count = 0; // �J�E���g�����Z�b�g
				return new GameSelect();// �J�ڏꏊ�͈�U�u���Ă邾��(�h���[)
			}
		}
	}

	return this;
}

void HitAndBlow::Draw() const
{
	DrawGraph(0, 0, TableBgImg, FALSE); // �w�i�摜�\��(����OFF)

	DrawGraph(0, 0, BoardImg, TRUE); // �{�[�h�摜�\��

	for (int i = 0; i < 6; i++) { // ���\��
		DrawGraph(350 + i * 100, 600, ColorImg[i], TRUE); // ���ꂼ��̐F�̋��\��(�ʒu�͌���)
	}
	if (Turns < 8 && SaveHit[Turns - 1] != 4) {
		DrawBox(350 + SidePosition * 100, 595, 420 + SidePosition * 100, 665, 0xff0000, FALSE); // �F�𖄂߂�ꏊ���ǂ��ɂ��邩��������{�b�N�X
		DrawBox(80 + Turns * 130, 210 + WarpPosition * 80, 160 + Turns * 130, 290 + WarpPosition * 80, 0x00ff00, FALSE); // �ǂ��̏ꏊ�𖄂߂悤�Ƃ��Ă��邩�\��
	}
	
	//DrawFormatString(100, 600, 0xffffff, "Turns��%d", Hit); // �f�o�b�N�p
	//DrawFormatString(100, 700, 0xffffff, "Turns��%d", Reasoning[WarpPosition]); // �f�o�b�N�p
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
		if (FirstMoveFlg == TRUE) {
			if (i % 2 == 0) {
				DrawFormatString(90 + (i / 2) * 260, 50, 0xff0000, "P"); // �v���C���[�̏��Ԃ���ɕ\��
			}
			else {
				DrawFormatString(220 + (i / 2) * 260, 50, 0x0000ff, "E"); // �G�l�~�[�̏��Ԃ���ɕ\��
			}
		}
		else if (i % 2 == 0) {
			DrawFormatString(90 + (i / 2) * 260, 50, 0x0000ff, "E"); // �G�l�~�[�̏��Ԃ���ɕ\��
		}
		else {
			DrawFormatString(220 + (i / 2) * 260, 50, 0xff0000, "P"); // �v���C���[�̏��Ԃ���ɕ\��
		}

	}
}

void HitAndBlow::RandomDecision()
{
	/* �����̔z��������_���ɐݒ肷�� */
	srand((unsigned int)time(NULL));

	if (DecisionFlg == TRUE) {
		for (int i = 0; i < 4; i++) {
			Answer[i] = rand() % 6;
			if (Answer[i] == Answer[(i + 1) % 4] || Answer[i] == Answer[(i + 2) % 4] || Answer[i] == Answer[(i + 3) % 4]) { // �F���d�Ȃ�����
				i--; // �I�ʂ���蒼��
			}
		}
		DecisionFlg = FALSE;
	}
	/* ��U�E��U�������_���Ɍ��߂� */
	if (TurnFlg == TRUE) {
		MoveFlg = rand() % 2;
		TurnFlg = FALSE;
		FirstMoveFlg = MoveFlg; // ��U����U�����o���Ă��炤�i�`�揈���ŕK�v�j
	}
	
}

void HitAndBlow::ERandomChoice()
{
	/* �����̔z��������_���ɐݒ肷�� */
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 4; i++) {
		//if (SaveHit[Turns - 1] + SaveBlow[Turns - 1] == 4 /*|| SaveHit[Turns - 2] + SaveBlow[Turns - 2]*/) {// �q�b�g�ƃu���[�̍��v�̐����S�ɂȂ�����
		//	ChangeColor = rand() % 4;
		//	Reasoning[i] = SaveReasoning[Turns][ChangeColor]; // �ꏊ�����ς���
		//	if (Reasoning[i] == Reasoning[(i + 1) % 4] || Reasoning[i] == Reasoning[(i + 2) % 4] || Reasoning[i] == Reasoning[(i + 3) % 4]) { // ���Ԕ���Ă���
		//		i--; // i�̒��I��蒼��
		//	}
		//}
		/*else */{
			Reasoning[i] = rand() % 6;
			if (Reasoning[i] == Reasoning[(i + 1) % 4] || Reasoning[i] == Reasoning[(i + 2) % 4] || Reasoning[i] == Reasoning[(i + 3) % 4]) { // �F���d�Ȃ�����
				i--; // �I�ʂ���蒼��
			}
			// 1�^�[���ڂɓ�����̂�j�~
			if (Turns / 2 == 0 && Reasoning[0] == Answer[0] && Reasoning[1] == Answer[1] && Reasoning[2] == Answer[2] && Reasoning[3] == Answer[3]) {
				i = 0;
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

//void HitAndBlow::FirstMove() 
//{
//	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START)) { // ���ɂ��鏈��
//		MoveFlg = TRUE;
//	}
//	else if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y)) { // ��U�ɂ��鏈��
//		MoveFlg = FALSE;
//	}
//}

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