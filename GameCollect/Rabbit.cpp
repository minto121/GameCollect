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

	//RabbitImg[1] = LoadGraph("../images/RabbitAndHounds/Rabbit.png");
	//LoadDivGraph("images/RabbitAndHounds/Rabbit.png", 2, 2, 1, 256, 512, RabbitImg);

	// �e�N�X�`���̓ǂݍ���
	//R_texture = LoadGraph("images/RabbitAndHounds/Textures/Coloe_Textures/T_PigHead_00.TGA");

	RabbitFlg = 5;
	RabbitDrawflg = TRUE;
	RabbitMoveflg = 0;

	cursorFlg = 5;		//�J�[�\���t���O������

	//�X�e�[�W������
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 3; j++) {
			if (i == 0 && j == 0) {
				bord[i][j].flg = 16; //����Ȃ��t���O
				bord[i][j].x = 150;  //����
				bord[i][j].y = 100; 
			}
			else if (i == 4 && j == 0) {
				bord[i][j].flg =16; //����Ȃ��t���O
				bord[i][j].x = 1080;  //�E��
				bord[i][j].y = 100;
			}
			else if (i == 0 && j == 2) {
				bord[i][j].flg = 16; //����Ȃ��t���O
				bord[i][j].x = 150;  //����
				bord[i][j].y = 575;
			}
			else if (i == 4 && j == 2) {
				bord[i][j].flg = 16;  //����Ȃ��t���O
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

			//�E�T�M�̕`��
			if (RabbitDrawflg == TRUE) {
				if (RabbitFlg == 1 && bord[i][j].flg == 1) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (RabbitFlg == 2 && bord[i][j].flg == 2) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (RabbitFlg == 3 && bord[i][j].flg == 3) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (RabbitFlg == 5 && bord[i][j].flg == 5) {	//�����ʒu
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (RabbitFlg == 6 && bord[i][j].flg == 6) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (RabbitFlg == 7 && bord[i][j].flg == 7) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (RabbitFlg == 8 && bord[i][j].flg == 8) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (RabbitFlg == 9 && bord[i][j].flg == 9) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (RabbitFlg == 11 && bord[i][j].flg == 11) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (RabbitFlg == 12 && bord[i][j].flg == 12) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (RabbitFlg == 13 && bord[i][j].flg == 13) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
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
	//// �E�T�M���ړ�
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
	//	RabbitFlg -= 5;
	//}
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
	//	RabbitFlg += 5;
	//}
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
	//	RabbitFlg -= 1;
	//}
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
	//	RabbitFlg += 1;
	//}

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

	//���̋�(��)
	//DrawBox(890, 140, 960, 210, 0x0000ff, TRUE);     //��
	//DrawBox(1080, 350, 1130, 400, 0x0000ff, TRUE);   //�^��
	//DrawBox(900, 550, 950, 600, 0x0000ff, TRUE);     //��

	//�E�T�M�̋�(��)
	//DrawBox(150 + rabbit_X, 340 + rabbit_Y, 200 + rabbit_X, 390 + rabbit_Y, 0xff0000, RabbitImg[2]);
	//DrawGraph(100, 250, rabbitimg, TRUE);

	//�J�[�\���\��
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
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
		}
	}

	SetFontSize(20);
	DrawFormatString(200, 10, 0x000000, "rabbitFlg:%d", RabbitFlg);

	
}