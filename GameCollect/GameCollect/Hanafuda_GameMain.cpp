#include"DxLib.h"
#include"Hanafuda_GameMain.h"
#include"Math.h"
#include"Time.h"
#include"PadInput.h"
#include"stdlib.h"
#include<iostream>

Hanafuda::Hanafuda()
{
	
	Stage = LoadGraph("images/Hanafuda/Background03.png");
	UraImg = LoadGraph("images/Hanafuda/HanafudaCard_Back.png");
	if(LoadDivGraph("images/Hanafuda/HanafudaCard.png", 48,8,6,128,256,FudaImg)){}
	//�\���̂ɎD�̏����i�[�i�摜�A���A�D�̎�ށj
	for (int i = 0; i < 48; i++) {
		Fuda[i].Img = FudaImg[i];
		Fuda[i].month = i / 4 + 1;
		//switch (i) {
		//case 0:
		//case 1:
		//case 2:
		//case 3:
		//	Fuda[i].month = 1;
		//	break;
		//case 4:
		//case 5:
		//case 6:
		//case 7:
		//	Fuda[i].month = 2;
		//	break;
		//case 8:
		//case 9:
		//case 10:
		//case 11:
		//	Fuda[i].month = 3;
		//	break;
		//case 12:
		//case 13:
		//case 14:
		//case 15:
		//	Fuda[i].month = 4;
		//	break;
		//case 16:
		//case 17:
		//case 18:
		//case 19:
		//	Fuda[i].month = 5;
		//	break;
		//case 20:
		//case 21:
		//case 22:
		//case 23:
		//	Fuda[i].month = 6;
		//	break;
		//case 24:
		//case 25:
		//case 26:
		//case 27:
		//	Fuda[i].month = 7;
		//	break;
		//case 28:
		//case 29:
		//case 30:
		//case 31:
		//	Fuda[i].month = 8;
		//case 32:
		//case 33:
		//case 34:
		//case 35:
		//	Fuda[i].month = 9;
		//	break;
		//case 36:
		//case 37:
		//case 38:
		//case 39:
		//	Fuda[i].month = 10;
		//	break;
		//case 40:
		//case 41:
		//case 42:
		//case 43:
		//	Fuda[i].month = 11;
		//	break;
		//case 44:
		//case 45:
		//case 46:
		//case 47:
		//	Fuda[i].month = 12;
		//	break;
		//}
		switch (i) {
		case 0:
		case 1:
		case 4:
		case 5:
		case 8:
		case 9:
		case 12:
		case 13:
		case 16:
		case 17:
		case 20:
		case 21:
		case 24:
		case 25:
		case 28:
		case 29:
		case 32:
		case 33:
		case 36:
		case 37:
		case 40:
		case 44:
		case 45:
		case 46:
			Fuda[i].Kas = TRUE;
			Fuda[i].Tan = FALSE;
			Fuda[i].Tane = FALSE;
			Fuda[i].Hikari = FALSE;
			break;
		case 2:
		case 6:
		case 10:
		case 14:
		case 18:
		case 22:
		case 26:
		case 34:
		case 38:
		case 41:
			Fuda[i].Tan = TRUE;
			Fuda[i].Kas = FALSE;
			Fuda[i].Tane = FALSE;
			Fuda[i].Hikari = FALSE;
			break;
		case 7:
		case 15:
		case 19:
		case 23:
		case 27:
		case 30:
		case 35:
		case 39:
		case 42:
			Fuda[i].Tane = TRUE;
			Fuda[i].Kas = FALSE;
			Fuda[i].Tan = FALSE;
			Fuda[i].Hikari = FALSE;
			break;
		case 3:
		case 11:
		case 31:
		case 43:
		case 47:
			Fuda[i].Hikari = TRUE;
			Fuda[i].Kas = FALSE;
			Fuda[i].Tan = FALSE;
			Fuda[i].Tane = FALSE;
			break;
		}
	}
	//��D���W�̐ݒ�
	Player[0].FudaX = 80;
	Player[0].FudaY = 600;
	for (int i = 1; i < 8; i++) {
		Player[i].FudaX = Player[i - 1].FudaX + 80;
		Player[i].FudaY = 600;
	}
	//�u���D�̍��W�ݒ�(�̂ĎD�Œu���{?���������Ƃ��̂��ߗ]���ɐݒ�j
	Field[0].FudaX = 300;
	Field[0].FudaY = 250;
	Field[4].FudaX = 300;
	Field[4].FudaY = 400;
	for (int i = 1; i < 4; i++)
	{
		Field[i].FudaX = Field[i - 1].FudaX + 80;
		Field[i].FudaY = 250;
	}
	for (int i = 5; i < 8; i++) {
		Field[i].FudaX = Field[i - 1].FudaX + 80;
		Field[i].FudaY = 400;
	}
	//�����̎����D�̍��W�ݒ�i�S�S�i�@����͖̂��ݒ�Ȃ̂Œ����̕K�v������\������j
	//�J�X�D�i�ŉ��i�j
	P_Motifuda.kas[0].x = 905;
	P_Motifuda.kas[0].y = 675;
	for (int i = 1; i < 24; i++) {
		P_Motifuda.kas[i].x = P_Motifuda.kas[i - 1].x + 40;
		P_Motifuda.kas[i].y = 675;
	}
	//�^���D�i������Q�i�ځj6
	P_Motifuda.tan[0].x = 905;
	P_Motifuda.tan[0].y = 595;
	for (int i = 1; i < 10; i++) {
		P_Motifuda.tan[i].x = P_Motifuda.tan[i - 1].x + 40;
		P_Motifuda.tan[i].y = 590;
	}
	//�^�l�D�i�ォ��Q�i�ځj
	P_Motifuda.tane[0].x = 905;
	P_Motifuda.tane[0].y = 515;
	for (int i = 1; i < 9; i++) {
		P_Motifuda.tane[i].x = P_Motifuda.tane[i - 1].x + 40;
		P_Motifuda.tane[i].y = 510;
	}
	//���D�i�ŏ�i�j
	P_Motifuda.hikari[0].x = 905;
	P_Motifuda.hikari[0].y = 435;
	for (int i = 1; i < 5; i++) {
		P_Motifuda.hikari[i].x = P_Motifuda.hikari[i - 1].x + 40;
		P_Motifuda.hikari[i].y = 440;
	}
	torifuda[0].FudaX = 695;
	torifuda[0].FudaY = 250;
	for (int i = 1; i < 8; i++) {
		torifuda[i].FudaX = torifuda[i - 1].FudaX + 30;
		torifuda[i].FudaY = 250;
	}
	// 0�`47�܂ł̒l�����Ɋi�[
	for (int i = 0; i < 48; i++)
	{
		yama[i] = i;
	}
	//�}�E�X���W
	MouseX = 0;
	MouseY = 0;
	OyaGimeflg = 0; //�e���߂̃t���O
	Startflg = 0;
	Judgeflg = 0; //�e���ߗp�t���O
	Playerflg = 0;
	P_judge = 0;
	E_judge = 0;
	Partnerflg = 0;
	shuffleflg = 0;
	Phase = 1;
	Gameflg = 0;
	n = 0;
	j = 0;
	P_shuffleflg = 0;
	E_shuffleflg = 0;
	CursorX = 45; //��D�̑I���D���͂ލ��W
	CursorY = 547;
	CenterX = 80; //�I���D�̒��S���W
	CenterY = 600;
	Judgefuda.Judge = FALSE;
	Judgefuda.month = 0;
	Judgeflg = 0;
	count = 0;
	P_count = 0;
	E_count = 0;
	input_margin = 0;

}
Hanafuda::~Hanafuda()
{
}

AbstractScene* Hanafuda::Update()
{
	GetMousePoint(&MouseX, &MouseY);
	switch (Phase)
	{
	case 0://�e����
	/*	OyaGime();*/
		if (CheckHitKey(KEY_INPUT_0)) {
			Phase = 1;
			tick = 0;
		}
		break;
	case 1: //�D�z�z
		shuffleFuda();
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
			Phase = 2;
		}
		break;
	case 2:
		Oyaban();
	}
	return this;
}
void Hanafuda::Draw()const
{
	DrawGraph(0, 0, Stage, TRUE);
	SetFontSize(12);
	DrawFormatString(1000, 150, GetColor(0, 0, 0), "P_hand:%d", P_count);
	DrawFormatString(1000, 200, GetColor(255, 0, 0), "Phase:%d", Phase);
	DrawFormatString(1000, 100, GetColor(255, 0, 0), "toricount:%d", toricount);
	DrawFormatString(700, 20, GetColor(255, 0, 0), " �}�E�X���W�FX���W %d Y���W %d ", MouseX, MouseY);
	DrawFormatString(700, 480, GetColor(255, 0, 0), "%d��", torifuda[toricount].month);
	DrawFormatString(700, 300, GetColor(255, 0, 0), "stickX:%d", PAD_INPUT::GetLStick().ThumbX);
	switch (Phase)
	{
	case 0: //�e����
		DrawRotaGraph(280, 100, 0.6f, 0, E_fudaImg, FALSE);
		//DrawFormatString(FudaX + 300, FudaY + 120, GetColor(255, 0, 0), "%d��", E_judge);
		DrawRotaGraph(280, 400, 0.7f, 0, P_fudaImg, FALSE);
		/*DrawFormatString(FudaX + 300, FudaY + 420, GetColor(255, 0, 0), "%d��", P_judge);*/
		/*f (Judgeflg == 1)
			DrawFormatString(300, 360, GetColor(255, 0, 0), "���Ȃ����e�i���j�ł�");
		}
		else {
			DrawFormatString(300, 360, GetColor(255, 0, 0), "���肪�e�i���j�ł�");
		}*/
		break;
	case 1://�D�z�z
	case 2:
	case 3:
		//�R�D
		DrawRotaGraph(200, 345, 0.6f, 0, UraImg, TRUE);
		//Player
		if (Player[0].display == TRUE) {
			DrawRotaGraph(Player[0].FudaX, Player[0].FudaY, 0.6f, 0, Player[0].Img, TRUE);
		}
		if (Player[1].display == TRUE) {
			DrawRotaGraph(Player[1].FudaX, Player[1].FudaY, 0.6f, 0, Player[1].Img, TRUE);
		}
		if (Player[2].display == TRUE) {
			DrawRotaGraph(Player[2].FudaX, Player[2].FudaY, 0.6f, 0, Player[2].Img, TRUE);
		}
		if (Player[3].display == TRUE) {
			DrawRotaGraph(Player[3].FudaX, Player[3].FudaY, 0.6f, 0, Player[3].Img, TRUE);
		}
		if (Player[4].display == TRUE) {
			DrawRotaGraph(Player[4].FudaX, Player[4].FudaY, 0.6f, 0, Player[4].Img, TRUE);
		}
		if (Player[5].display == TRUE) {
			DrawRotaGraph(Player[5].FudaX, Player[5].FudaY, 0.6f, 0, Player[5].Img, TRUE);
		}
		if (Player[6].display == TRUE) {
			DrawRotaGraph(Player[6].FudaX, Player[6].FudaY, 0.6f, 0, Player[6].Img, TRUE);
		}
		if (Player[7].display == TRUE) {
			DrawRotaGraph(Player[7].FudaX, Player[7].FudaY, 0.6f, 0, Player[7].Img, TRUE);
		}
		DrawFormatString(80, 500, GetColor(255, 255, 255), "%d", Player[0].month);
		//Enemy
		if (Enemy[0].display == TRUE) {
			DrawRotaGraph(80, 100, 0.6f, 0, Enemy[0].Img, TRUE);
		}
		if (Enemy[1].display == TRUE) {
			DrawRotaGraph(160, 100, 0.6f, 0, Enemy[1].Img, TRUE);
		}
		if (Enemy[2].display == TRUE) {
			DrawRotaGraph(240, 100, 0.6f, 0, Enemy[2].Img, TRUE);
		}
		if (Enemy[3].display == TRUE) {
			DrawRotaGraph(320, 100, 0.6f, 0, Enemy[3].Img, TRUE);
		}
		if (Enemy[4].display == TRUE) {
			DrawRotaGraph(400, 100, 0.6f, 0, Enemy[4].Img, TRUE);
		}
		if (Enemy[5].display == TRUE) {
			DrawRotaGraph(480, 100, 0.6f, 0, Enemy[5].Img, TRUE);
		}
		if (Enemy[6].display == TRUE) {
			DrawRotaGraph(560, 100, 0.6f, 0, Enemy[6].Img, TRUE);
		}
		if (Enemy[7].display == TRUE) {
			DrawRotaGraph(640, 100, 0.6f, 0, Enemy[7].Img, TRUE);
		}
		for (int x = 0; x <= F_count; x++) {
				DrawRotaGraph(Field[F_count].FudaX, Field[F_count].FudaY, 0.6f, 0, Field[F_count].Img, TRUE);
		}
		//Field��
		if (Field[0].diplay == TRUE) {
			DrawRotaGraph(Field[0].FudaX, Field[0].FudaY, 0.6f, 0, Field[0].Img, TRUE);
		}
		if (Field[1].diplay == TRUE) {
			DrawRotaGraph(Field[1].FudaX, Field[1].FudaY, 0.6f, 0, Field[1].Img, TRUE);
		}
		if (Field[2].diplay == TRUE) {
			DrawRotaGraph(Field[2].FudaX, Field[2].FudaY, 0.6f, 0, Field[2].Img, TRUE);
		}
		if (Field[3].diplay == TRUE) {
			DrawRotaGraph(Field[3].FudaX, Field[3].FudaY, 0.6f, 0, Field[3].Img, TRUE);
		}
		if (Field[4].diplay == TRUE) {
			DrawRotaGraph(Field[4].FudaX, Field[4].FudaY, 0.6f, 0, Field[4].Img, TRUE);
		}
		if (Field[5].diplay == TRUE) {
			DrawRotaGraph(Field[5].FudaX, Field[5].FudaY, 0.6f, 0, Field[5].Img, TRUE);
		}
		if (Field[6].diplay == TRUE) {
			DrawRotaGraph(Field[6].FudaX, Field[6].FudaY, 0.6f, 0, Field[6].Img, TRUE);
		}
		if (Field[7].diplay == TRUE) {
			DrawRotaGraph(Field[7].FudaX, Field[7].FudaY, 0.6f, 0, Field[7].Img, TRUE);
		}
		//�D�I��
		/*if (Cursor == TRUE) {*/
			DrawBox(CursorX, CursorY, CursorX + 70, CursorY + 110, GetColor(255, 0, 0), FALSE);
			DrawCircle(CenterX, CenterY, 20, GetColor(0, 0, 255), TRUE);
		//}
	}
	if (Judgefuda.Judge == TRUE) {
		//DrawBox(Judgefuda.judgeX - 35, Judgefuda.judgeY - 55, Judgefuda.judgeX + 35, Judgefuda.judgeY + 55, GetColor(0, 255, 0), FALSE);
		DrawRotaGraph(700, 400, 0.6f, 0, Judgefuda.Img, TRUE);
	}
 	if (yamafuda.draw == TRUE) {
		DrawRotaGraph(250, 345, 0.6f, 0, yamafuda.Img, TRUE);
	}
	if (torifuda[1].display == TRUE) {
		//DrawBox(torifuda[0].FudaX - 35, torifuda[0].FudaY - 55, torifuda[0].FudaX + 35, torifuda[0].FudaY + 55, GetColor(0, 0, 255), FALSE);
		DrawRotaGraph(torifuda[0].FudaX, torifuda[0].FudaY, 0.6f, 0, torifuda[1].Img, TRUE);
	}
	if (torifuda[2].display == TRUE) {
		//DrawBox(torifuda[2].FudaX - 35, torifuda[2].FudaY - 55, torifuda[2].FudaX + 35, torifuda[2].FudaY + 55, GetColor(0, 0, 255), FALSE);
		DrawRotaGraph(torifuda[2].FudaX, torifuda[2].FudaY, 0.6f, 0, torifuda[2].Img, TRUE);
	}
	if (torifuda[3].display == TRUE) {
		//DrawBox(torifuda[3].FudaX - 35, torifuda[3].FudaY - 55, torifuda[3].FudaX + 35, torifuda[3].FudaY + 55, GetColor(0, 0, 255), FALSE);
		DrawRotaGraph(torifuda[3].FudaX, torifuda[3].FudaY, 0.6f, 0, torifuda[3].Img, TRUE);
	}

	////���D�̎����D�\��
	/*if (P_Motifuda.hikari[0].display == TRUE) {*/
		DrawRotaGraph(P_Motifuda.hikari[0].x, P_Motifuda.hikari[0].y, 0.5f, 0, P_Motifuda.hikari[0].Img, TRUE);
		DrawRotaGraph(P_Motifuda.hikari[1].x, P_Motifuda.hikari[1].y, 0.5f, 0, P_Motifuda.hikari[1].Img, TRUE);
		DrawRotaGraph(P_Motifuda.hikari[2].x, P_Motifuda.hikari[2].y, 0.5f, 0, P_Motifuda.hikari[2].Img, TRUE);
		DrawRotaGraph(P_Motifuda.hikari[3].x, P_Motifuda.hikari[3].y, 0.5f, 0, P_Motifuda.hikari[3].Img, TRUE);
		DrawRotaGraph(P_Motifuda.hikari[4].x, P_Motifuda.hikari[4].y, 0.5f, 0, P_Motifuda.hikari[4].Img, TRUE);

	//}
	//if (P_Motifuda.hikari[1].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.hikari[1].x, P_Motifuda.hikari[1].y, 0.5f, 0, P_Motifuda.hikari[1].Img, TRUE);
	//}
	//if (P_Motifuda.hikari[2].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.hikari[2].x, P_Motifuda.hikari[2].y, 0.5f, 0, P_Motifuda.hikari[2].Img, TRUE);
	//}
	//if (P_Motifuda.hikari[3].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.hikari[3].x, P_Motifuda.hikari[3].y, 0.5f, 0, P_Motifuda.hikari[3].Img, TRUE);
	//}
	//if (P_Motifuda.hikari[4].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.hikari[4].x, P_Motifuda.hikari[4].y, 0.5f, 0, P_Motifuda.hikari[4].Img, TRUE);
	//}
	//�^�l�D�̎����D�\��
	//if (P_Motifuda.tane[0].display == TRUE) {
		DrawRotaGraph(P_Motifuda.tane[0].x, P_Motifuda.tane[0].y, 0.5f, 0, P_Motifuda.tane[0].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tane[1].x, P_Motifuda.tane[0].y, 0.5f, 0, P_Motifuda.tane[1].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tane[2].x, P_Motifuda.tane[0].y, 0.5f, 0, P_Motifuda.tane[2].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tane[3].x, P_Motifuda.tane[0].y, 0.5f, 0, P_Motifuda.tane[3].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tane[4].x, P_Motifuda.tane[0].y, 0.5f, 0, P_Motifuda.tane[4].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tane[5].x, P_Motifuda.tane[0].y, 0.5f, 0, P_Motifuda.tane[5].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tane[6].x, P_Motifuda.tane[0].y, 0.5f, 0, P_Motifuda.tane[6].Img, TRUE);
	//}
	//if (P_Motifuda.tane[1].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.tane[1].x, P_Motifuda.tane[1].y, 0.5f, 0, P_Motifuda.tane[1].Img, TRUE);
	//}
	//if (P_Motifuda.tane[2].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.tane[2].x, P_Motifuda.tane[2].y, 0.5f, 0, P_Motifuda.tane[2].Img, TRUE);
	//}
	//if (P_Motifuda.tane[3].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.tane[3].x, P_Motifuda.tane[3].y, 0.5f, 0, P_Motifuda.tane[3].Img, TRUE);
	//}
	//if (P_Motifuda.tane[4].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.tane[4].x, P_Motifuda.tane[4].y, 0.5f, 0, P_Motifuda.tane[4].Img, TRUE);
	//}
	//if (P_Motifuda.tane[5].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.tane[5].x, P_Motifuda.tane[5].y, 0.5f, 0, P_Motifuda.tane[5].Img, TRUE);
	//}
	//if (P_Motifuda.tane[6].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.tane[6].x, P_Motifuda.tane[6].y, 0.5f, 0, P_Motifuda.tane[6].Img, TRUE);
	//}
	//if (P_Motifuda.tane[7].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.tane[7].x, P_Motifuda.tane[7].y, 0.5f, 0, P_Motifuda.tane[7].Img, TRUE);
	//}
	//if (P_Motifuda.tane[8].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.tane[8].x, P_Motifuda.tane[8].y, 0.5f, 0, P_Motifuda.tane[8].Img, TRUE);
	//}
	//�^���D�̕\��
	//if (P_Motifuda.tan[0].display == TRUE) {
		DrawRotaGraph(P_Motifuda.tan[0].x, P_Motifuda.tan[0].y, 0.5f, 0, P_Motifuda.tan[0].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tan[1].x, P_Motifuda.tan[1].y, 0.5f, 0, P_Motifuda.tan[1].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tan[2].x, P_Motifuda.tan[2].y, 0.5f, 0, P_Motifuda.tan[2].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tan[3].x, P_Motifuda.tan[3].y, 0.5f, 0, P_Motifuda.tan[3].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tan[4].x, P_Motifuda.tan[4].y, 0.5f, 0, P_Motifuda.tan[4].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tan[5].x, P_Motifuda.tan[5].y, 0.5f, 0, P_Motifuda.tan[5].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tan[6].x, P_Motifuda.tan[6].y, 0.5f, 0, P_Motifuda.tan[6].Img, TRUE);
		

	//}
	//if (P_Motifuda.tan[1].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.tan[1].x, P_Motifuda.tan[1].y, 0.5f, 0, P_Motifuda.tan[1].Img, TRUE);
	//}
	//if (P_Motifuda.tan[2].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.tan[2].x, P_Motifuda.tan[2].y, 0.5f, 0, P_Motifuda.tan[2].Img, TRUE);
	//}
	//if (P_Motifuda.tan[3].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.tan[3].x, P_Motifuda.tan[3].y, 0.5f, 0, P_Motifuda.tan[3].Img, TRUE);
	//}
	//if (P_Motifuda.tan[4].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.tan[4].x, P_Motifuda.tan[4].y, 0.5f, 0, P_Motifuda.tan[4].Img, TRUE);
	//}
	//if (P_Motifuda.tan[5].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.tan[5].x, P_Motifuda.tan[5].y, 0.5f, 0, P_Motifuda.tan[5].Img, TRUE);
	//}
	//if (P_Motifuda.tan[5].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.tan[5].x, P_Motifuda.tan[5].y, 0.5f, 0, P_Motifuda.tan[5].Img, TRUE);
	//}
	//if (P_Motifuda.tan[6].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.tan[6].x, P_Motifuda.tan[6].y, 0.5f, 0, P_Motifuda.tan[6].Img, TRUE);
	//}
	//if (P_Motifuda.tan[7].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.tan[7].x, P_Motifuda.tan[7].y, 0.5f, 0, P_Motifuda.tan[7].Img, TRUE);
	//}
	//if (P_Motifuda.tan[8].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.tan[8].x, P_Motifuda.tan[8].y, 0.5f, 0, P_Motifuda.tan[8].Img, TRUE);
	//}
	//if (P_Motifuda.tan[9].display == TRUE) {
	//	DrawRotaGraph(P_Motifuda.tan[9].x, P_Motifuda.tan[9].y, 0.5f, 0, P_Motifuda.tan[9].Img, TRUE);
	//}
	//�J�X�D�̕\��
	/*if (P_Motifuda.kas[0].display == TRUE) {
			DrawRotaGraph(P_Motifuda.kas[0].x, P_Motifuda.kas[0].y, 0.5f, 0, P_Motifuda.kas[0].Img, TRUE);
	}
	if (P_Motifuda.kas[1].display == TRUE) {
		DrawRotaGraph(P_Motifuda.kas[1].x, P_Motifuda.kas[1].y, 0.5f, 0, P_Motifuda.kas[1].Img, TRUE);
	}
	if (P_Motifuda.kas[2].display == TRUE) {
		DrawRotaGraph(P_Motifuda.kas[2].x, P_Motifuda.kas[2].y, 0.5f, 0, P_Motifuda.kas[2].Img, TRUE);
	}
	if (P_Motifuda.kas[3].display == TRUE) {
		DrawRotaGraph(P_Motifuda.kas[3].x, P_Motifuda.kas[3].y, 0.5f, 0, P_Motifuda.kas[3].Img, TRUE);
	}
	if (P_Motifuda.kas[4].display == TRUE) {
		DrawRotaGraph(P_Motifuda.kas[4].x, P_Motifuda.kas[4].y, 0.5f, 0, P_Motifuda.kas[4].Img, TRUE);
	}
	if (P_Motifuda.kas[5].display == TRUE) {
		DrawRotaGraph(P_Motifuda.kas[5].x, P_Motifuda.kas[5].y, 0.5f, 0, P_Motifuda.kas[5].Img, TRUE);
	}
	if (P_Motifuda.kas[6].display == TRUE) {
		DrawRotaGraph(P_Motifuda.kas[6].x, P_Motifuda.kas[6].y, 0.5f, 0, P_Motifuda.kas[6].Img, TRUE);
	}
	if (P_Motifuda.kas[7].display == TRUE) {
		DrawRotaGraph(P_Motifuda.kas[7].x, P_Motifuda.kas[7].y, 0.5f, 0, P_Motifuda.kas[7].Img, TRUE);
	}
	if (P_Motifuda.kas[8].display == TRUE) {
		DrawRotaGraph(P_Motifuda.kas[8].x, P_Motifuda.kas[8].y, 0.5f, 0, P_Motifuda.kas[8].Img, TRUE);
	}
	if (P_Motifuda.kas[9].display == TRUE) {
		DrawRotaGraph(P_Motifuda.kas[9].x, P_Motifuda.kas[9].y, 0.5f, 0, P_Motifuda.kas[9].Img, TRUE);
	}*/
	DrawRotaGraph(P_Motifuda.kas[0].x, P_Motifuda.kas[0].y, 0.5f, 0, P_Motifuda.kas[0].Img, TRUE);
	DrawRotaGraph(P_Motifuda.kas[1].x, P_Motifuda.kas[1].y, 0.5f, 0, P_Motifuda.kas[1].Img, TRUE);
	DrawRotaGraph(P_Motifuda.kas[2].x, P_Motifuda.kas[2].y, 0.5f, 0, P_Motifuda.kas[2].Img, TRUE);
	DrawRotaGraph(P_Motifuda.kas[3].x, P_Motifuda.kas[3].y, 0.5f, 0, P_Motifuda.kas[3].Img, TRUE);
	DrawRotaGraph(P_Motifuda.kas[4].x, P_Motifuda.kas[4].y, 0.5f, 0, P_Motifuda.kas[4].Img, TRUE);
	DrawRotaGraph(P_Motifuda.kas[5].x, P_Motifuda.kas[5].y, 0.5f, 0, P_Motifuda.kas[5].Img, TRUE);
	DrawRotaGraph(P_Motifuda.kas[6].x, P_Motifuda.kas[6].y, 0.5f, 0, P_Motifuda.kas[6].Img, TRUE);
	DrawRotaGraph(P_Motifuda.kas[7].x, P_Motifuda.kas[7].y, 0.5f, 0, P_Motifuda.kas[7].Img, TRUE);
	DrawRotaGraph(P_Motifuda.kas[8].x, P_Motifuda.kas[8].y, 0.5f, 0, P_Motifuda.kas[8].Img, TRUE);
	DrawRotaGraph(P_Motifuda.kas[9].x, P_Motifuda.kas[9].y, 0.5f, 0, P_Motifuda.kas[9].Img, TRUE);
	DrawRotaGraph(P_Motifuda.kas[10].x, P_Motifuda.kas[10].y, 0.5f, 0, P_Motifuda.kas[10].Img, TRUE);
	DrawRotaGraph(P_Motifuda.kas[11].x, P_Motifuda.kas[11].y, 0.5f, 0, P_Motifuda.kas[11].Img, TRUE);

}
//�e����
void Hanafuda:: OyaGime()
{
	tick++;
	if (OyaGimeflg == 0 && tick == 1) {
		srand(time(NULL));
		int num = rand() % 47;
		E_fudaImg = Fuda[num].Img;
		int n = rand() % 47;
		P_fudaImg = Fuda[n].Img;
		OyaGimeflg = 1;
	}
}
void Hanafuda::Init()
{
	SRand(time(NULL));
	// �V���b�t��
	for (int i = 48 - 1; i > 0; i--)
	{
		int s = GetRand(i);

		int temp = yama[i];
		yama[i] = yama[s];
		yama[s] = temp;
	}
}

//�D�z�z  
void Hanafuda::shuffleFuda()
{
	Init(); //�z����V���b�t��
	if (CheckHitKey(KEY_INPUT_1) || PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		// ��ɔz�u
		int s = 0;
		for (x = 0; x < GAME_FUDA; x++) {
			Field[s].Img = Fuda[yama[x]].Img;
			Field[s].month = Fuda[yama[x]].month;
			Field[s].Hikari = Fuda[yama[x]].Hikari;
			Field[s].Tane = Fuda[yama[x]].Tane;
			Field[s].Tan = Fuda[yama[x]].Tan;
			Field[s].Kas = Fuda[yama[x]].Kas;
			Field[s].diplay = TRUE;
			F_count++;
			s++;
		}
		// �v���C���[�ɔz�z
		int t = x;
		s = 0;
		for (; x < (t + GAME_FUDA); x++)
		{
			Player[s].Img = Fuda[yama[x]].Img;
			Player[s].month = Fuda[yama[x]].month;
			Player[s].Hikari = Fuda[yama[x]].Hikari;
			Player[s].Tane = Fuda[yama[x]].Tane;
			Player[s].Tan = Fuda[yama[x]].Tan;
			Player[s].Kas = Fuda[yama[x]].Kas;
			Player[s].display = TRUE;
			P_count++;
			s++;
		}
		// �G�ɔz�z
		t = x;
		s = 0;
		for (; x < (t + GAME_FUDA); x++)
		{
			Enemy[s].Img = Fuda[yama[x]].Img;
			Enemy[s].month = Fuda[yama[x]].month;
			Enemy[s].Hikari = Fuda[yama[x]].Hikari;
			Enemy[s].Tane = Fuda[yama[x]].Tane;
			Enemy[s].Tan = Fuda[yama[x]].Tan;
			Enemy[s].Kas = Fuda[yama[x]].Kas;
			Enemy[s].display = TRUE;
			E_count++;
			s++;
		}
	}
}
//���
void Hanafuda::Oyaban()  //���Ԃ̎��̏��� ��D��I�ԁ���Ɣ��聨���D���̂ĎD�����肷��
{
	i = 0;
	// ����Ԋu����
	stick_x = PAD_INPUT::GetLStick().ThumbX;
	const int max_input_margin = 10;
	// �X�e�B�b�N�̊��x
	const int stick_sensitivity = 20000;
	select = 0;
	MoveCursor = TRUE;

	Tefudalocation();
	//Cursor = TRUE;
	if (input_margin < max_input_margin) {
		input_margin++;
	}
	else {
		// �X�e�B�b�N��Y���W���擾
		if (std::abs(stick_x) > stick_sensitivity) {
			// �X�e�B�b�N���E�Ɉړ������ꍇ
			if (stick_x > 0 && MoveCursor == TRUE) {
				CursorX += 80;
				CenterX += 80;
			}
			// �X�e�B�b�N�����Ɉړ������ꍇ
			else if (stick_x < 0 && MoveCursor == TRUE) {
				CursorX -= 80;
				CenterX -= 80;
			}
			if (CenterX < 45) {
				CursorX = 45;
				CenterX = 80;
			}
			if (CenterX > 640) {
				CursorX = 605;
				CenterX = 640;

			}
		}
		input_margin = 0;
	}
}
//��D����ǂ��������
void Hanafuda::Tefudalocation() 
{
	if (CenterX > 45 && CenterX < 115) { //�P����
		i = 1;
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)){
			if (CenterX < 80 || CenterX > 80){
				CursorX = 45;//�I��������J�[�\���𓮂����Ȃ��悤�ɂ���
			}
			MoveCursor = FALSE;
			Judgefuda.Img = Player[0].Img;
			Judgefuda.month = Player[0].month;
			Judgefuda.Hikari = Player[0].Hikari;
			Judgefuda.Tan = Player[0].Tan;
			Judgefuda.Tane = Player[0].Tane;
			Judgefuda.Kas = Player[0].Kas;
			Judgefuda.Judge = 1;
			P_draw = TRUE;
			count = 0;
			location();
		}
	}
	else if (CenterX > 125 && CenterX < 195) { //�Q����
		i = 2;
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {
			if (CursorX < 0 && stick_x > 0) {
				CursorX = 45;
			}
			Judgefuda.Img = Player[1].Img;
			Judgefuda.month = Player[1].month;
			Judgefuda.Hikari = Player[1].Hikari;
			Judgefuda.Tan = Player[1].Tan;
			Judgefuda.Tane = Player[1].Tane;
			Judgefuda.Kas = Player[1].Kas;
			Judgefuda.Judge = 1;
			P_draw = TRUE;
			count = 0;
			location();
		}
	}
	else if (CenterX > 215 && CenterX < 275) { //�R����
		i = 3;
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {
			Judgefuda.Img = Player[2].Img;
			Judgefuda.month = Player[2].month;
			Judgefuda.Hikari = Player[2].Hikari;
			Judgefuda.Tan = Player[2].Tan;
			Judgefuda.Tane = Player[2].Tane;
			Judgefuda.Kas = Player[2].Kas;
			Judgefuda.Judge = 1;
			P_draw = TRUE;
			count = 0;
			location();
		}
	}
	else if (CenterX > 285 && CenterX < 355) { //�S����
		i = 4;
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {
			Judgefuda.Img = Player[3].Img;
			Judgefuda.month = Player[3].month;
			Judgefuda.Hikari = Player[3].Hikari;
			Judgefuda.Tan = Player[3].Tan;
			Judgefuda.Tane = Player[3].Tane;
			Judgefuda.Kas = Player[3].Kas;
			Judgefuda.Judge = 1;
			P_draw = TRUE;
			count = 0;
			location();
		}
	}
	else if (CenterX > 365 && CenterX < 435) { //�T����
		i = 5;
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {
			Judgefuda.Img = Player[4].Img;
			Judgefuda.month = Player[4].month;
			Judgefuda.Hikari = Player[4].Hikari;
			Judgefuda.Tan = Player[4].Tan;
			Judgefuda.Tane = Player[4].Tane;
			Judgefuda.Kas = Player[4].Kas;
			Judgefuda.Judge = 1;
			P_draw = TRUE;
			count = 0;
			location();
		}
	}
	else if (CenterX > 445 && CenterX < 515) { //�U����
		i = 6;
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {
			Judgefuda.Img = Player[5].Img;
			Judgefuda.month = Player[5].month;
			Judgefuda.Hikari = Player[5].Hikari;
			Judgefuda.Tan = Player[5].Tan;
			Judgefuda.Tane = Player[5].Tane;
			Judgefuda.Kas = Player[5].Kas;
			Judgefuda.Judge = 1;
			P_draw = TRUE;
			count = 0;
			location();
		}
	}
	else if (CenterX > 525 && CenterX < 595) { //�V����
		i = 7;
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {
			Judgefuda.Img = Player[6].Img;
			Judgefuda.month = Player[6].month;
			Judgefuda.Hikari = Player[6].Hikari;
			Judgefuda.Tane = Player[6].Tane;
			Judgefuda.Tan = Player[6].Tan;
			Judgefuda.Kas = Player[6].Kas;
			Judgefuda.Judge = 1;
			P_draw = TRUE;
			count = 0;
			location();
		}
	}
	else if (CenterX > 605 && CenterX < 675) { //�W����
		i = 8;
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {
			Judgefuda.Img = Player[7].Img;
			Judgefuda.month = Player[7].month;
			Judgefuda.Hikari = Player[7].Hikari;
			Judgefuda.Tan = Player[7].Tan;
			Judgefuda.Tane = Player[7].Tane;
			Judgefuda.Kas = Player[7].Kas;
			Judgefuda.Judge = 1;
			P_draw = TRUE;
			count = 0;
			location();
		}
	}
	if (P_draw == TRUE && PAD_INPUT::OnButton(XINPUT_BUTTON_Y))
	{
		Hiku();
	}
}
//��Ɏ��D�����邩
void Hanafuda::location()
{
	int a = 0;
	switch (count) {
	case 0:
		a = 0;
		//���D�̃J�E���g��0��
		toricount = 0; 
		//��D����o�����Ƃ��i��Ɏ��镨���������������p�̏C���K�v�j
		do {
			for (j = 0; j < F_count; j++) {
				if (Judgefuda.month == Field[j].month) {
					torifuda[toricount].Img = Judgefuda.Img; //toricount��0
					torifuda[toricount].month = Judgefuda.month;
					torifuda[toricount].Hikari = Judgefuda.Hikari;
					torifuda[toricount].Tane = Judgefuda.Tane;
					torifuda[toricount].Tan = Judgefuda.Tan;
					torifuda[toricount].Kas = Judgefuda.Kas;
					torifuda[toricount].display = TRUE;
					toricount += 1;
					torifuda[toricount].Img = Field[j].Img; //toricount�͂P�ȏ�ɂ���
					torifuda[toricount].month = Field[j].month;
					torifuda[toricount].Hikari = Field[j].Hikari;
					torifuda[toricount].Tane = Field[j].Tane;
					torifuda[toricount].Tan = Field[j].Tan;
					torifuda[toricount].Kas = Field[j].Kas;
					torifuda[toricount].display = TRUE;
					toricount += 1;
					P_count -= 1;

				}
				else {
					a += 1; //��ɂ���D�����[�v�����̃J�E���g�@a����ɂ���D���J�E���g�����Ǝ̂ĎD
				}
			}
		} while (j < F_count);
		//�̂ĎD
		if (a == F_count) {
			F_count++;
			Field[F_count].Img = Judgefuda.Img;
			Field[F_count].month = Judgefuda.month;
			Field[F_count].Hikari = Judgefuda.Hikari;
			Field[F_count].Tane = Judgefuda.Tane;
			Field[F_count].Tan = Judgefuda.Tan;
			Field[F_count].Kas = Judgefuda.Kas;
			P_count -= 1;
		}
	case 1:
		//�R�D����o�����Ƃ�
		a = 0;
			do {		//��D����o�����Ƃ��i��Ɏ��镨���������������p�̏C���K�v�j
				for (j = 0; j < F_count; j++) {
					if (yamafuda.month == Field[j].month) 
					{
						torifuda[toricount].Img = Field[j].Img;
						torifuda[toricount].month = Field[j].month;
						torifuda[toricount].Hikari = Field[j].Hikari;
						torifuda[toricount].Tane = Field[j].Tane;
						torifuda[toricount].Tan = Field[j].Tan;
						torifuda[toricount].Kas = Field[j].Kas;
						torifuda[toricount].display = TRUE;
						toricount += 1;
						torifuda[toricount].Img = yamafuda.Img;
						torifuda[toricount].month = yamafuda.month;
						torifuda[toricount].Hikari = yamafuda.Hikari;
						torifuda[toricount].Tane = yamafuda.Tane;
						torifuda[toricount].Tan = yamafuda.Tan;
						torifuda[toricount].Kas = yamafuda.Kas;
						torifuda[toricount].display = TRUE;
						toricount += 1;
					}
					else{
						a += 1;

					}
				}
			} while (j < F_count);
		toricount = 0;
		Moveflg = TRUE;
		if (a == F_count) {
			F_count += 1;
			Field[F_count].Img = yamafuda.Img;
			Field[F_count].month = yamafuda.month;
			Field[F_count].Hikari = yamafuda.Hikari;
			Field[F_count].Tane = yamafuda.Tane;
			Field[F_count].Tan = yamafuda.Tan;
			Field[F_count].Kas = yamafuda.Kas;
		}
		break;
	}
}
//�R�D����������Ƃ�
void Hanafuda::Hiku(){ 
	yamafuda.Img = Fuda[yama[x]].Img;
	yamafuda.month = Fuda[yama[x]].month;
	yamafuda.Kas = Fuda[yama[x]].Kas;
	yamafuda.Tan = Fuda[yama[x]].Tan;
	yamafuda.Tane = Fuda[yama[x]].Tane;
	yamafuda.Hikari = Fuda[yama[x]].Hikari;
	
	count = 1;
	yamafuda.draw = TRUE;
	location();
	if (Moveflg == TRUE && PAD_INPUT::OnButton(XINPUT_BUTTON_Y)) {
		Move();
	}
}
//���D�������D�Ɉړ�
void Hanafuda::Move() { 
	//���D
	if (torifuda[0].Hikari == TRUE && P_Motifuda.hikari_count < 4) {
		P_Motifuda.hikari[P_Motifuda.hikari_count].Img = torifuda[0].Img;
		torifuda[0].Img = 0;
		P_Motifuda.hikari[0].display = TRUE;
		P_Motifuda.hikari_count += 1;
	}
	if (torifuda[1].Hikari == TRUE && P_Motifuda.hikari_count < 4) {
		P_Motifuda.hikari[P_Motifuda.hikari_count].Img = torifuda[1].Img;
		torifuda[1].Img = 0;
		P_Motifuda.hikari[P_Motifuda.hikari_count].display = TRUE;
		P_Motifuda.hikari_count += 1;
	}
	 if (torifuda[2].Hikari == TRUE && P_Motifuda.hikari_count < 4) {
		P_Motifuda.hikari[P_Motifuda.hikari_count].Img = torifuda[2].Img;
		torifuda[2].Img = 0;
		P_Motifuda.hikari[P_Motifuda.hikari_count].display = TRUE;
		P_Motifuda.hikari_count += 1;
	 }
	 if (torifuda[3].Hikari == TRUE && P_Motifuda.hikari_count < 4) {
		P_Motifuda.hikari[P_Motifuda.hikari_count].Img = torifuda[3].Img;
		torifuda[3].Img = 0;
		P_Motifuda.hikari[P_Motifuda.hikari_count].display = TRUE;
		P_Motifuda.hikari_count += 1;
	}
	 if (torifuda[4].Hikari == TRUE && P_Motifuda.hikari_count < 4) {
		P_Motifuda.hikari[P_Motifuda.hikari_count].Img = torifuda[4].Img;
		torifuda[4].Img = 0;
		P_Motifuda.hikari[P_Motifuda.hikari_count].display = TRUE;
		P_Motifuda.hikari_count += 1;
	}
	 if (torifuda[5].Hikari == TRUE && P_Motifuda.hikari_count < 4) {
		P_Motifuda.hikari[P_Motifuda.hikari_count].Img = torifuda[5].Img;
		torifuda[5].Img = 0;
		P_Motifuda.hikari[P_Motifuda.hikari_count].display = TRUE;
		P_Motifuda.hikari_count += 1;
	 }
	 if (torifuda[6].Hikari == TRUE && P_Motifuda.hikari_count < 4) {
		P_Motifuda.hikari[P_Motifuda.hikari_count].Img = torifuda[6].Img;
		torifuda[6].Img = 0;
		P_Motifuda.hikari[P_Motifuda.hikari_count].display = TRUE;
		P_Motifuda.hikari_count += 1;
	}
	 if (torifuda[7].Hikari == TRUE && P_Motifuda.hikari_count < 4) {
		P_Motifuda.hikari[P_Motifuda.hikari_count].Img = torifuda[7].Img;
		torifuda[7].Img = 0;
		P_Motifuda.hikari[P_Motifuda.hikari_count].display = TRUE;
		P_Motifuda.hikari_count += 1;
	}
	//�^�l�D
	if (torifuda[0].Tane == TRUE) {
		P_Motifuda.tane[P_Motifuda.tane_count].Img = torifuda[0].Img;
		torifuda[0].Img = 0;
		P_Motifuda.tane[P_Motifuda.tane_count].display = TRUE;
		P_Motifuda.tane_count += 1;
	}
	 if (torifuda[1].Tane == TRUE) {
		 P_Motifuda.tane[P_Motifuda.tane_count].Img = torifuda[1].Img;
		torifuda[1].Img = 0;
		P_Motifuda.tane[P_Motifuda.tane_count].display = TRUE;
		P_Motifuda.tane_count += 1;
	}
	 if (torifuda[2].Tane == TRUE) {
		P_Motifuda.tane[P_Motifuda.tane_count].Img = torifuda[2].Img;
		torifuda[2].Img = 0;
		P_Motifuda.tane[P_Motifuda.tane_count].display = TRUE;
		P_Motifuda.tane_count += 1;
	}
	 if (torifuda[3].Tane == TRUE) {
		P_Motifuda.tane[P_Motifuda.tane_count].Img = torifuda[3].Img;
		torifuda[3].Img = 0;
		P_Motifuda.tane[3].display = TRUE;
		P_Motifuda.tane_count += 1;
	}
	 if (torifuda[4].Tane == TRUE) {
		P_Motifuda.tane[P_Motifuda.tane_count].Img = torifuda[4].Img;
		torifuda[4].Img = 0;
		P_Motifuda.tane[P_Motifuda.tane_count].display = TRUE;
		P_Motifuda.tane_count += 1;
	}
	 if (torifuda[5].Tane == TRUE) {
		 P_Motifuda.tane[P_Motifuda.tane_count].Img = torifuda[5].Img;
		torifuda[5].Img = 0;
		P_Motifuda.tane[P_Motifuda.tane_count].display = TRUE;
		P_Motifuda.tane_count += 1;
	}
	 if (torifuda[6].Tane == TRUE) {
		P_Motifuda.tane[6].Img = torifuda[6].Img;
		torifuda[6].Img = 0;
		P_Motifuda.tane[P_Motifuda.tane_count].display = TRUE;
		P_Motifuda.tane_count += 1;
	}
	 if (torifuda[7].Tane == TRUE) {
		P_Motifuda.tane[P_Motifuda.tane_count].Img = torifuda[7].Img;
		torifuda[7].Img = 0;
		P_Motifuda.tane[P_Motifuda.tane_count].display = TRUE;
		P_Motifuda.tane_count += 1;
	}
	//�^��
	if (torifuda[0].Tan == TRUE) {
		P_Motifuda.tan[P_Motifuda.tan_count].Img = torifuda[0].Img;
		P_Motifuda.tan_count += 1;
		P_Motifuda.tan[P_Motifuda.tan_count].display = TRUE;
		torifuda[0].Img = 0;
	}
	 if (torifuda[1].Tan == TRUE) {
		P_Motifuda.tan[P_Motifuda.tan_count].Img = torifuda[1].Img;
		P_Motifuda.tan_count += 1;
		P_Motifuda.tan[P_Motifuda.tan_count].display = TRUE;
		torifuda[1].Img = 0;
	}
	 if (torifuda[2].Tan == TRUE) {
		P_Motifuda.tan[P_Motifuda.tan_count].Img = torifuda[2].Img;
		P_Motifuda.tan_count += 1;
		P_Motifuda.tan[P_Motifuda.tan_count].display = TRUE;
		torifuda[2].Img = 0;
	}
	 if (torifuda[3].Tan == TRUE) {
		 P_Motifuda.tan[P_Motifuda.tan_count].Img = torifuda[3].Img;
		P_Motifuda.tan_count += 1;
		P_Motifuda.tan[P_Motifuda.tan_count].display = TRUE;
		torifuda[3].Img = 0;
	}
	 if (torifuda[4].Tan == TRUE) {
		P_Motifuda.tan[P_Motifuda.tan_count].Img = torifuda[4].Img;
		P_Motifuda.tan[P_Motifuda.tan_count].display = TRUE;
		P_Motifuda.tan_count += 1;
		torifuda[4].Img = 0;
	}
	 if (torifuda[5].Tan == TRUE) {
		P_Motifuda.tan[P_Motifuda.tan_count].Img = torifuda[5].Img;
		P_Motifuda.tan[P_Motifuda.tan_count].display = TRUE;
		P_Motifuda.tan_count += 1;		
		torifuda[5].Img = 0;
	}
	 if (torifuda[6].Tan == TRUE) {
		P_Motifuda.tan[P_Motifuda.tan_count].Img = torifuda[6].Img;
		P_Motifuda.tan[P_Motifuda.tan_count].display = TRUE;
		P_Motifuda.tan_count += 1;
		torifuda[6].Img = 0;
	}
	 if (torifuda[7].Tan == TRUE) {
		P_Motifuda.tan[P_Motifuda.tan_count].Img = torifuda[7].Img;
		P_Motifuda.tan[P_Motifuda.tan_count].display = TRUE;
		P_Motifuda.tan_count += 1;
		torifuda[7].Img = 0;
	}
	//�J�X
	if (torifuda[0].Kas == TRUE) {
		P_Motifuda.kas[P_Motifuda.kas_count].Img = torifuda[0].Img;
		P_Motifuda.kas[P_Motifuda.kas_count].display = TRUE;
		torifuda[0].Img = 0;
		P_Motifuda.kas_count += 1;
	}
	 if (torifuda[1].Kas == TRUE) {
		P_Motifuda.kas[P_Motifuda.kas_count].Img = torifuda[1].Img;
		torifuda[1].Img = 0;
		P_Motifuda.kas[P_Motifuda.kas_count].display = TRUE;
		P_Motifuda.kas_count += 1;
	}
	 if (torifuda[2].Kas == TRUE) 
	{
		P_Motifuda.kas[P_Motifuda.kas_count].Img = torifuda[2].Img;
		P_Motifuda.kas[P_Motifuda.kas_count].display = TRUE;
		torifuda[2].Img = 0;
		P_Motifuda.kas_count += 1;
	}
	 if (torifuda[3].Tan == TRUE) {
		P_Motifuda.kas[P_Motifuda.kas_count].Img = torifuda[3].Img;
		P_Motifuda.kas[P_Motifuda.kas_count].display = TRUE;
		torifuda[3].Img = 0;
		P_Motifuda.kas_count += 1;
	}
	 if (torifuda[4].Kas == TRUE) {
		P_Motifuda.kas[P_Motifuda.kas_count].Img = torifuda[4].Img;
		P_Motifuda.kas[P_Motifuda.kas_count].display = TRUE;
		P_Motifuda.kas_count += 1;
		torifuda[4].Img = 0;
	}
	 if (torifuda[5].Kas == TRUE) {
		P_Motifuda.kas[P_Motifuda.kas_count].Img = torifuda[5].Img;
		P_Motifuda.kas[P_Motifuda.kas_count].display = TRUE;
		torifuda[5].Img = 0;
		P_Motifuda.kas_count += 1;
	}
	 if (torifuda[6].Kas == TRUE) {
		P_Motifuda.kas[P_Motifuda.kas_count].Img = torifuda[6].Img;
		torifuda[6].Img = 0;
		P_Motifuda.kas[P_Motifuda.kas_count].display = TRUE;
		P_Motifuda.kas_count += 1;
	}
	 if (torifuda[7].Kas == TRUE) {
		P_Motifuda.kas[P_Motifuda.kas_count].Img = torifuda[7].Img;
		torifuda[7].Img = 0;
		P_Motifuda.kas[P_Motifuda.kas_count].display = TRUE;
		P_Motifuda.kas_count += 1;
	}
}

