#include"Hit&Blow.h"
#include"DxLib.h"

HitAndBlow::HitAndBlow() 
{
	// �_�~�[�摜��Ǎ�
	LoadGraph("../images/HitAndBlow/BG_Dummy.png");
	// �q�b�g�������̉摜�Ǎ�
	HitImg=LoadGraph("../images/HitAndBlow/�q�b�g�s��1.png");
	// �u���[�������̉摜�Ǎ�
	BlowImg=LoadGraph("../images/HitAndBlow/�u���[�s��.png");
	// �F�̉摜�ǉ�(���\��)
	Color[0] = LoadGraph("../images/HitAndBlow/�F�̋�1.png");
	Color[1] = LoadGraph("../images/HitAndBlow/�ԐF�̋�1.png");
	Color[2] = LoadGraph("../images/HitAndBlow/�ΐF�̋�1.png");
	Color[3] = LoadGraph("../images/HitAndBlow/���F�̋�1.png");
	Color[4] = LoadGraph("../images/HitAndBlow/���F�̋�1.png");
	Color[5] = LoadGraph("../images/HitAndBlow/���F�̋�.png");
}

HitAndBlow::~HitAndBlow()
{
	
}

AbstractScene* HitAndBlow::Update()
{
	return this;
}

void HitAndBlow::Draw() const
{
	for (int i = 0; i < 6; i++) {
		DrawGraph(200 + i * 75, 200, Color[i], TRUE); // ���ꂼ��̐F�̋��\��
	}
}