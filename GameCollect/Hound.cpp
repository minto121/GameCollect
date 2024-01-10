#include"RabbitAndHounds.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Hound.h"

Hound::Hound()
{
	BackGroundImg = LoadGraph("images/RabbitAndHounds/BackGround02.png");

	//3D���f���̓Ǎ�
	HoundImg = MV1LoadModel("Dog_Model.mv1");
	RabbitImg = MV1LoadModel("Rabbit_Model.mv1");

	// �e�N�X�`���̓ǂݍ���
	R_texture = LoadGraph("images/RabbitAndHounds/Textures/Coloe_Textures/T_PigHead_00.TGA");

	hound_X = 0;
	hound_Y = 0;

}

Hound::~Hound()
{
	// ���f���n���h���̍폜
	/*MV1DeleteModel(HoundImg);
	MV1DeleteModel(RabbitImg);*/
}

AbstractScene* Hound::Update()
{

	////�E�T�M���W
	//rabbit_X = 100, rabbit_Y = 100;

	//if (PAD_INPUT::OnButton(KEY_INPUT_RIGHT) == true)
	//{
	//	rabbit_X = 200;
	//}

	// �����ړ�
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
		hound_Y -= 200;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
		hound_Y += 200;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		hound_X -= 200;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		hound_X += 200;
	}

	return this;
}

void Hound::Draw() const
{
	//�w�i�摜
	DrawGraph(0, 0, BackGroundImg, TRUE);

	//�^�C�g��
	DrawString(10, 20, "�v���C���[����͗�", 0x000000);

	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -1000), VGet(0, 0, 0));

	// ��ʂɉf��ʒu�ɂR�c���f�����ړ�
	MV1SetPosition(RabbitImg, VGet(320.0f, -300.0f, 600.0f));
	MV1SetScale(RabbitImg, VGet(1, 1, 1)); // ���f���̃X�P�[����ݒ�
	MV1SetRotationXYZ(RabbitImg, VGet(0, 0, 0)); // ���f���̉�]��ݒ�

	// �e�N�X�`���̐ݒ�
	SetUseTextureToShader(0, R_texture);

	//MV1SetPosition(HoundImg, VGet(320.0f, -300.0f, 600.0f));

	//3D���f���̕`��
	MV1DrawModel(RabbitImg);
	MV1DrawModel(HoundImg);

	//�E�T�M�Ɨ���`��
	/*DrawBox(200 + rabbit_X, 250 + rabbit_Y, 300 + rabbit_X - 1, 350 + rabbit_Y - 1, GetColor(0, 0, 255), RabbitImg);
	DrawCircle(hound_X, hound_Y, hound_X - 1, hound_Y - 1, GetColor(0, 0, 255), HoundImg);*/


	DrawCircle(325, 375, 50, 0x00ff00, TRUE);


	//���̋�(��)
	DrawBox(890, 140, 960, 210, 0x0000ff, TRUE);     //��
	DrawBox(1100, 350, 1150, 400, 0x0000ff, TRUE);   //�^��
	DrawBox(900, 550, 950, 600, 0x0000ff, TRUE);     //��

	//�E�T�M�̋�(��)
	DrawBox(100 + hound_X, 350 + hound_Y, 150 + hound_X, 400 + hound_Y, 0xff0000, HoundImg);
}