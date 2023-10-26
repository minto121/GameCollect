#include"Hit&Blow.h"
#include"DxLib.h"
#include"PadInput.h"
#include<stdlib.h>
#include<time.h>

HitAndBlow::HitAndBlow() 
{
	// �_�~�[�摜��Ǎ�
	/*LoadGraph("../images/HitAndBlow/BG_Dummy.png");*/
	// �q�b�g�������̉摜�Ǎ�
	HitImg = LoadGraph("../images/HitAndBlow/HitPin.png");
	// �u���[�������̉摜�Ǎ�
	BlowImg = LoadGraph("../images/HitAndBlow/BlowPin.png");
	// �F�̉摜�ǉ�(���\��)
	ColorImg[0] = LoadGraph("../images/HitAndBlow/Blue_Foal.png");
	ColorImg[1] = LoadGraph("../images/HitAndBlow/Red_Foal.png");
	ColorImg[2] = LoadGraph("../images/HitAndBlow/Green_Foal.png");
	ColorImg[3] = LoadGraph("../images/HitAndBlow/Yellow_Foal.png");
	ColorImg[4] = LoadGraph("../images/HitAndBlow/Purple_Foal.png");
	ColorImg[5] = LoadGraph("../images/HitAndBlow/White_Foal.png");

	DecisionFlg = TRUE;

	WarpPosition = 1;
	SidePosition = 0;

	Turns = 0;
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
		if (WarpPosition > 4) WarpPosition = 4;
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
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_X))
	{
		Turns++;
		if (Turns > 8) {
			Turns = 8;
		}
	}

	// �f�o�b�N�p
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y))
	{
		Turns--;
		if (Turns < 0) {
			Turns = 0;
		}
	}
		
	/* �����Ɏ�����������鏈�������� */
	/* �d�����ă^�X�N�̉������Ȃ��Ȃ邽�߁A�R�����g�A�E�g�� */
	if (Turns < 8)
	{
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A && WarpPosition == 0))
		{
			/* �W���b�W���������� */
			Turns++;
		}
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_A && WarpPosition != 0))
		{
			Reasoning[WarpPosition] = Color[SidePosition];  // �F���ꏊ�ɔz�u
		}

	}
	else {
		/* �������o�������ǉ� */
	}
		
	return this;
}

void HitAndBlow::Draw() const
{
	for (int i = 0; i < 6; i++) { // ���\��
		DrawGraph(350 + i * 100, 600, ColorImg[i], TRUE); // ���ꂼ��̐F�̋��\��(�ʒu�͌���)
	}
	DrawGraph(200, 100, HitImg, TRUE); // ���ꂼ��̐F�̋��\��
	DrawGraph(300, 100, BlowImg, TRUE); // ���ꂼ��̐F�̋��\��
	
	DrawTriangle(300 + SidePosition * 100, 575, 350 + SidePosition * 100, 625, 300 + SidePosition * 100, 675, 0xff0000, TRUE); // �ǂ��̋���w���Ă���̂��\��
	DrawBox(200 + Turns * 75, 100 + WarpPosition * 100, 275 + Turns * 75, 175 + WarpPosition * 100, 0x00ff00, FALSE); // �ǂ��̏ꏊ�𖄂߂悤�Ƃ��Ă��邩�\��

	DrawFormatString(100, 600, 0xffffff, "Turns��%d", Turns); // �f�o�b�N�p
	
	/* �����̋�\�� */
	/* �d�����ă^�X�N�̉������Ȃ��Ȃ邽�߁A�R�����g�A�E�g�� */
	if (DecisionFlg == FALSE) {
		for (int i = 0; i < 4; i++) {
			DrawFormatString(400, 400 + i * 20, 0xffffff, "%d", Answer[i]); // �f�o�b�N�p
			DrawGraph(1100, 170 + i * 75, ColorImg[Answer[i]], TRUE); // �������摜�ŕ\��
			DrawFormatString(100, 700, 0xffffff, "Turns��%d",Reasoning[WarpPosition]); // �f�o�b�N�p
			//DrawGraph(100 * Turns, 170 + i * 75, ColorImg[Reasoning[WarpPosition]], TRUE); // �\�z���摜�ŕ\��
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
			if (Answer[i] == Answer[(i + 1) % 4] || Answer[i] == Answer[(i + 2) % 4] || Answer[i] == Answer[(i + 3) % 4]) {
				i--;
			}
		}
		DecisionFlg = FALSE;
	}

}