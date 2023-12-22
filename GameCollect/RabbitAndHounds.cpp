#include"RabbitAndHounds.h"
#include "Rabbit.h"
#include "Hound.h"
#include "DxLib.h"
#include "PadInput.h"
#include<iostream>

static int MenuNumber = 0;
int Cursor_X = 0;

RabbitAndHounds::RabbitAndHounds()
{
	BackGroundImg = LoadGraph("images/RabbitAndHounds/BackGround01.png");
	//3D���f���̓Ǎ�
	//HoundImg = MV1LoadModel("Dog_Model.mv1");
	//RabbitImg = MV1LoadModel("Rabbit_Model.mv1");

	////�E�T�M���W
	//rabbit_X = 100, rabbit_Y = 100;
	//rabbitSpeed = 2;

	////�����W
	//hound_X = 400, hound_Y = 400;
	//houndSpeed = 1;

	Cursor_X = 0;

	Player = 0;
}

RabbitAndHounds::~RabbitAndHounds()
{
	// ���f���n���h���̍폜
	/*MV1DeleteModel(HoundImg);
	MV1DeleteModel(RabbitImg);*/
}

AbstractScene* RabbitAndHounds::Update()
{
	//�\���L�[�E 
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		Cursor_X = 480;
		Player = 1;
	}
	//�\���L�[��
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		Cursor_X = -10;
		Player = 2;
	}
	
	//A�{�^���������ăv���C���[�̑��삷�����I��
	if (Cursor_X <= 300 && PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true))
	{
		return new Rabbit();
	}
	else if (Cursor_X >= 300 && PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true))
	{
		return new Hound();
	}
		return this;
}

void RabbitAndHounds::Draw() const
{
	//�^�C�g��
	DrawString(10, 20, "�E�T�M�Ɨ�", 0xffffff);
	//�w�i�摜
	DrawGraph(0, 0, BackGroundImg, TRUE);

	// �`�悷�镶����̃T�C�Y��ݒ�
	SetFontSize(50);
	DrawString(300, 350, "�E�T�M", 0xffffff);
	DrawString(800, 350, "��", 0xffffff);

	//�J�[�\���`��
	DrawTriangle(260 + Cursor_X, 360, 290 + Cursor_X, 380, 260 + Cursor_X, 400, GetColor(255, 0, 0), TRUE);

	//�v���C���[���쌈��
	if (Player != 1) {
		DrawString(100, 100, "�v���C���[�̓E�T�M", 0xffffff);
	}
	else
	{
		DrawString(600, 100, "�v���C���[�͗�", 0xffffff);
	}

}
