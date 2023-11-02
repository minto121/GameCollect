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

	for (int i = 0; i < 4; i++) {
		Reasoning[i] = -1;// �G���[�����p�̃R���X�g���N�g
	}

	SaveColor = 0; // �Z�[�u�J���[������

	Hit = 0;  // �q�b�g�̐���������
	Blow = 0;  // �u���[�̐���������
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
		if (WarpPosition < 0) WarpPosition = 0; // �ʒu��0�����Ȃ�A0�ɂ���
	}

	// �\���L�[������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		WarpPosition++;
		if (WarpPosition > 3) WarpPosition = 3; // �ʒu��3�𒴂�����A3�ɂ���
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
			Judgment();

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
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
		{
			ColorDecision = WarpPosition; // ���ꂽ���c�̈ʒu��ۑ�
			Reasoning[ColorDecision] = SidePosition;  // �F���ꏊ�ɔz�u
			WarpPosition++;
			if (WarpPosition > 3) WarpPosition = 3; // �ʒu��3�𒴂�����A3�ɂ���
		}
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
	DrawTriangle(300 + SidePosition * 100, 575, 350 + SidePosition * 100, 625, 300 + SidePosition * 100, 675, 0xff0000, TRUE); // �ǂ��̋���w���Ă���̂��\��
	DrawBox(200 + Turns * 70, 100 + WarpPosition * 100, 280 + Turns * 70, 180 + WarpPosition * 100, 0x00ff00, FALSE); // �ǂ��̏ꏊ�𖄂߂悤�Ƃ��Ă��邩�\��

	//DrawFormatString(100, 600, 0xffffff, "Turns��%d", Turns); // �f�o�b�N�p

	/* �����̋�\�� */
	if (DecisionFlg == FALSE) { // ���������܂��Ă��āA8�^�[���o�߂��A4�q�b�g������\��
		for (int i = 0; i < 4; i++) {
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
			if (SaveReasoning[i][0] >= 0) {
				DrawGraph(215 + i * 70, 115, ColorImg[SaveReasoning[i][0]], TRUE);
			}
			if (SaveReasoning[i][1] >= 0) {
				DrawGraph(215 + i * 70, 115 + 1 * 100, ColorImg[SaveReasoning[i][1]], TRUE);
			}
			if (SaveReasoning[i][2] >= 0) {
				DrawGraph(215 + i * 70, 115 + 2 * 100, ColorImg[SaveReasoning[i][2]], TRUE);
			}
			if (SaveReasoning[i][3] >= 0) {
				DrawGraph(215 + i * 70, 115 + 3 * 100, ColorImg[SaveReasoning[i][3]], TRUE);
			}
			/* �W���b�W�p�̕`�揈�������� */
			for (int j = 0; j < SaveHit[i]; j++) {
				DrawGraph(215 + (j % 2) * 40 + i * 80, 50 + (j / 2) * 40, HitImg, TRUE);
			}
			for (int k = 0; k < SaveBlow[i]; k++) {
				DrawGraph(215 + ((SaveHit[i] + k) % 2) * 40 + i * 80, 50 + ((SaveHit[i] + k) / 2) * 40, BlowImg, TRUE);
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

void HitAndBlow::Judgment()
{
	for (int i = 0; i < 4; i++) {
		if (Reasoning[i] == Answer[i]) {
			Hit++; // hit�ɂP�𑫂�
		}
		else if (Reasoning[i] == Answer[(i + 1) % 4] || Reasoning[i] == Answer[(i + 2) % 4] || Reasoning[i] == Answer[(i + 3) % 4]) {
			Blow++; // blow�ɂP�𑫂�
		}
	}
	SaveHit[Turns] = Hit;
	SaveBlow[Turns] = Blow;
}