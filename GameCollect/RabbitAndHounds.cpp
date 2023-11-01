#include"RabbitAndHounds.h"
#include "DxLib.h"
#include "PadInput.h"

static int MenuNumber = 0;
int Cursor_X = 0;

RabbitAndHounds::RabbitAndHounds()
{
	BackGroundImg = LoadGraph("images/RabbitAndHounds/BackGround01.png");
	//3D���f���̓Ǎ�
	HoundImg = MV1LoadModel("Dog_Model.mv1");
	RabbitImg = MV1LoadModel("Rabbit_Model.mv1");

	
}

RabbitAndHounds::~RabbitAndHounds()
{
	//// ���f���n���h���̍폜
	//MV1DeleteModel(HoundImg);
	//MV1DeleteModel(RabbitImg);
}

AbstractScene* RabbitAndHounds::Update()
{
	//�\���L�[������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
	
	}
	//�\���L�[������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT))
	{

	}

	return this;
}

void RabbitAndHounds::Draw() const
{
	DrawGraph(0, 0, BackGroundImg, TRUE);

	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -1000), VGet(0, 0, 0));

	// ��ʂɉf��ʒu�ɂR�c���f�����ړ�
	MV1SetPosition(HoundImg, VGet(320.0f, -300.0f, 600.0f));
	MV1SetPosition(RabbitImg, VGet(320.0f, -300.0f, 600.0f));

	//3D���f���̕`��
	MV1DrawModel(HoundImg);
	MV1DrawModel(RabbitImg);

	DrawString(10, 20, "�E�T�M�Ɨ�", 0xffffff);
	// �`�悷�镶����̃T�C�Y��ݒ�
	/*SetFontSize(50);
	DrawString(300, 350, "�E�T�M", 0xffffff);
	DrawString(800, 350, "��", 0xffffff);*/

	//�J�[�\���`��
	/*Cursor_X = MenuNumber * 60;
	DrawTriangle(260, 360 + Cursor_X, 290, 380 + Cursor_X, 260, 400 + Cursor_X, GetColor(255, 0, 0), TRUE);*/
}
