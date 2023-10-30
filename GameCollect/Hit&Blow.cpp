#include"Hit&Blow.h"
#include"DxLib.h"
#include"PadInput.h"
#include<stdlib.h>
#include<time.h>

HitAndBlow::HitAndBlow() 
{
	// �q�b�g�������̉摜�Ǎ�
	HitImg = LoadGraph("../images/HitAndBlow/HitPin.png");
	// �u���[�������̉摜�Ǎ�
	BlowImg = LoadGraph("../images/HitAndBlow/BlowPin.png");

	LoadDivGraph("../images/HitAndBlow/ColorBall.png", 6, 6, 1, 64, 64, ColorImg);
	
	DecisionFlg = TRUE;

	WarpPosition = 0;
	SidePosition = 0;

	Turns = 0;

	ColorFlg = FALSE;

	for (int i = 0; i++; i < 4) {
		Reasoning[i] = 0;
	}
	Reasoning[0] = -1; // �G���[�����p�̃R���X�g���N�g
	Reasoning[1] = -1; // �G���[�����p�̃R���X�g���N�g
	Reasoning[2] = -1; // �G���[�����p�̃R���X�g���N�g
	Reasoning[3] = -1; // �G���[�����p�̃R���X�g���N�g

	SaveColor = 0; // �Z�[�u�J���[������
}

HitAndBlow::~HitAndBlow()
{
	
}

AbstractScene* HitAndBlow::Update()
{
	RandomDecision(); // �����̔z��������_���ɐݒ肷��

	//�\���L�[������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
	{
		WarpPosition--;
		if (WarpPosition < 0) WarpPosition = 0;  // �ʒu��0��艺�Ȃ�A0�ɂ���
	}

	// �\���L�[������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		WarpPosition++;
		if (WarpPosition > 3) WarpPosition = 3;
	}

	// �\���L�[������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		Color[SidePosition--];
		if (SidePosition < 0) SidePosition = 5;
	}

	//�\���L�[������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		Color[SidePosition++];
		if (SidePosition > 5) SidePosition = 0;
	}

	// �f�o�b�N�p
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER))
	{
		Turns++;
		if (Turns > 7) {
			Turns = 7;
		}
	}

	// �f�o�b�N�p
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_LEFT_SHOULDER))
	{
		Turns--;
		if (Turns < 0) {
			Turns = 0;
		}
	}
	
	
	/* �����Ɏ�����������鏈�������� */
	if (Turns < 8)
	{
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_X) && Reasoning[0] != -1 && Reasoning[1] != -1 && Reasoning[2] != -1 && Reasoning[3] != -1) // �F�������Ă��鎞
		{
			/* �W���b�W���������� */
			
			//SaveColor = Turns; // �O�̃^�[���̐F�Ə��Ԃ��Z�[�u����
			 /* �F�̃f�[�^�����p�� */ 
			SaveReasoning[SaveColor][0] = Reasoning[0];
			SaveReasoning[SaveColor][1] = Reasoning[1];
			SaveReasoning[SaveColor][2] = Reasoning[2];
			SaveReasoning[SaveColor][3] = Reasoning[3];

			SaveColor++; // �`���1�ǉ�
			Turns++; // �^�[����1����
			
			Reasoning[0] = -1; // �F�����Z�b�g
			Reasoning[1] = -1; // �F�����Z�b�g
			Reasoning[2] = -1; // �F�����Z�b�g
			Reasoning[3] = -1; // �F�����Z�b�g

		}
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
		{
			ColorDecision = WarpPosition; // ���ꂽ���c�̈ʒu��ۑ�
			Reasoning[ColorDecision] = SidePosition;  // �F���ꏊ�ɔz�u
			ColorFlg = TRUE; // �F����ꂽ���m�F����t���O��^�Ƃ���
		}
		/* ���̏����͗v��Ȃ���������Ȃ��̂ŁA���Ƃŏ��� */
		//else if (Reasoning[WarpPosition] != SidePosition) {
		//	ColorFlg = FALSE;
		//}

	}
	else {
		/* �������o�������ǉ� */
	}
		
	return this;
}

void HitAndBlow::Draw() const
{
	for (int i = 0; i < 7; i++) { // ���\��
		DrawGraph(350 + i * 100, 600, ColorImg[i], TRUE); // ���ꂼ��̐F�̋��\��(�ʒu�͌���)
	}
	DrawGraph(200, 100, HitImg, TRUE); // HitPin��\��
	DrawGraph(300, 100, BlowImg, TRUE); //BlowPin��\��
	
	DrawTriangle(300 + SidePosition * 100, 575, 350 + SidePosition * 100, 625, 300 + SidePosition * 100, 675, 0xff0000, TRUE); // �ǂ��̋���w���Ă���̂��\��
	DrawBox(200 + Turns * 70, 100 + WarpPosition * 100, 280 + Turns * 70, 180 + WarpPosition * 100, 0x00ff00, FALSE); // �ǂ��̏ꏊ�𖄂߂悤�Ƃ��Ă��邩�\��

	DrawFormatString(100, 600, 0xffffff, "Turns��%d", Turns); // �f�o�b�N�p
	
	/* �����̋�\�� */
	/* �d�����ă^�X�N�̉������Ȃ��Ȃ邽�߁A�R�����g�A�E�g�� */
	if (DecisionFlg == FALSE) {
		for (int i = 0; i < 4; i++) {
			//DrawFormatString(400, 400 + i * 20, 0xffffff, "%d", Answer[i]); // �f�o�b�N�p
			DrawGraph(1100, 170 + i * 75, ColorImg[Answer[i]], TRUE); // �������摜�ŕ\��
		}
		//DrawFormatString(100, 700, 0xffffff, "Turns��%d", Reasoning[WarpPosition]); // �f�o�b�N�p
		/* �\�z�����J���[��\������ */
		if (ColorFlg == TRUE || Reasoning[WarpPosition % 4] >= 0) {
			DrawGraph(215 + Turns * 70, 115 + WarpPosition * 100, ColorImg[Reasoning[WarpPosition % 4]], TRUE); // �\�z���摜�ŕ\��
		}
		if (ColorFlg == TRUE || Reasoning[(WarpPosition + 1) % 4] >= 0) {
			DrawGraph(215 + Turns * 70, 115 + (WarpPosition + 1) % 4 * 100, ColorImg[Reasoning[(WarpPosition + 1) % 4]], TRUE); // �\�z���摜�ŕ\��
		}
		if (ColorFlg == TRUE || Reasoning[(WarpPosition + 2) % 4] >= 0) {
			DrawGraph(215 + Turns * 70, 115 + (WarpPosition + 2) % 4 * 100, ColorImg[Reasoning[(WarpPosition + 2) % 4]], TRUE); // �\�z���摜�ŕ\��
		}
		if (ColorFlg == TRUE || Reasoning[(WarpPosition + 3) % 4] >= 0) {
			DrawGraph(215 + Turns * 70, 115 + (WarpPosition + 3) % 4 * 100, ColorImg[Reasoning[(WarpPosition + 3) % 4]], TRUE); // �\�z���摜�ŕ\��
		}
		/* �ߋ��ɓ��ꂽ�F��\�� */
		for (int i = 0; i < Turns; i++) {
			for (int j = 0; j < 4; j++) {
				if (SaveReasoning[i][0] >= 0) {
					DrawGraph(215 + i * 70, 115, ColorImg[SaveReasoning[i][0]], TRUE); // �\�z���摜�ŕ\��
				}
				if (SaveReasoning[i][1] >= 0) {
					DrawGraph(215 + i * 70, 115 + 1 * 100, ColorImg[SaveReasoning[i][1]], TRUE); // �\�z���摜�ŕ\��
				}
				if (SaveReasoning[i][2] >= 0) {
					DrawGraph(215 + i * 70, 115 + 2 * 100, ColorImg[SaveReasoning[i][2]], TRUE); // �\�z���摜�ŕ\��
				}
				if (SaveReasoning[i][3] >= 0) {
					DrawGraph(215 + i * 70, 115 + 3 * 100, ColorImg[SaveReasoning[i][3]], TRUE); // �\�z���摜�ŕ\��
				}
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
			Answer[i] = rand() % 6;
			if (Answer[i] == Answer[(i + 1) % 4] || Answer[i] == Answer[(i + 2) % 4] || Answer[i] == Answer[(i + 3) % 4]) { // �F���d�Ȃ�����
				i--; // �I�ʂ���蒼��
			}
		}
		DecisionFlg = FALSE;
	}

}