#include"Hit&Blow.h"
#include"DxLib.h"
#include<stdlib.h>
#include<time.h>

HitAndBlow::HitAndBlow() 
{
	// �_�~�[�摜��Ǎ�
	/*LoadGraph("../images/HitAndBlow/BG_Dummy.png");*/
	// �q�b�g�������̉摜�Ǎ�
	HitImg = LoadGraph("../images/HitAndBlow/�q�b�g�s��.png");
	// �u���[�������̉摜�Ǎ�
	BlowImg = LoadGraph("../images/HitAndBlow/�u���[�s��.png");
	// �F�̉摜�ǉ�(���\��)
	ColorImg[0] = LoadGraph("../images/HitAndBlow/�F�̋�.png");
	ColorImg[1] = LoadGraph("../images/HitAndBlow/�ԐF�̋�.png");
	ColorImg[2] = LoadGraph("../images/HitAndBlow/�ΐF�̋�.png");
	ColorImg[3] = LoadGraph("../images/HitAndBlow/���F�̋�.png");
	ColorImg[4] = LoadGraph("../images/HitAndBlow/���F�̋�.png");
	ColorImg[5] = LoadGraph("../images/HitAndBlow/���F�̋�.png");
}

HitAndBlow::~HitAndBlow()
{
	
}

AbstractScene* HitAndBlow::Update()
{
	/* �����̔z��������_���ɐݒ肷�� */
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 4; i++) {
		Answer[i] = rand() % 6;
		if (Answer[i] == Answer[(i + 1) % 4] || Answer[i] == Answer[(i + 2) % 4] || Answer[i] == Answer[(i + 3) % 4]) {
			i--;
		}
	}
	return this;
}

void HitAndBlow::Draw() const
{
	for (int i = 0; i < 6; i++) { // ���\��
		DrawGraph(350 + i * 100, 600, ColorImg[i], TRUE); // ���ꂼ��̐F�̋��\��(�ʒu�͌���)
	}
	DrawGraph(200, 200, HitImg, TRUE); // ���ꂼ��̐F�̋��\��
	DrawGraph(200, 250, BlowImg, TRUE); // ���ꂼ��̐F�̋��\��

	for (int i = 0; i < 4; i++) {
		DrawFormatString(400, 400 + i * 20, 0xffffff, "%d", Answer[i]);
	}
	
}