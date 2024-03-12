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
	//構造体に札の情報を格納（画像、月、札の種類）
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
	//手札座標の設定
	Player[0].FudaX = 80;
	Player[0].FudaY = 600;
	for (int i = 1; i < 8; i++) {
		Player[i].FudaX = Player[i - 1].FudaX + 80;
		Player[i].FudaY = 600;
	}
	//置き札の座標設定(捨て札で置き府?が増えたときのため余分に設定）
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
	//自分の持ち札の座標設定（全４段　相手のは未設定なので調整の必要がある可能性あり）
	//カス札（最下段）
	P_Motifuda.kas[0].x = 905;
	P_Motifuda.kas[0].y = 675;
	for (int i = 1; i < 24; i++) {
		P_Motifuda.kas[i].x = P_Motifuda.kas[i - 1].x + 40;
		P_Motifuda.kas[i].y = 675;
	}
	//タン札（下から２段目）6
	P_Motifuda.tan[0].x = 905;
	P_Motifuda.tan[0].y = 595;
	for (int i = 1; i < 10; i++) {
		P_Motifuda.tan[i].x = P_Motifuda.tan[i - 1].x + 40;
		P_Motifuda.tan[i].y = 590;
	}
	//タネ札（上から２段目）
	P_Motifuda.tane[0].x = 905;
	P_Motifuda.tane[0].y = 515;
	for (int i = 1; i < 9; i++) {
		P_Motifuda.tane[i].x = P_Motifuda.tane[i - 1].x + 40;
		P_Motifuda.tane[i].y = 510;
	}
	//光札（最上段）
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
	// 0～47までの値を順に格納
	for (int i = 0; i < 48; i++)
	{
		yama[i] = i;
	}
	//マウス座標
	MouseX = 0;
	MouseY = 0;
	OyaGimeflg = 0; //親決めのフラグ
	Startflg = 0;
	Judgeflg = 0; //親決め用フラグ
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
	CursorX = 45; //手札の選択札を囲む座標
	CursorY = 547;
	CenterX = 80; //選択札の中心座標
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
	case 0://親決め
	/*	OyaGime();*/
		if (CheckHitKey(KEY_INPUT_0)) {
			Phase = 1;
			tick = 0;
		}
		break;
	case 1: //札配布
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
	DrawFormatString(700, 20, GetColor(255, 0, 0), " マウス座標：X座標 %d Y座標 %d ", MouseX, MouseY);
	DrawFormatString(700, 480, GetColor(255, 0, 0), "%d月", torifuda[toricount].month);
	DrawFormatString(700, 300, GetColor(255, 0, 0), "stickX:%d", PAD_INPUT::GetLStick().ThumbX);
	switch (Phase)
	{
	case 0: //親決め
		DrawRotaGraph(280, 100, 0.6f, 0, E_fudaImg, FALSE);
		//DrawFormatString(FudaX + 300, FudaY + 120, GetColor(255, 0, 0), "%d月", E_judge);
		DrawRotaGraph(280, 400, 0.7f, 0, P_fudaImg, FALSE);
		/*DrawFormatString(FudaX + 300, FudaY + 420, GetColor(255, 0, 0), "%d月", P_judge);*/
		/*f (Judgeflg == 1)
			DrawFormatString(300, 360, GetColor(255, 0, 0), "あなたが親（先手）です");
		}
		else {
			DrawFormatString(300, 360, GetColor(255, 0, 0), "相手が親（先手）です");
		}*/
		break;
	case 1://札配布
	case 2:
	case 3:
		//山札
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
		//Field上
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
		//札選択
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

	////光札の持ち札表示
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
	//タネ札の持ち札表示
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
	//タン札の表示
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
	//カス札の表示
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
//親決め
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
	// シャッフル
	for (int i = 48 - 1; i > 0; i--)
	{
		int s = GetRand(i);

		int temp = yama[i];
		yama[i] = yama[s];
		yama[s] = temp;
	}
}

//札配布  
void Hanafuda::shuffleFuda()
{
	Init(); //配列内シャッフル
	if (CheckHitKey(KEY_INPUT_1) || PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		// 場に配置
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
		// プレイヤーに配布
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
		// 敵に配布
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
//手番
void Hanafuda::Oyaban()  //順番の時の処理 手札を選ぶ→場と判定→取り札か捨て札か判定する
{
	i = 0;
	// 操作間隔時間
	stick_x = PAD_INPUT::GetLStick().ThumbX;
	const int max_input_margin = 10;
	// スティックの感度
	const int stick_sensitivity = 20000;
	select = 0;
	MoveCursor = TRUE;

	Tefudalocation();
	//Cursor = TRUE;
	if (input_margin < max_input_margin) {
		input_margin++;
	}
	else {
		// スティックのY座標を取得
		if (std::abs(stick_x) > stick_sensitivity) {
			// スティックが右に移動した場合
			if (stick_x > 0 && MoveCursor == TRUE) {
				CursorX += 80;
				CenterX += 80;
			}
			// スティックが左に移動した場合
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
//手札からどれをだすか
void Hanafuda::Tefudalocation() 
{
	if (CenterX > 45 && CenterX < 115) { //１枚目
		i = 1;
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)){
			if (CenterX < 80 || CenterX > 80){
				CursorX = 45;//選択したらカーソルを動かせないようにする
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
	else if (CenterX > 125 && CenterX < 195) { //２枚目
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
	else if (CenterX > 215 && CenterX < 275) { //３枚目
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
	else if (CenterX > 285 && CenterX < 355) { //４枚目
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
	else if (CenterX > 365 && CenterX < 435) { //５枚目
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
	else if (CenterX > 445 && CenterX < 515) { //６枚目
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
	else if (CenterX > 525 && CenterX < 595) { //７枚目
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
	else if (CenterX > 605 && CenterX < 675) { //８枚目
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
//場に取り札があるか
void Hanafuda::location()
{
	int a = 0;
	switch (count) {
	case 0:
		a = 0;
		//取り札のカウントを0に
		toricount = 0; 
		//手札から出したとき（場に取れる物が複数あった時用の修正必要）
		do {
			for (j = 0; j < F_count; j++) {
				if (Judgefuda.month == Field[j].month) {
					torifuda[toricount].Img = Judgefuda.Img; //toricountは0
					torifuda[toricount].month = Judgefuda.month;
					torifuda[toricount].Hikari = Judgefuda.Hikari;
					torifuda[toricount].Tane = Judgefuda.Tane;
					torifuda[toricount].Tan = Judgefuda.Tan;
					torifuda[toricount].Kas = Judgefuda.Kas;
					torifuda[toricount].display = TRUE;
					toricount += 1;
					torifuda[toricount].Img = Field[j].Img; //toricountは１以上にする
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
					a += 1; //場にある札分ループ処理のカウント　aが場にある札分カウントされると捨て札
				}
			}
		} while (j < F_count);
		//捨て札
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
		//山札から出したとき
		a = 0;
			do {		//手札から出したとき（場に取れる物が複数あった時用の修正必要）
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
//山札から引いたとき
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
//取り札を持ち札に移動
void Hanafuda::Move() { 
	//光札
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
	//タネ札
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
	//タン
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
	//カス
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

