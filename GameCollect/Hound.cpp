#include"RabbitAndHounds.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Hound.h"

Hound::Hound()
{
	BackGroundImg = LoadGraph("images/RabbitAndHounds/RabbitAndHoundsBoard.png");
	cursorImg = LoadGraph("images/RabbitAndHounds/cursor.png");

	//3D���f���̓Ǎ�
	HoundImg = MV1LoadModel("Dog_Model.mv1");
	RabbitImg = MV1LoadModel("Rabbit_Model.mv1");

	// �e�N�X�`���̓ǂݍ���
	R_texture = LoadGraph("images/RabbitAndHounds/Textures/Coloe_Textures/T_PigHead_00.TGA");

	RabbitFlg = 9;				//�E�T�M�t���O������
	RabbitDrawflg = TRUE;		//�E�T�M�`��t���O������
	RabbitMoveflg = 0;			//�E�T�M�ړ��t���O������

	HoundFlg1 = 5;		//���t���O������
	HoundFlg2 = 1;
	HoundFlg3 = 11;

	/*HoundFlg[1] = 5;
	HoundFlg[2] = 1;
	HoundFlg[3] = 11;*/

	HoundDrawflg1 = TRUE;	//���`��t���O������
	HoundDrawflg2 = TRUE;
	HoundDrawflg3 = TRUE;
	
	HoundMoveflg1 = 0;		//���ړ��t���O������
	HoundMoveflg2 = 0;
	HoundMoveflg3 = 0;

	cursorFlg = 5;			//�J�[�\���t���O������

	//�X�e�[�W������
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == 0 && j == 0) {
				bord[i][j].flg = 0; //����Ȃ��t���O
				bord[i][j].x = 150;  //����
				bord[i][j].y = 100;
			}
			else if (i == 4 && j == 0) {
				bord[i][j].flg = 4; //����Ȃ��t���O
				bord[i][j].x = 1080;  //�E��
				bord[i][j].y = 100;
			}
			else if (i == 0 && j == 2) {
				bord[i][j].flg = 10; //����Ȃ��t���O
				bord[i][j].x = 150;  //����
				bord[i][j].y = 575;
			}
			else if (i == 4 && j == 2) {
				bord[i][j].flg = 14;  //����Ȃ��t���O
				bord[i][j].x = 1080;  //�E��
				bord[i][j].y = 575;
			}
			else if (i == 1 && j == 0) {
				bord[i][j].flg = 1;  //�����t���O
				bord[i][j].x = 390;  //��i�@��
				bord[i][j].y = 95;
			}
			else if (i == 2 && j == 0) {
				bord[i][j].flg = 2;  //�����t���O
				bord[i][j].x = 625;  //��i�@�^��
				bord[i][j].y = 95;
			}
			else if (i == 3 && j == 0) {
				bord[i][j].flg = 3;  //�����t���O
				bord[i][j].x = 860;  //��i�@�E
				bord[i][j].y = 95;
			}
			else if (i == 0 && j == 1) {
				bord[i][j].flg = 5;  //�����t���O
				bord[i][j].x = 150;  //���i�@���[
				bord[i][j].y = 335;
			}
			else if (i == 1 && j == 1) {
				bord[i][j].flg = 6;  //�����t���O
				bord[i][j].x = 390;  //���i�@��
				bord[i][j].y = 335;
			}
			else if (i == 2 && j == 1) {
				bord[i][j].flg = 7;  //�����t���O
				bord[i][j].x = 625;  //���i�@�^��
				bord[i][j].y = 335;
			}
			else if (i == 3 && j == 1) {
				bord[i][j].flg = 8;  //�����t���O
				bord[i][j].x = 865;  //���i�@�E
				bord[i][j].y = 335;
			}
			else if (i == 4 && j == 1) {
				bord[i][j].flg = 9; //�����t���O
				bord[i][j].x = 1080;  //���i�@�E�[
				bord[i][j].y = 335;
			}
			else if (i == 1 && j == 2) {
				bord[i][j].flg = 11; //�����t���O
				bord[i][j].x = 390;  //���i�@��
				bord[i][j].y = 575;
			}
			else if (i == 2 && j == 2) {
				bord[i][j].flg = 12; //�����t���O
				bord[i][j].x = 625;  //���i�@�^��
				bord[i][j].y = 575;
			}
			else if (i == 3 && j == 2) {
				bord[i][j].flg = 13; //�����t���O
				bord[i][j].x = 860;  //���i�@�E
				bord[i][j].y = 575;
			}
		}
	}
}

Hound::~Hound()
{
	// ���f���n���h���̍폜
	/*MV1DeleteModel(HoundImg);
	MV1DeleteModel(RabbitImg);*/
}

AbstractScene* Hound::Update()
{
	//�J�[�\���ړ�����
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
		cursorFlg -= 5;
		if (cursorFlg < 1 || cursorFlg == 0 || cursorFlg == 4) {
			cursorFlg += 5;
		}
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
		cursorFlg += 5;
		if (cursorFlg > 14 || cursorFlg == 14 || cursorFlg == 10) {
			cursorFlg -= 5;
		}
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		cursorFlg -= 1;
		if (cursorFlg < 1 || cursorFlg == 4 || cursorFlg == 10) {
			cursorFlg += 1;
		}
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		cursorFlg += 1;
		if (cursorFlg < 1 || cursorFlg == 4 || cursorFlg == 10 || cursorFlg == 14) {
			cursorFlg -= 1;
		}
	}

	//A�{�^���ŃE�T�M��I������
	if (RabbitMoveflg == 0)
	{
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
		{
			if (RabbitFlg == cursorFlg)
			{
				RabbitMoveflg = 1;
			}
			else {
				RabbitMoveflg = 0;
			}

		}
	}
	else if(RabbitMoveflg == 1)	//�I�������E�T�M�𓮂���
	{
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
			RabbitFlg = cursorFlg;
			if (RabbitFlg == HoundFlg1 || RabbitFlg == HoundFlg2 || RabbitFlg == HoundFlg3 || RabbitFlg < 1 || RabbitFlg == 0 || RabbitFlg == 4) {
				RabbitFlg += 5;
			}
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
			RabbitFlg = cursorFlg;
			if (RabbitFlg == HoundFlg1 || RabbitFlg == HoundFlg2 || RabbitFlg == HoundFlg3 || RabbitFlg > 14 || RabbitFlg == 14 || RabbitFlg == 10) {
				RabbitFlg -= 5;
			}
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
			RabbitFlg = cursorFlg;
			if (RabbitFlg == HoundFlg1 || RabbitFlg == HoundFlg2 || RabbitFlg == HoundFlg3 || RabbitFlg >= 14 || RabbitFlg == 4 || RabbitFlg == 10) {
				RabbitFlg -= 1;
			}
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
			RabbitFlg = cursorFlg;
			if (RabbitFlg == HoundFlg1 || RabbitFlg == HoundFlg2 || RabbitFlg == HoundFlg3 || RabbitFlg == 0 || RabbitFlg == 10) {
				RabbitFlg += 1;
			}
		}
		else if(PAD_INPUT::OnButton(XINPUT_BUTTON_A))
		{
			RabbitMoveflg = 0;
		}
	}

	//A�{�^���ŗ���I������
	if (HoundMoveflg1 == 0)
	{
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
		{
			if (HoundFlg1 == cursorFlg)
			{
				HoundMoveflg1 = 1;
			}
			else {
				HoundMoveflg1 = 0;
			}

		}
	}
	else if(HoundMoveflg1 == 1)	//�I���������𓮂���
	{
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
			HoundFlg1 = cursorFlg;
			if (HoundFlg1 == RabbitFlg || HoundFlg1 == HoundFlg2 || HoundFlg1 == HoundFlg3 || HoundFlg1 < 1 || HoundFlg1 == 0 || HoundFlg1 == 4) {
				HoundFlg1 += 5;
			}
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
			HoundFlg1 = cursorFlg;
			if (HoundFlg1 == RabbitFlg || HoundFlg1 == HoundFlg2 || HoundFlg1 == HoundFlg3 || HoundFlg1 > 14 || HoundFlg1 == 14 || HoundFlg1 == 10) {
				HoundFlg1 -= 5;
			}
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
			HoundFlg1 = cursorFlg;
			if (HoundFlg1 == RabbitFlg || HoundFlg1 == HoundFlg2 || HoundFlg1 == HoundFlg3 || HoundFlg1 >= 14 || HoundFlg1 == 4 || HoundFlg1 == 10) {
				HoundFlg1 -= 1;
			}
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
		{
			HoundMoveflg1 = 0;
		}
	}
	
	
	//A�{�^���ŗ���I������2
	if (HoundMoveflg2 == 0)
	{
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
		{
			if (HoundFlg2 == cursorFlg)
			{
				HoundMoveflg2 = 1;
			}
			else {
				HoundMoveflg2 = 0;
			}

		}
	}
	else if(HoundMoveflg2 == 1)	//�I���������𓮂���
	{
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
			HoundFlg2 = cursorFlg;
			if (HoundFlg2 == HoundFlg1 || HoundFlg2 == HoundFlg3 || HoundFlg2 < 1 || HoundFlg2 == 0 || HoundFlg2 == 4) {
				HoundFlg2 += 5;
			}
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
			HoundFlg2 = cursorFlg;
			if (HoundFlg2 == HoundFlg1 || HoundFlg2 == HoundFlg3 || HoundFlg2 > 14 || HoundFlg2 == 14 || HoundFlg2 == 10) {
				HoundFlg2 -= 5;
			}
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
			HoundFlg2 = cursorFlg;
			if (HoundFlg2 == HoundFlg1 || HoundFlg2 == HoundFlg3 || HoundFlg2 >= 14 || HoundFlg2 == 4 || HoundFlg2 == 10) {
				HoundFlg2 -= 1;
			}
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
		{
			HoundMoveflg2 = 0;
		}
	}
	
	
	//A�{�^���ŗ���I������3
	if (HoundMoveflg3 == 0)
	{
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
		{
			if (HoundFlg3 == cursorFlg)
			{
				HoundMoveflg3 = 1;
			}
			else {
				HoundMoveflg3 = 0;
			}

		}
	}
	else if(HoundMoveflg3 == 1)	//�I���������𓮂���
	{
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
			HoundFlg3 = cursorFlg;
			if (HoundFlg3 == HoundFlg1 || HoundFlg3 == HoundFlg2 || HoundFlg3 < 1 || HoundFlg3 == 0 || HoundFlg3 == 4) {
				HoundFlg3 += 5;
			}
		}

		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
			HoundFlg3 = cursorFlg;
			if (HoundFlg3 == HoundFlg1 || HoundFlg3 == HoundFlg2 || HoundFlg3 > 14 || HoundFlg3 == 14 || HoundFlg3 == 10) {
				HoundFlg3 -= 5;
			}
		}

		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
			HoundFlg3 = cursorFlg;
			if (HoundFlg3 == HoundFlg1 || HoundFlg3 == HoundFlg2 || HoundFlg3 >= 14 || HoundFlg3 == 4 || HoundFlg3 == 10) {
				HoundFlg3 -= 1;
			}
		}

		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
		{
			HoundMoveflg3 = 0;
		}
	}
	

	GameJudge();

	return this;
}

void Hound::GameJudge()
{
	if(HoundFlg1 = 8 || HoundFlg2 = 3)
}

void Hound::Draw() const
{
	//�w�i�摜
	DrawGraph(0, 0, BackGroundImg, TRUE);
	//�^�C�g��
	DrawString(10, 20, "�v���C���[����͗�", 0x000000);

	//SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -1000), VGet(0, 0, 0));

	//// ��ʂɉf��ʒu�ɂR�c���f�����ړ�
	//MV1SetPosition(RabbitImg, VGet(320.0f, -300.0f, 600.0f));
	//MV1SetScale(RabbitImg, VGet(1, 1, 1)); // ���f���̃X�P�[����ݒ�
	//MV1SetRotationXYZ(RabbitImg, VGet(0, 0, 0)); // ���f���̉�]��ݒ�

	// �e�N�X�`���̐ݒ�
	//SetUseTextureToShader(0, R_texture);

	//MV1SetPosition(HoundImg, VGet(320.0f, -300.0f, 600.0f));

	//3D���f���̕`��
	//MV1DrawModel(RabbitImg);
	//MV1DrawModel(HoundImg);

	//���̋�(��)
	//DrawBox(390, 95, 440, 145, 0x0000ff, TRUE);     //��
	//DrawBox(150, 335, 200, 385, 0x0000ff, TRUE);   //�^��
	//DrawBox(390, 575, 440, 625, 0x0000ff, TRUE);     //��

	//�J�[�\���E�E�T�M�E���̓���
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {

			//�J�[�\���\��
			if (cursorFlg == 1 && bord[i][j].flg == 1) {
				DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
			}
			else if (cursorFlg == 2 && bord[i][j].flg == 2) {
				DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
			}
			else if (cursorFlg == 3 && bord[i][j].flg == 3) {
				DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
			}
			else if (cursorFlg == 5 && bord[i][j].flg == 5) {   //�����ʒu
				DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
			}
			else if (cursorFlg == 6 && bord[i][j].flg == 6) {
				DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
			}
			else if (cursorFlg == 7 && bord[i][j].flg == 7) {
				DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
			}
			else if (cursorFlg == 8 && bord[i][j].flg == 8) {
				DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
			}
			else if (cursorFlg == 9 && bord[i][j].flg == 9) {
				DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
			}
			else if (cursorFlg == 11 && bord[i][j].flg == 11) {
				DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
			}
			else if (cursorFlg == 12 && bord[i][j].flg == 12) {
				DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
			}
			else if (cursorFlg == 13 && bord[i][j].flg == 13) {
				DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
			}

			//�E�T�M�̕`��
			if (RabbitDrawflg == TRUE) {
				if (RabbitFlg == 1 && bord[i][j].flg == 1) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				if (RabbitFlg == 2 && bord[i][j].flg == 2) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				if (RabbitFlg == 3 && bord[i][j].flg == 3) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				if (RabbitFlg == 5 && bord[i][j].flg == 5) {	
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				if (RabbitFlg == 6 && bord[i][j].flg == 6) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				if (RabbitFlg == 7 && bord[i][j].flg == 7) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				if (RabbitFlg == 8 && bord[i][j].flg == 8) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				if (RabbitFlg == 9 && bord[i][j].flg == 9) {		//�����ʒu
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				if (RabbitFlg == 11 && bord[i][j].flg == 11) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				if (RabbitFlg == 12 && bord[i][j].flg == 12) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				if (RabbitFlg == 13 && bord[i][j].flg == 13) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
			}

			//��1�̕`��
			if (HoundDrawflg1 == TRUE) {
				if (HoundFlg1 == 1 && bord[i][j].flg == 1) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (HoundFlg1 == 2 && bord[i][j].flg == 2) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (HoundFlg1 == 3 && bord[i][j].flg == 3) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (HoundFlg1 == 5 && bord[i][j].flg == 5) {	//�����ʒu
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (HoundFlg1 == 6 && bord[i][j].flg == 6) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (HoundFlg1 == 7 && bord[i][j].flg == 7) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (HoundFlg1 == 8 && bord[i][j].flg == 8) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (HoundFlg1 == 9 && bord[i][j].flg == 9) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (HoundFlg1 == 11 && bord[i][j].flg == 11) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (HoundFlg1 == 12 && bord[i][j].flg == 12) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (HoundFlg1 == 13 && bord[i][j].flg == 13) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
			}
			
			//��2�̕`��
			if (HoundDrawflg2 == TRUE) {
				if (HoundFlg2 == 1 && bord[i][j].flg == 1) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg2 == 2 && bord[i][j].flg == 2) {	//�����ʒu
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg2 == 3 && bord[i][j].flg == 3) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg2 == 5 && bord[i][j].flg == 5) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg2 == 6 && bord[i][j].flg == 6) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg2 == 7 && bord[i][j].flg == 7) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
					}
				else if (HoundFlg2 == 8 && bord[i][j].flg == 8) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg2 == 9 && bord[i][j].flg == 9) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg2 == 11 && bord[i][j].flg == 11) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg2 == 12 && bord[i][j].flg == 12) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg2 == 13 && bord[i][j].flg == 13) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
			}
			
			//��3�̕`��
			if (HoundDrawflg3 == TRUE) {
				if (HoundFlg3 == 1 && bord[i][j].flg == 1) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg3 == 2 && bord[i][j].flg == 2) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg3 == 3 && bord[i][j].flg == 3) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg3 == 5 && bord[i][j].flg == 5) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg3 == 6 && bord[i][j].flg == 6) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg3 == 7 && bord[i][j].flg == 7) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg3 == 8 && bord[i][j].flg == 8) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg3 == 9 && bord[i][j].flg == 9) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg3 == 11 && bord[i][j].flg == 11) {		//�����ʒu
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg3 == 12 && bord[i][j].flg == 12) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg3 == 13 && bord[i][j].flg == 13) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
			}
		}
	}

	SetFontSize(20);
	DrawFormatString(200, 10, 0x000000, "cursorFlg:%d", cursorFlg);
	DrawFormatString(400, 10, 0x000000, "HoundFlg1:%d", HoundFlg1);
	DrawFormatString(600, 10, 0x000000, "HoundFlg2:%d", HoundFlg2);
	DrawFormatString(800, 10, 0x000000, "HoundFlg3:%d", HoundFlg3);

	DrawFormatString(1000, 10, 0x000000, "HoundMoveflg1:%d", HoundMoveflg1);
	DrawFormatString(1000, 50, 0x000000, "HoundMoveflg2:%d", HoundMoveflg2);
	DrawFormatString(1000, 90, 0x000000, "HoundMoveflg3:%d", HoundMoveflg3);

	DrawFormatString(1000, 130, 0x000000, "RabbitMoveflg:%d", RabbitMoveflg);
}