#include "Reversi.h"
#include<DxLib.h>
#include "PadInput.h"
#include"GameSelect.h"

#define SCREEN_HEIGHT 720	//��ʃT�C�Y (�c)
#define SCREEN_WIDTH 1280	//��ʃT�C�Y (��)



//// ��U��U��\��������
//void Reversi::FirstTurnScreen() {
//	DrawFormatString(100, 100, GetColor(255, 255, 255), "��U��U�����肵�܂��B");
//	DrawFormatString(100, 150, GetColor(255, 255, 255), "�X�y�[�X�L�[�������Ă��������B");
//
//	if (CheckHitKey(XINPUT_BUTTON_A)) {
//		SelectTurn();
//		// ��U��U�����܂�����A�Q�[����ʂɑJ�ڂ���Ȃǂ̏����������ɒǉ�
//	}
//}

Reversi::Reversi()
{
	
	BackImg = LoadGraph("images/Reversi/BackGround01.png");
	Bac = LoadGraph("images/Reversi/banmen_4.png");
	Bla = LoadGraph("images/Reversi/osero(black).png");
	Whi= LoadGraph("images/Reversi/osero(white).png");
	XOnce = TRUE;
	YOnce = TRUE;
	/*CursorPoint = { 0, 0 };*/

	K_Flg = FALSE;
	C_Flg = FALSE;
	//�|�[�Y����
	PauseFlg = FALSE;
	PauseFlashFlg = FALSE;
	PauseFlashTime = 0;

	//�t���O������
	Fla.Xr = 0;
	Fla.Xl = 0;
	Fla.Yu = 0;
	Fla.Yd = 0;
	Fla.button = 0;

	Tur = 0;
	End = FALSE;

	//�z��̏����l
	for (int y = 0; y < 8; y = y++)
	{
		for (int x = 0; x < 8; x = x++)
		{
			Sto.Typ[x][y] = 0;
			Sto.X[x][y] = 0;
			Sto.Y[x][y] = 0;
		}
	}

	//���㍕
	Sto.Typ[3][3] = 1;
	Sto.X[3][3] = 545;
	Sto.Y[3][3] = 280;

	//�E����
	Sto.Typ[4][4] = 1;
	Sto.X[4][4] = 630;
	Sto.Y[4][4] = 364;

	//������
	Sto.Typ[3][4] = 2;
	Sto.X[3][4] = 545;
	Sto.Y[3][4] = 365;

	//�E�㔒
	Sto.Typ[4][3] = 2;
	Sto.X[4][3] = 630;
	Sto.Y[4][3] = 279;

}

Reversi::~Reversi()
{

}

AbstractScene* Reversi::Update()
{


	//�|�[�Y�t���O�؂�ւ�����
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START))
	{
		PauseFlg = !PauseFlg;
	}
	//�|�[�Y���łȂ��Ȃ�
	if (PauseFlg == FALSE) {
		Fla.button = 0;
		Cursor();
		turn();

		e.x.m = Cur.X / 85 - 3;
		e.y.m = Cur.Y / 85;

		e.x.r = e.x.m + 1;
		e.x.l = e.x.m - 1;
		e.y.d = e.y.m + 1;
		e.y.u = e.y.m - 1;

		if (Fla.button == 1/*&&Sto.Typ == 0*/)
		{
			int x, y;
			int cou = 0;

			//��
			int same;
			//��
			int diff;

			if (Tur % 2 == 0)
			{
				same = 2;
				diff = 1;
			}
			else
			{
				same = 1;
				diff = 2;
			}

			//�E�ɐ΂��u����Ă��邩�̊m�F
			for (x = e.x.r; x < 9; x++)
			{
				if (Sto.Typ[x][e.y.m] == 0)break;
				else if (Sto.Typ[x][e.y.m] == same)
				{
					for (x = e.x.r; x < e.x.r + cou; x++)
					{
						Sto.Typ[x][e.y.m] = same;
					}break;
				}
				else if (Sto.Typ[x][e.y.m] == diff)cou = cou + 1;
				else break;
			}
				cou = 0;

			//���ɐ΂��u����Ă��邩�̊m�F
			for (x = e.x.l; x > 0; x--)
			{
				if (Sto.Typ[x][e.y.m] == 0)break;
				else if (Sto.Typ[x][e.y.m] == same)
				{
					for (x = e.x.l; x > e.x.l - cou; x--)
					{
						Sto.Typ[x][e.y.m] = same;
					}break;
				}
				else if (Sto.Typ[x][e.y.m] == diff)cou = cou + 1;
				else break;
			}
			cou = 0;

			//���ɐ΂��u����Ă��邩�̊m�F
			for (y = e.y.d; y < 9; y++)
			{
				if (Sto.Typ[e.x.m][y] == 0)break;
				else if (Sto.Typ[e.x.m][y] == same)
				{
					for (y = e.y.d; y < e.y.d + cou; y++)
					{
						Sto.Typ[e.x.m][y] = same;
					}break;
				}
				else if (Sto.Typ[e.x.m][y] == diff)cou = cou + 1;
				else break;
			}
			cou = 0;

			//��ɐ΂��u����Ă��邩�̊m�F
			for (y = e.y.u; y > 0; y--)
			{
				if (Sto.Typ[e.x.m][y] == 0)break;
				else if (Sto.Typ[e.x.m][y] == same)
				{
					for (y = e.y.u; y > e.y.u - cou; y--)
					{
						Sto.Typ[e.x.m][y] = same;
					}break;
				}
				else if (Sto.Typ[e.x.m][y] == diff)cou = cou + 1;
				else break;
			}
			cou = 0;


			//�E��ɐ΂��u����Ă��邩�̊m�F
			for (x = e.x.r, y = e.y.u;
				x < 8, y > 0;
				x++, y--)
			{
				if (Sto.Typ[x][y] == 0)break;
				else if (Sto.Typ[x][y] == same)
				{
					for (x = e.x.r, y = e.y.u;
						x < e.x.r + cou, y > e.y.u - cou;
						x = x++, y = y--)
					{
						Sto.Typ[x][y] = same;
					}break;
				}
				else if (Sto.Typ[x][y] == diff)cou = cou++;
				else break;
			}
			cou = 0;


			//�E���ɐ΂��u����Ă��邩�̊m�F
			for (x = e.x.r, y = e.y.d;
				x < 8, y < 8;
				x++, y++)
			{
				if (Sto.Typ[x][y] == 0)break;
				else if (Sto.Typ[x][y] == same)
				{
					for (x = e.x.r, y = e.y.d;
						x < e.x.r + cou, y < e.y.d + cou;
						x++, y++)
					{
						Sto.Typ[x][y] = same;
					}break;
				}
				else if (Sto.Typ[x][y] == diff)cou = cou++;
				else break;
			}
			cou = 0;

			//����ɐ΂��u����Ă��邩�̊m�F
			for (x = e.x.l, y = e.y.u;
				x > 0, y > 0;
				x--, y--)
			{
				if (Sto.Typ[x][y] == 0)break;
				else if (Sto.Typ[x][y] == same)
				{
					for (x = e.x.l, y = e.y.u;
						x > e.x.r - cou, y > e.y.u - cou;
						x--, y--)
					{
						Sto.Typ[x][y] = same;
					}break;
				}
				else if (Sto.Typ[x][y] == diff)cou = cou++;
				else break;
			}
			cou = 0;


			//�����ɐ΂��u����Ă��邩�̊m�F
			for (x = e.x.l, y = e.y.d;
				x > 0, y < 8;
				x--, y++)
			{
				if (Sto.Typ[x][y] == 0)break;
				else if (Sto.Typ[x][y] == same)
				{
					for (x = e.x.l, y = e.y.d;
						x > e.x.r - cou, y < e.y.d + cou;
						x--, y++)
					{
						Sto.Typ[x][y] = same;
					}break;
				}
				else if (Sto.Typ[x][y] == diff)cou = cou++;
				else break;
			}
			cou = 0;

			// ���u���O�ɗ��Ԃ���΂�����ꍇ
			if (cou > 0 && Sto.Typ[e.x.r][e.y.m] == 0) {
				Sto.Typ[e.x.r][e.y.m] = same; // ���u��
				// ���̑��̏����i���݂̃v���C���[�̐؂�ւ��Ȃǁj
			}
			else {
				// ���Ԃ���΂��Ȃ��ꍇ�A�܂��͋�łȂ��Z���ɋ��u�����Ƃ����ꍇ�A���u���Ȃ�
			}
		}
		
	}

	//�ꎞ��~��
	if (PauseFlg == TRUE)
	{
		if (++PauseFlashTime >= 10)
		{
			PauseFlashFlg = !PauseFlashFlg;
			PauseFlashTime = 0;
		}
	}

	if (Tur>=60)
	{
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_START))
		{
			return new GameSelect;
		}
	}


	return this;
}

void Reversi::Draw() const
{

	int cou_n = 0;
	int cou_b = 0;
	int cou_w = 0;

	DrawGraph(0, 0, BackImg, TRUE);
	//DrawFormatString(0, 100, GetColor(255, 255, 255), " %d:button", Fla.button);
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			DrawGraph(x * 85 + 300, y * 85 + 20, Bac, TRUE);
		}
	}

	for (int y = 0; y < 8;y++)
	{
		for (int x = 0; x < 8; x++)
		{
			switch (Sto.Typ[x][y])
			{
			case 0:
				cou_n = cou_n + 1;
				break;
			case 1: //��
				cou_b = cou_b + 1;
				DrawGraph(Sto.X[x][y], Sto.Y[x][y], Bla, TRUE);
				break;
			case 2: //��
				cou_w = cou_w + 1;
				DrawGraph(Sto.X[x][y], Sto.Y[x][y], Whi, TRUE);
				break;
			}
			
		}
	}

	//�ꎞ��~���̕`��
	if (PauseFlg == TRUE)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		if (PauseFlashFlg == TRUE) {
			DrawString(540, 360, "---�|�[�Y��---", 0x000000, TRUE);
		}
		else {
			DrawString(540, 360, "---�|�[�Y��---", 0xffffff, TRUE);
		}
		DrawString(520, 520, "Start�{�^���ōĊJ", 0xffffff, TRUE);
	}

	DrawBox(Cur.X, Cur.Y, Cur.X + 85, Cur.Y + 85, 0xffffff, FALSE);

	for (int y = 0; y < 8;y++)
	{
		for (int x = 0; x < 8;x++)
		{
			if (Sto.Typ[x][y] == 1) {
				cou_b++;
			}
			else if (Sto.Typ[x][y] == 2) {
				cou_w++;
			}

			if (Tur >= 60)
			{
				if (cou_w < cou_b) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
					DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
					SetFontSize(60);
					DrawString(500, 320, "Black Win!", GetColor(255, 255, 255));
					DrawString(170, 450, "Start�{�^���ŃZ���N�g��ʂɖ߂�", GetColor(255, 255, 255));
				}
				else if (cou_w > cou_b) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
					DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
					SetFontSize(60);
					DrawString(500, 160,"White Win!", GetColor(255, 255, 255));
					DrawString(170, 450, "Start�{�^���ŃZ���N�g��ʂɖ߂�", GetColor(255, 255, 255));

				}
				else {
					DrawFormatString(540, 160, GetColor(255, 255, 255), "Draw");
				}
			}
		}
	}
	/*DrawFormatString(0, 120, GetColor(255, 255, 255), "Cur.X,Cur.Y=(%d,%d)", Cur.X, Cur.Y);
	DrawFormatString(0, 140, GetColor(255, 255, 255), "Tur,%d", Tur);
	DrawFormatString(0, 180, GetColor(255, 255, 255), "Sto.X,%d", Sto.X);
	DrawFormatString(0, 200, GetColor(255, 255, 255), "Sto.Typ,%d", Sto.Typ);
	DrawFormatString(0, 280, GetColor(255, 255, 255), "e.x.m,%d", e.x.m);
	DrawFormatString(0, 300, GetColor(255, 255, 255), "e.y.m,%d", e.y.m);*/

	

	//DrawFormatString(0, 220, GetColor(255, 255, 255), "No,Black,White (%d,%d,%d)", cou_n, cou_b, cou_w);

	/*if (Tur % 2 == 0)
	{
		DrawFormatString(0, 160, GetColor(255, 255, 255), "%dTurn Black", Tur);
	}
	else
	{
		DrawFormatString(0, 160, GetColor(255, 255, 255), "%dTurn White", Tur);
	}*/

	
}


void Reversi::Cursor()
{
	
	//�J�[�\������ړ�������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP) || (PAD_INPUT::GetLStick().ThumbY > 10000 && YOnce == TRUE)) {
		Cur.Y -= 85;
		//�A�����͂��Ȃ��悤�ɂ���
		YOnce = FALSE;

	}
	//�J�[�\�����E�ړ�������
	else if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT) || (PAD_INPUT::GetLStick().ThumbX > 10000 && YOnce == TRUE)) {
		Cur.X += 85;
		//�A�����͂��Ȃ��悤�ɂ���
		YOnce = FALSE;

	}
	//�J�[�\�������ړ�������
	else if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN) || (PAD_INPUT::GetLStick().ThumbY < -10000 && YOnce == TRUE)) {
		Cur.Y += 85;
		//�A�����͂��Ȃ��悤�ɂ���
		YOnce = FALSE;

	}
	//�J�[�\�������ړ�������
	else if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT) || (PAD_INPUT::GetLStick().ThumbX < -10000 && YOnce == TRUE)) {
		Cur.X -= 85;

		//�A�����͂��Ȃ��悤�ɂ���
		YOnce = FALSE;

	}

	//�J�[�\�����Ֆʂ̊O�ɍs���Ȃ��悤�ɂ���
	if (Cur.Y < 20) {
		Cur.Y = 20;
	}
	if (Cur.Y > 615) {
		Cur.Y = 615;
	}
	if (Cur.X < 300) {
		Cur.X = 300;
	}
	if (Cur.X > 895) {
		Cur.X = 895;
	}

}

void Reversi::turn()
{

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		Fla.button = 1;
	}

	for (int y = 0; y < 8; y = y++)
	{
		for (int x = 0; x < 8; x = x++)
		{
			if (Cur.X == 85 * x  + 300 && Cur.Y == 85 * y + 20 &&
				Fla.button == 1 && Sto.Typ[x][y] == 0)
			{
				Tur = Tur + 1;
				Sto.X[x][y] = Cur.X - 10;
				Sto.Y[x][y] = Cur.Y + 5;
				if (Tur % 2 == 0)
				{
					Sto.Typ[x][y] = 2;
				}
				else
				{
					Sto.Typ[x][y] = 1;
				}

			}
		}
	}

}

//void SelectTurn()
//{
//	static int turn = 0;
//	//�J�[�\�����E�ړ�������
//	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
//
//
//	}
//	//�J�[�\�������ړ�������
//	else if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
//
//	}
//
//	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
//	{
//		switch (turn)
//		{
//		case 0:
//			Sto.Typ
//		default:
//			break;
//		}
//	}
//
//	DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
//}

//void Reversi::SelectTurn()
//{
//	//0�Ȃ�v���C���[�̃^�[��
//	PTurn = (GetRand(2) == 0);
//}



