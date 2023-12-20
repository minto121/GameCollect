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

	rabbitFlg = 5;

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

Rabbit::~Rabbit()
{
	// ���f���n���h���̍폜
	/*MV1DeleteModel(HoundImg);
	MV1DeleteModel(RabbitImg);*/
}

AbstractScene* Rabbit::Update()
{	
	// �E�T�M���ړ�
	/*if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
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
	}*/

	// �E�T�M���ړ�
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
		rabbitFlg += 5;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
		rabbitFlg -= 5;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		rabbitFlg += 1;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		rabbitFlg -= 1;
	}
	
	//��ʂ���o�Ȃ��悤�ɂ���
	/*if (rabbit_X < 100 || rabbit_X > 1100 || rabbit_Y < -300 || rabbit_Y > 400)
	{
		rabbit_X = 0;
		rabbit_Y = 0;
	}*/

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
	//DrawBox(890, 140, 960, 210, 0x0000ff, TRUE);     //��
	//DrawBox(1080, 350, 1130, 400, 0x0000ff, TRUE);   //�^��
	//DrawBox(900, 550, 950, 600, 0x0000ff, TRUE);     //��
	
	//�J�[�\��
	DrawGraph(-10 + rabbit_X, 250 + rabbit_Y, cursorImg, TRUE);

	//�E�T�M�̋�(��)
	//DrawBox(150 + rabbit_X, 340 + rabbit_Y, 200 + rabbit_X, 390 + rabbit_Y, 0xff0000, RabbitImg[2]);
	//DrawGraph(100, 250, rabbitimg, TRUE);

	//�{�[�h�̃}�X
	//for (int i = 0; i < 5; i++) {
	//	for (int j = 0; j < 3; j++) {
	//		if (bord[i][j].flg == -1) {   //�����Ȃ��}�X�\��
	//			DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x000000, TRUE);
	//		}
	//		if (bord[i][j].flg == 1) {
	//			DrawBox(bord[i][j].x - 5, bord[i][j].y - 5, bord[i][j].x + 55, bord[i][j].y + 55, 0xffffff, TRUE);
	//		}
	//		else if (bord[i][j].flg == 2) {
	//			DrawBox(bord[i][j].x - 5, bord[i][j].y - 5, bord[i][j].x + 55, bord[i][j].y + 55, 0xffffff, TRUE);
	//		}
	//		else if (bord[i][j].flg == 3) {
	//			DrawBox(bord[i][j].x - 5, bord[i][j].y - 5, bord[i][j].x + 55, bord[i][j].y + 55, 0xffffff, TRUE);
	//		}
	//		else if (bord[i][j].flg == 5) {
	//			DrawBox(bord[i][j].x - 5, bord[i][j].y - 5, bord[i][j].x + 55, bord[i][j].y + 55, 0xffffff, TRUE);
	//		}
	//		else if (bord[i][j].flg == 6) {
	//			DrawBox(bord[i][j].x - 5, bord[i][j].y - 5, bord[i][j].x + 55, bord[i][j].y + 55, 0xffffff, TRUE);
	//		}
	//		else if (bord[i][j].flg == 7) {
	//			DrawBox(bord[i][j].x - 5, bord[i][j].y - 5, bord[i][j].x + 55, bord[i][j].y + 55, 0xffffff, TRUE);
	//		}
	//		else if (bord[i][j].flg == 8) {
	//			DrawBox(bord[i][j].x - 5, bord[i][j].y - 5, bord[i][j].x + 55, bord[i][j].y + 55, 0xffffff, TRUE);
	//		}
	//		else if (bord[i][j].flg == 9) {
	//			DrawBox(bord[i][j].x - 5, bord[i][j].y - 5, bord[i][j].x + 55, bord[i][j].y + 55, 0xffffff, TRUE);
	//		}
	//		else if (bord[i][j].flg == 11) {
	//			DrawBox(bord[i][j].x - 5, bord[i][j].y - 5, bord[i][j].x + 55, bord[i][j].y + 55, 0xffffff, TRUE);
	//		}
	//		else if (bord[i][j].flg == 12) {
	//			DrawBox(bord[i][j].x - 5, bord[i][j].y - 5, bord[i][j].x + 55, bord[i][j].y + 55, 0xffffff, TRUE);
	//		}
	//		else if (bord[i][j].flg == 13) {
	//			DrawBox(bord[i][j].x - 5, bord[i][j].y - 5, bord[i][j].x + 55, bord[i][j].y + 55, 0xffffff, TRUE);
	//		}
	//	}
	//}

	//�v���C���[�\��
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			switch (rabbitFlg)
			{
			case 0:
				if (rabbitFlg == 5 && bord[i][j].flg == 5) {   //�����ʒu
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				break;
			case 1:
				if (rabbitFlg == 1 && bord[i][j].flg == 1) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				break;
			case 2:
				if (rabbitFlg == 2 && bord[i][j].flg == 2) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				break;
			case 3:
				if (rabbitFlg == 3 && bord[i][j].flg == 3) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				break;
			case 4:
				if (rabbitFlg == 6 && bord[i][j].flg == 6) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				break;
			case 5:
				if (rabbitFlg == 7 && bord[i][j].flg == 7) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				break;
			case 6:
				if (rabbitFlg == 8 && bord[i][j].flg == 8) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				break;
			case 7:
				if (rabbitFlg == 9 && bord[i][j].flg == 9) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				break;
			case 8:
				if (rabbitFlg == 11 && bord[i][j].flg == 11) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				break;
			case 9:
				if (rabbitFlg == 12 && bord[i][j].flg == 12) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				break;
			case 10:
				if (rabbitFlg == 13 && bord[i][j].flg == 13) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				break;
			default:
				if (rabbitFlg == 5 && bord[i][j].flg == -1) {   //�����Ȃ��}�X�\��
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x000000, TRUE);
				}
				break;
	}
		}
	}

}