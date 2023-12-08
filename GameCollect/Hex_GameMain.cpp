#include"DxLib.h"
#include"Hex_GameMain.h"
#include"Padinput.h"

//�R���X�g���N�^
Hex::Hex() {
	BackImg = LoadGraph("images/Hex/Background02.png");
	BlueHexImg = LoadGraph("images/Hex/hexagon-B50.png");
	RedHexImg = LoadGraph("images/Hex/hexagon-R50.png");
	BlackHexImg = LoadGraph("images/Hex/hexagon-Black50.png");
	GreenHexImg = LoadGraph("images/Hex/hexagon-G50.png");
	HexImg = LoadGraph("images/Hex/hexagon-50.png");
	Select_i = 6;
	Select_j = 6;
	P_CheckFlg = 0;
	P_CheckCnt = 0;
	ClearFlg = 0;
	E_CheckFlg = 0;
	E_CheckCnt = 0;
	TurnFlg = GetRand(1);
	TurnSave = TurnFlg;
	GameInit();
}
	
//�`��ȊO
AbstractScene* Hex::Update() {
	if (ClearFlg == 0) {
		TurnSave = TurnFlg;
		if (TurnFlg % 2 == 1) {
			Select();
		}
		if (TurnFlg % 2 == 0) {
			TurnSave = TurnFlg;
			Enemy();
		}
		Check_P();
		Check_E();
	}
	else if (ClearFlg == 1) {

	}
	else if (ClearFlg == 2) {

	}
	return this;
}

//�`��̂�
void Hex::Draw()const {

	if (ClearFlg == 0) {
		//�w�i�摜
		DrawGraph(0, 0, BackImg, FALSE);

		DrawStage();

		DrawGraph(gStage[Select_i][Select_j].x, gStage[Select_i][Select_j].y, GreenHexImg, TRUE);

		//DrawGraph(gStage[1][2].x, gStage[1][2].y, GreenHexImg, TRUE);

	}
	if (ClearFlg == 1) {
		DrawGraph(0, 0, BackImg, FALSE);
	}
	else if (ClearFlg == 2) {
		DrawGraph(615, 335, GreenHexImg, TRUE);
	}
}

//������
void Hex::GameInit() {
	//�X�e�[�W������
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 13; j++) {
			gStage[i][j].cnt = 0;
			if (j == 0 && i == 0 || j == 12 && i == 12) {
				gStage[i][j].flg = 3;	//��
			}
			else if (i == 0 && j != 12 || i == 12) {
				gStage[i][j].flg = 5;	//��
			}
			else if (j == 0 || j == 12) {
				gStage[i][j].flg = 4;	//��
			}
			else {
				gStage[i][j].flg = 0;	//��
			}
			gStage[i][j].x = (j + i - 1) * -30 + 945;	
			gStage[i][j].y = (j - i - 1) * -17 + 320;	
		}
	}
}

//�^�C����u���ꏊ�̈ړ�&�ݒu
void Hex::Select() {
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		if (gStage[++Select_i][--Select_j].flg >= 3) {
			Select_j = Select_j + 1;
			Select_i = Select_i - 1;
			if (gStage[Select_i][--Select_j].flg >= 3) {
				Select_j = Select_j + 1;
			}
			if (gStage[++Select_i][Select_j].flg >= 3) {
				Select_i = Select_i - 1;
			}
		}
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
	{
		if (gStage[--Select_i][++Select_j].flg >= 3) {
			Select_i = Select_i + 1;
			Select_j = Select_j - 1;
			if (gStage[Select_i][++Select_j].flg >= 3) {
				Select_j = Select_j - 1;
			}
			if (gStage[--Select_i][Select_j].flg >= 3) {
				Select_i = Select_i + 1;
			}
		}
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		if (gStage[Select_i][--Select_j].flg >= 3) {
			Select_j = Select_j + 1;
			if (gStage[--Select_i][Select_j].flg >= 3) {
				Select_i = Select_i + 1;
			}
		}
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		if (gStage[++Select_i][Select_j].flg >= 3) {
			Select_i = Select_i - 1;
			if (gStage[Select_i][++Select_j].flg >= 3) {
				Select_j = Select_j - 1;
			}
		}
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		if (gStage[Select_i][Select_j].flg == 0) {
			gStage[Select_i][Select_j].flg = 1;
			Select_i = 6;
			Select_j = 6;
			TurnFlg++;
		}
	}
	/*if (TurnFlg % 2 == 0) {
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_B))
		{
			if (gStage[Select_i][Select_j].flg == 0) {
				gStage[Select_i][Select_j].flg = 2;
				Select_i = 6;
				Select_j = 6;
				TurnFlg++;
			}
		}
	}*/
}

//�X�e�[�W�`��
void Hex::DrawStage() const {

	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 13; j++) {
			switch (gStage[i][j].flg) {
			case 0:
				DrawGraph(gStage[i][j].x, gStage[i][j].y, HexImg, TRUE);
				break;
			case 1:
			case 4:
				DrawGraph(gStage[i][j].x, gStage[i][j].y, RedHexImg, TRUE);
				break;
			case 2:
			case 5:
				DrawGraph(gStage[i][j].x, gStage[i][j].y, BlueHexImg, TRUE);
				break;
			case 3:
				DrawGraph(gStage[i][j].x, gStage[i][j].y, BlackHexImg, TRUE);
				break;
			}
		}
	}
}

void Hex::Check_P() {
	//�ۑ��p
	int i = 1;
	int j = 1;
	//�ύX�p
	int x = 1;
	int y = 1;
	//�J�E���g�ۑ�
	int SaveCnt = P_CheckCnt;

	for (i = 1; i < 12;i++) {
		for (j = 1; j < 12; j++) {
			//�ŏ��̗�̌���
			if (i == 1) {
				//���������אڂ���}�X���L������
				if (gStage[j][i].flg == 1) {
					x = i;
					y = j;
					//��
					gStage[--y][++x].cnt = 1;
					x = i;
					y = j;
					//��
					gStage[++y][--x].cnt = 1;
					x = i;
					y = j;
					//����
					gStage[y][++x].cnt = 1;
					x = i;
					//�E��
					gStage[--y][x].cnt = 1;
					y = j;
					//��
					gStage[++y][x].cnt = 1;
					y = j;
					//�E
					gStage[y][--x].cnt = 1;
					x = i;
					P_CheckCnt++;
					SaveCnt = P_CheckCnt;
				}	//�ŏ��̗�ɋ�Ȃ�������I��
				else if(j == 11){
					if (P_CheckCnt == 0) {
						break;
					}
				}
			}	//���̗�̌����i��Ȃ�������I���j
			else {
				if (P_CheckCnt != 0) {
					//�����}�X���L������Ă�����אڂ���}�X���L������
					if (gStage[j][i].flg == 1) {
						if (gStage[j][i].cnt == 1) {
							x = i;
							y = j;
							//��
							gStage[--y][++x].cnt = 1;
							x = i;
							y = j;
							//��
							gStage[++y][--x].cnt = 1;
							x = i;
							y = j;
							//����
							gStage[y][++x].cnt = 1;
							x = i;
							//�E��
							gStage[--y][x].cnt = 1;
							y = j;
							//��
							gStage[++y][x].cnt = 1;
							y = j;
							//�E
							gStage[y][--x].cnt = 1;
							x = i;
							P_CheckCnt++;
							//11�񌟍����p�������Ƃ��N���A�����ׂ�
							if (i > 10) {
								if (gStage[y][++x].flg == 4) {
									P_CheckFlg = 1;
									break;
								}
								else {
									x = i;
								}
							}//�Ō�܂Ō������ċ�Ȃ������ꍇ�I��
							else if (j == 11 && SaveCnt == P_CheckCnt) {
								SaveCnt = P_CheckCnt;
								P_CheckCnt = 0;
								break;
							}//�r���Ȃ̂Ōp��
							else {
								SaveCnt = P_CheckCnt;
							}
						}
					}
				}
			}
		}

		//�N���A�����𖞂����Ă�����I��
		if (P_CheckFlg == 1) {
			ClearFlg = 1;
			P_CheckCnt = 0;
			P_CheckFlg = 0;
			break;
		}
		
		//��ɋ�Ȃ�������I��
		if (P_CheckCnt == 0) {
			break;
		}
	}
}

void Hex::Check_E() {
	//�ۑ��p
	int i = 1;
	int j = 1;
	//�ύX�p
	int x = 1;
	int y = 1;
	//�J�E���g�ۑ�
	int SaveCnt = E_CheckCnt;

	for (i = 1; i < 12; i++) {
		for (j = 1; j < 12; j++) {
			//�ŏ��̗�̌���
			if (i == 1) {
				//���������אڂ���}�X���L������
				if (gStage[i][j].flg == 2) {
					x = i;
					y = j;
					//��
					gStage[--x][++y].cnt = 2;
					x = i;
					y = j;
					//��
					gStage[++x][--y].cnt = 2;
					x = i;
					y = j;
					//����
					gStage[x][++y].cnt = 2;
					y = j;
					//�E��
					gStage[--x][y].cnt = 2;
					x = i;
					//��
					gStage[++x][y].cnt = 2;
					x = i;
					//�E
					gStage[x][--y].cnt = 2;
					y = j;
					E_CheckCnt++;
					SaveCnt = E_CheckCnt;
				}	//�ŏ��̗�ɋ�Ȃ�������I��
				else if (j == 11) {
					if (E_CheckCnt == 0) {
						break;
					}
				}
			}	//���̗�̌����i��Ȃ�������I���j
			else {
				if (E_CheckCnt != 0) {
					//�����}�X���L������Ă�����אڂ���}�X���L������
					if (gStage[i][j].flg == 2) {
						if (gStage[i][j].cnt == 2) {
							x = i;
							y = j;
							//��
							gStage[--x][++y].cnt = 2;
							x = i;
							y = j;
							//��
							gStage[++x][--y].cnt = 2;
							x = i;
							y = j;
							//����o
							gStage[x][++y].cnt = 2;
							y = j;
							//�E��o
							gStage[--x][y].cnt = 2;
							x = i;
							//��o
							gStage[++x][y].cnt = 2;
							x = i;
							//�Eo
							gStage[x][--y].cnt = 2;
							y = j;
							E_CheckCnt++;
							//11�񌟍����p�������Ƃ��N���A�����ׂ�
							if (i > 10) {
								if (gStage[++x][y].flg == 5) {
									E_CheckFlg = 1;
									break;
								}
								else {
									x = i;
								}
							}	//�Ō�܂Ō������ċ�Ȃ������ꍇ�I��
							else if (j == 11 && SaveCnt == E_CheckCnt) {
								SaveCnt = E_CheckCnt;
								E_CheckCnt = 0;
								break;
							}//�r���Ȃ̂Ōp��
							else {
								SaveCnt = E_CheckCnt;
							}
						}
					}
				}
			}
		}

		//�N���A�����𖞂����Ă�����I��
		if (E_CheckFlg == 1) {
			ClearFlg = 2;
			E_CheckCnt = 0;
			E_CheckFlg = 0;
			break;
		}

		//��ɋ�Ȃ�������I��
		if (E_CheckCnt == 0) {
			break;
		}
	}
}

void Hex::Enemy() {

	int x = 1;
	int y = 1;
	int rand = GetRand(1);

	if (TurnFlg == 0) {
		gStage[6][6].flg = 2;
		TurnFlg++;
	}
	else if (TurnFlg == 1) {
		if (gStage[6][6].flg == 0) {
			gStage[6][6].flg = 2;
			TurnFlg++;
		}	
		else if (gStage[4][8].flg != 0) {
		gStage[4][8].flg = 2;
		TurnFlg++;
		}
	}

	if(TurnFlg > 1){
		rand = GetRand(1);
		switch (rand) {	//0:���� 1:��
		case 0:
			for (int i = 1; i < 12; i++) {
				for (int j = 1; j < 12; j++) {
					if (gStage[i][j].flg == 2) {
						x = i;
						y = j;
						rand = GetRand(1);
						switch (rand) {
						case 0:	//����
							x = x - 2;
							--y;
							//����
							if (x <= 0 || x > 11 || y <= 0 || y > 11) {
								break;
							}//�z�u
							else if (gStage[x][y].flg == 0) {
								gStage[x][y].flg = 2;
								x = i;
								y = j;
								TurnFlg++;
								break;
							}
							else {
								x = i;
								y = j;
							}
						case 1:	//��
							++x;
							++y;
							//����
							if (x <= 0 || x > 11 || y <= 0 || y > 11) {
								break;
							}//�z�u
							else if(gStage[x][y].flg == 0) {
								gStage[x][y].flg = 2;
								x = i;
								y = j;
								TurnFlg++;
								break;
							}
							else {
								x = i;
								y = j;
								rand = GetRand(2);
								switch(rand){
								case 0:	//��
									if (gStage[++x][--y].flg == 0) {
										gStage[x][y].flg = 2;
										x = i;
										y = j;
										TurnFlg++;
										break;
									}
									else {
										x = i;
										y = j;
									}
								case 1:	//�����P
									if (gStage[++x][y].flg == 0) {
										gStage[x][y].flg = 2;
										x = i;
										y = j;
										TurnFlg++;
										break;
									}
									else {
										x = i;
										y = j;
									}
								case 2:	//����P
									if (gStage[x][++y].flg == 0) {
										gStage[x][y].flg = 2;
										x = i;
										y = j;
										TurnFlg++;
										break;
									}
									else {
										x = i;
										y = j;
									}
								}
							}
						}
						////�E��
						//if (gStage[++i][j - 2].flg == 0 || i <= 11 || i > 0 || j <= 11 || j > 0) {
						//	gStage[i][j].flg = 2;
						//	TurnFlg++;
						//	break;
						//}
						////�E
						//else if (gStage[--i][--j].flg == 0 || i <= 11 || i > 0 || j <= 11 || j > 0) {
						//	gStage[i][j].flg = 2;
						//	TurnFlg++;
						//	break;
						//}
						//else {
						//	rand = GetRand(2);
						//	switch (rand) {
						//	case 0:
						//		if (gStage[--i][j].flg == 0) {
						//			gStage[i][j].flg = 2;
						//			TurnFlg++;
						//		}
						//		break;
						//	case 1:
						//		if (gStage[i][--j].flg == 0) {
						//			gStage[i][j].flg = 2;
						//			TurnFlg++;
						//		}
						//		break;
						//	case 2:
						//		if (gStage[++i][--j].flg == 0) {
						//			gStage[i][j].flg = 2;
						//			TurnFlg++;
						//		}
						//		break;
						//	}
						//	break;
						//}
					}
				}
				if (TurnSave != TurnFlg)break;
			}
		case 1:
			for (int i = 12; i > 1; i--) {
				for (int j = 1; j < 12; j++) {
					if (gStage[i][j].flg == 2) {
						
					}
				}
				if (TurnSave != TurnFlg)break;
			}
			break;
		}
	}
	if (TurnSave == TurnFlg) {
		for (int i = 1; i < 12; i++) {
			for (int j = 1; j < 12; j++) {
				if (gStage[j][i].flg == 0) {
					gStage[j][i].flg = 2;
					TurnFlg++;
					break;
				}
			}
			if (TurnSave != TurnFlg)break;
		}
	}
}
