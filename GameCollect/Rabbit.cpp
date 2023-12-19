#include"RabbitAndHounds.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Rabbit.h"

Rabbit::Rabbit()
{
	BackGroundImg = LoadGraph("images/RabbitAndHounds/RabbitAndHoundsBoard.png");
	cursorImg = LoadGraph("images/RabbitAndHounds/cursor.png");

	//3D���f���̓Ǎ�
	/*HoundImg = MV1LoadModel("Dog_Model.mv1");
	RabbitImg = MV1LoadModel("Rabbit_Model.mv1");*/

	RabbitImg[2] = LoadGraph("../images/RabbitAndHounds/Rabbit.png");
	if (LoadDivGraph("images/RabbitAndHounds/Rabbit.png", 2, 2, 1, 32, 64, RabbitImg));
	RabbitImg[2] = rabbitimg;

	// �e�N�X�`���̓ǂݍ���
	//R_texture = LoadGraph("images/RabbitAndHounds/Textures/Coloe_Textures/T_PigHead_00.TGA");

	rabbit_X = 0;
	rabbit_Y = 0;


	//�X�e�[�W������
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 3; j++) {
			if (i == 0 && j == 0) {
				bord[i][j].flg = -1; //����Ȃ��t���O
				bord[i][j].x = 150;  //����
				bord[i][j].y = 100; 
			}
			else if (i == 4 && j == 0) {
				bord[i][j].flg = -1; //����Ȃ��t���O
				bord[i][j].x = 1080;  //�E��
				bord[i][j].y = 100;
			}
			else if (i == 0 && j == 2) {
				bord[i][j].flg = -1; //����Ȃ��t���O
				bord[i][j].x = 150;  //����
				bord[i][j].y = 575;
			}
			else if (i == 4 && j == 2) {
				bord[i][j].flg = -1;  //����Ȃ��t���O
				bord[i][j].x = 1080;  //�E��
				bord[i][j].y = 575;
			}
			else if (i == 1 && j == 0) {
				bord[i][j].flg = 2;  //�����t���O
				bord[i][j].x = 390;  //��i�@��
				bord[i][j].y = 95;
			}
			else if (i == 2 && j == 0) {
				bord[i][j].flg = 3;  //�����t���O
				bord[i][j].x = 625;  //��i�@�^��
				bord[i][j].y = 95;
			}
			else if (i == 3 && j == 0) {
				bord[i][j].flg = 4;  //�����t���O
				bord[i][j].x = 860;  //��i�@�E
				bord[i][j].y = 95;
			}
			else if (i == 0 && j == 1) {
				bord[i][j].flg = 6;  //�����t���O
				bord[i][j].x = 150;  //���i�@���[
				bord[i][j].y = 335;
			}
			else if (i == 1 && j == 1) {
				bord[i][j].flg = 7;  //�����t���O
				bord[i][j].x = 390;  //���i�@��
				bord[i][j].y = 335;
			}
			else if (i == 2 && j == 1) {
				bord[i][j].flg = 8;  //�����t���O
				bord[i][j].x = 625;  //���i�@�^��
				bord[i][j].y = 335;
			}
			else if (i == 3 && j == 1) {
				bord[i][j].flg = 9;  //�����t���O
				bord[i][j].x = 865;  //���i�@�E
				bord[i][j].y = 335;
			}
			else if (i == 4 && j == 1) {
				bord[i][j].flg = 10; //�����t���O
				bord[i][j].x = 1080;  //���i�@�E�[
				bord[i][j].y = 335;
			}
			else if (i == 1 && j == 2) {
				bord[i][j].flg = 12; //�����t���O
				bord[i][j].x = 390;  //���i�@��
				bord[i][j].y = 575;
			}
			else if (i == 2 && j == 2) {
				bord[i][j].flg = 13; //�����t���O
				bord[i][j].x = 625;  //���i�@�^��
				bord[i][j].y = 575;
			}
			else if (i == 3 && j == 2) {
				bord[i][j].flg = 14; //�����t���O
				bord[i][j].x = 860;  //���i�@�E
				bord[i][j].y = 575;
			}
		}	
	}
}

Rabbit::~Rabbit()
{
	// ���f���n���h���̍폜
	/*MV1DeleteModel(HoundImg);
	MV1DeleteModel(RabbitImg);*/
}

AbstractScene* Rabbit::Update()
{	
	// �E�T�M���ړ�
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
		rabbit_Y -= 230;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
		rabbit_Y += 230;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		rabbit_X -= 250;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		rabbit_X += 250;
	}

	// �E�T�M���ړ�
	/*if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
		rabbit_Y = bord[5][3].flg;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
		rabbit_Y = bord[5][3].flg;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		rabbit_X = bord[5][3].flg;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		rabbit_X = bord[5][3].flg;
	}*/
	
	//��ʂ���o�Ȃ��悤�ɂ���
	if (rabbit_X < 100 || rabbit_X > 1100 || rabbit_Y < -300 || rabbit_Y > 400)
	{
		rabbit_X = 0;
		rabbit_Y = 0;
	}

	//switch (bord[5][3].flg)
	//{
	//	case 0:
	//		if (bord[5][3].flg = 0)
	//		{
	//			return 0;
	//		};
	//		break;
	//	/*case 1:
	//		if (bord[5][3].flg = -1)
	//		{
	//			return -1;
	//		};*/
	//		break;
	//	default:
	//		break;
	//}

	return this;
}

void Rabbit::Draw() const
{
	//�w�i�摜
	DrawGraph(0, 0, BackGroundImg, TRUE);

	//�^�C�g��
	DrawString(10, 20, "�v���C���[����̓E�T�M", 0x000000);

	/*SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -1000), VGet(0, 0, 0));*/

	// ��ʂɉf��ʒu�ɂR�c���f�����ړ�
	//MV1SetPosition(RabbitImg, VGet(320.0f, -300.0f, 600.0f));
	//MV1SetScale(RabbitImg, VGet(1, 1, 1)); // ���f���̃X�P�[����ݒ�
	//MV1SetRotationXYZ(RabbitImg, VGet(0, 0, 0)); // ���f���̉�]��ݒ�

	// �e�N�X�`���̐ݒ�
	/*SetUseTextureToShader(0, R_texture);*/

	//MV1SetPosition(HoundImg, VGet(320.0f, -300.0f, 600.0f));

	//3D���f���̕`��
	/*MV1DrawModel(RabbitImg);
	MV1DrawModel(HoundImg);*/

	//�E�T�M�Ɨ���`��
	/*DrawBox(200 + rabbit_X, 250 + rabbit_Y, 300 + rabbit_X - 1, 350 + rabbit_Y - 1, GetColor(0, 0, 255), RabbitImg);
	DrawCircle(hound_X, hound_Y, hound_X - 1, hound_Y - 1, GetColor(0, 0, 255), HoundImg);*/

	//���̋�(��)
	DrawBox(890, 140, 960, 210, 0x0000ff, TRUE);     //��
	DrawBox(1100, 350, 1150, 400, 0x0000ff, TRUE);   //�^��
	DrawBox(900, 550, 950, 600, 0x0000ff, TRUE);     //��
	
	//�J�[�\��
	//DrawGraph(-10 + rabbit_X, 250 + rabbit_Y, cursorImg, TRUE);

	//�E�T�M�̋�(��)
	DrawBox(150 + rabbit_X, 340 + rabbit_Y, 200 + rabbit_X, 390 + rabbit_Y, 0xff0000, RabbitImg[2]);
	DrawGraph(100, 250, rabbitimg, TRUE);

	/*if (bord[i][j].flg == 0) {
		DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x000000, TRUE);
	}
	else if (bord[i][j].flg == 1) {
		DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
	}*/

	//�{�[�h
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			if (bord[i][j].flg == -1) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x000000, TRUE);
			}
			else if (bord[i][j].flg == 2) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
			else if (bord[i][j].flg == 3) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
			else if (bord[i][j].flg == 4) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
			else if (bord[i][j].flg == 6) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
			else if (bord[i][j].flg == 7) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
			else if (bord[i][j].flg == 8) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
			else if (bord[i][j].flg == 9) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
			else if (bord[i][j].flg == 10) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
			else if (bord[i][j].flg == 12) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
			else if (bord[i][j].flg ==13) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
			else if (bord[i][j].flg == 14) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
		}
	}

	DrawBox(bord[5][3].x, bord[5][3].y, 200 + bord[5][3].x, 390 + bord[5][3].y, 0xff0000, RabbitImg[2]);
}