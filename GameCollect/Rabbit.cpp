#include"RabbitAndHounds.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Rabbit.h"

Rabbit::Rabbit()
{
	BackGroundImg = LoadGraph("images/RabbitAndHounds/BackGround02.png");

	//3D���f���̓Ǎ�
	HoundImg = MV1LoadModel("Dog_Model.mv1");
	RabbitImg = MV1LoadModel("Rabbit_Model.mv1");

	// �e�N�X�`���̓ǂݍ���
	R_texture = LoadGraph("images/RabbitAndHounds/Textures/Coloe_Textures/T_PigHead_00.TGA");
}

Rabbit::~Rabbit()
{
	// ���f���n���h���̍폜
	/*MV1DeleteModel(HoundImg);
	MV1DeleteModel(RabbitImg);*/
}

AbstractScene* Rabbit::Update()
{
	while (CheckHitKey(KEY_INPUT_A)) {
		// 3D�`��̊J�n
		//ClearDrawScreen();

		// ��ʂ̍X�V
		//
		ScreenFlip();
	}

	////�E�T�M���W
	//rabbit_X = 100, rabbit_Y = 100;

	//if (PAD_INPUT::OnButton(KEY_INPUT_RIGHT) == true)
	//{
	//	rabbit_X = 200;
	//}

	// �E�T�M���ړ�
	/*if (CheckHitKey(KEY_INPUT_UP)) {
		rabbit_Y -= rabbitSpeed;
	}
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		rabbit_Y += rabbitSpeed;
	}
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		rabbit_X -= rabbitSpeed;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		rabbit_X += rabbitSpeed;
	}*/
	

	return this;
}

void Rabbit::Draw() const
{
	//�w�i�摜
	DrawGraph(0, 0, BackGroundImg, TRUE);

	//�^�C�g��
	DrawString(10, 20, "�v���C���[����̓E�T�M", 0x000000);

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

	/*DrawBox(300, 350, 400, 450, GetColor(255, 0, 0), RabbitImg);
	DrawCircle(900, 400, 60, GetColor(0, 0, 255), TRUE);*/
}