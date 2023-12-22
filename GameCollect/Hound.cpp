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

	hound_X = 0;
	hound_Y = 0;

	HoundFlg1 = 5;
	HoundFlg2 = 1;
	HoundFlg3 = 11;

	HoundMoveflg1 = FALSE;
	HoundMoveflg2 = FALSE;
	HoundMoveflg3 = FALSE;

	cursorFlg = 5;

	//�X�e�[�W������
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == 0 && j == 0) {
				bord[i][j].flg = 16; //����Ȃ��t���O
				bord[i][j].x = 150;  //����
				bord[i][j].y = 100;
			}
			else if (i == 4 && j == 0) {
				bord[i][j].flg = 16; //����Ȃ��t���O
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
	// �����ړ�
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
	//	HoundFlg -= 5;
	//}
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
	//	HoundFlg += 5;
	//}
	///*if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
	//	HoundFlg -= 1;
	//}*/
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
	//	HoundFlg += 1;
	//}

	//�J�[�\��
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
		cursorFlg -= 5;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
		cursorFlg += 5;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		cursorFlg -= 1;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		cursorFlg += 1;
	}

	if (HoundFlg1 == cursorFlg && PAD_INPUT::OnPressed(XINPUT_BUTTON_A)) {
		HoundMoveflg1 = TRUE;

		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
			HoundFlg1 -= 5;
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
			HoundFlg1 += 5;
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
			HoundFlg1 += 1;
		}
	}

	if (HoundFlg2 == cursorFlg && PAD_INPUT::OnPressed(XINPUT_BUTTON_A)) {
		HoundMoveflg2 = TRUE;

		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
			HoundFlg2 -= 5;
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
			HoundFlg2 += 5;
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
			HoundFlg2 += 1;
		}
	}
	
	if (HoundFlg3 == cursorFlg && PAD_INPUT::OnPressed(XINPUT_BUTTON_A)) {
		HoundMoveflg3 = TRUE;

		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
			HoundFlg3 -= 5;
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
			HoundFlg3 += 5;
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
			HoundFlg3 += 1;
		}
	}

	return this;
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

	//// �e�N�X�`���̐ݒ�
	//SetUseTextureToShader(0, R_texture);

	////MV1SetPosition(HoundImg, VGet(320.0f, -300.0f, 600.0f));

	////3D���f���̕`��
	//MV1DrawModel(RabbitImg);
	//MV1DrawModel(HoundImg);

	//���̋�(��)
	//DrawBox(390, 95, 440, 145, 0x0000ff, TRUE);     //��
	//DrawBox(150, 335, 200, 385, 0x0000ff, TRUE);   //�^��
	//DrawBox(390, 575, 440, 625, 0x0000ff, TRUE);     //��

	//�v���C���[�\��
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

			//��1�̕`��
			if (HoundMoveflg1 == TRUE) {
				if (HoundFlg1 == 1 && bord[i][j].flg == 1) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 2 && bord[i][j].flg == 2) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 3 && bord[i][j].flg == 3) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 5 && bord[i][j].flg == 5) {	//�����ʒu
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 6 && bord[i][j].flg == 6) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 7 && bord[i][j].flg == 7) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 8 && bord[i][j].flg == 8) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 9 && bord[i][j].flg == 9) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 11 && bord[i][j].flg == 11) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 12 && bord[i][j].flg == 12) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 13 && bord[i][j].flg == 13) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 0 && HoundFlg1 == 5 && HoundFlg1 == 10 && HoundFlg1 == 15) {   //�����Ȃ��}�X�\��
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
			}
			
			//��2�̕`��
			if (HoundMoveflg2 == TRUE) {
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
				else if (HoundFlg2 == 0 && HoundFlg2 == 5 && HoundFlg2 == 10 && HoundFlg2 == 15) {   //�����Ȃ��}�X�\��
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
			}
			
			//��3�̕`��
			if (HoundMoveflg3 == TRUE) {
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
				else if (HoundFlg3 == 0 && HoundFlg3 == 5 && HoundFlg3 == 10 && HoundFlg3 == 15) {   //�����Ȃ��}�X�\��
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
			}
		}
	}
	//�J�[�\��
	/*for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			
		}
	}*/

	//�J�[�\��
	//for (int i = 0; i < 5; i++) {
	//	for (int j = 0; j < 3; j++) {
	//		if (HoundFlg == 1 && bord[i][j].flg == 1) {
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//		else if (HoundFlg == 2 && bord[i][j].flg == 2) {
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//		else if (HoundFlg == 3 && bord[i][j].flg == 3) {
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//		else if (HoundFlg == 5 && bord[i][j].flg == 5) {   //�����ʒu
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//		else if (HoundFlg == 6 && bord[i][j].flg == 6) {
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//		else if (HoundFlg == 7 && bord[i][j].flg == 7) {
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//		else if (HoundFlg == 8 && bord[i][j].flg == 8) {
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//		else if (HoundFlg == 9 && bord[i][j].flg == 9) {
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//		else if (HoundFlg == 11 && bord[i][j].flg == 11) {
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//		else if (HoundFlg == 12 && bord[i][j].flg == 12) {
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//		else if (HoundFlg == 13 && bord[i][j].flg == 13) {
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//	}
	//}
	
	SetFontSize(20);
	DrawFormatString(200, 10, 0x000000, "cursorFlg:%d", cursorFlg);
	DrawFormatString(400, 10, 0x000000, "HoundFlg1:%d", HoundFlg1);
	DrawFormatString(600, 10, 0x000000, "HoundFlg2:%d", HoundFlg2);
	DrawFormatString(800, 10, 0x000000, "HoundFlg3:%d", HoundFlg3);

}