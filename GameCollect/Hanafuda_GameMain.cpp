#include"Hanafuda_GameMain.h"
#include"DxLib.h"
#include"Math.h"
#include"Time.h"
#include"PadInput.h"
#include"stdlib.h"
#include<iostream>
Hanafuda::Hanafuda()
{
	for (int i = 0; i < 8; i++) {
		torifuda[i] = { 0 };
	}
	Stage = LoadGraph("images/Hanafuda/Background03.png");
	UraImg = LoadGraph("images/Hanafuda/HanafudaCard_Back.png");
	if (LoadDivGraph("images/Hanafuda/HanafudaCard.png", 48, 8, 6, 128, 256, FudaImg)) {}
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
	Enemy[0].FudaX = 80;
	Enemy[0].FudaY = 100;
	for (int i = 1; i < 8; i++) {
		Enemy[i].FudaX = Enemy[i - 1].FudaX + 80;
		Enemy[i].FudaY = 100;
	}
	//置き札の座標設定(捨て札で置き札が増えたときのため余分に設定）
	Field[0].FudaX = 300;
	Field[0].FudaY = 250;
	Field[4].FudaX = 300;
	Field[4].FudaY = 400;
	for (int i = 1; i < 4; i++)
	{
		Field[i].FudaX = Field[i - 1].FudaX + 70;
		Field[i].FudaY = 250;
	}
	for (int i = 5; i < 8; i++) {
		Field[i].FudaX = Field[i - 1].FudaX + 70;
		Field[i].FudaY = 400;
	}
	for (int i = 8; i < 12; i++) {
		Field[i].FudaX = Field[i - 1].FudaX + 70;
		switch (i)
		{
		case 8:
			Field[i].FudaY = 250;
			break;
		case 9:
			Field[i].FudaY = 400;
			break;
		case 10:
			Field[i].FudaY = 250;
			break;
		case 11:
			Field[i].FudaY = 400;
			break;
		}
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
			P_Motifuda.tan[i].y = 595;
		}
		//タネ札（上から２段目）
		P_Motifuda.tane[0].x = 905;
		P_Motifuda.tane[0].y = 515;
		for (int i = 1; i < 9; i++) {
			P_Motifuda.tane[i].x = P_Motifuda.tane[i - 1].x + 40;
			P_Motifuda.tane[i].y = 515;
		}
		//光札（最上段）
		P_Motifuda.hikari[0].x = 905;
		P_Motifuda.hikari[0].y = 435;
		for (int i = 1; i < 5; i++) {
			P_Motifuda.hikari[i].x = P_Motifuda.hikari[i - 1].x + 40;
			P_Motifuda.hikari[i].y = 435;
		}
		//敵の持ち札の座標
		E_Motifuda.kas[0].x = 905;
		E_Motifuda.kas[0].y = 45;
		for (int i = 1; i < 24; i++) {
			E_Motifuda.kas[i].x = E_Motifuda.kas[i - 1].x + 40;
			E_Motifuda.kas[i].y = 45;
		}
		E_Motifuda.tan[0].x = 905;
		E_Motifuda.tan[0].y = 125;
		for (int i = 1; i < 10; i++) {
			E_Motifuda.tan[i].x = E_Motifuda.tan[i - 1].x + 40;
			E_Motifuda.tan[i].y = 125;
		}
		E_Motifuda.tane[0].x = 905;
		E_Motifuda.tane[0].y = 205;
		for (int i = 1; i < 9; i++) {
			E_Motifuda.tane[i].x = E_Motifuda.tane[i - 1].x + 40;
			E_Motifuda.tane[i].y = 205;
		}
		E_Motifuda.hikari[0].x = 905;
		E_Motifuda.hikari[0].y = 285;
		for (int i = 1; i < 5; i++) {
			E_Motifuda.hikari[i].x = E_Motifuda.hikari[i - 1].x + 40;
			E_Motifuda.hikari[i].y = 285;
		}
		//取り札座標
		torifuda[0].FudaX = 715;
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
		Judgefuda.X = 700;
		Judgefuda.Y = 400;
		P_shuffleflg = 0;
		E_shuffleflg = 0;
		P_CursorX = 45; //手札の選択札を囲む座標
		P_CursorY = 547;
		E_CursorX = 45;
		E_CursorY = 47;
		P_CenterX = 80; //選択札の中心座標
		P_CenterY = 600;
		E_CenterX = 80;
		E_CenterY = 100;
		Judgeflg = 0;
		count = 0;
		P_count = 0;
		E_count = 0;
		input_margin = 0;
		P_turn = TRUE;
		E_turn = FALSE;
		P_Score = 0;
		E_Score = 1;
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
		if (P_turn == TRUE && E_turn == FALSE) {
			MoveJudge = 0;
			P_ban();
		}
		if (P_count == 0 && E_count == 0) {
			Phase = 4;
			break;
		}
		break;
	case 3:
		if (P_turn == FALSE && E_turn == TRUE) {
			MoveJudge = 1;
			E_ban();
			break;
		}
		if (P_count == 0 && E_count == 0) {
			Phase = 4;
			break;
		}
		break;
	case 4:
		Judge();
		break;
	}
	return this;
}
void Hanafuda::Draw()const
{
	DrawGraph(0, 0, Stage, TRUE);
	SetFontSize(12);
	/*DrawFormatString(1000, 330, GetColor(255, 0, 0), "P_kas:%d",P_Motifuda.kas_count);
	DrawFormatString(1000, 360, GetColor(255, 0, 0), "P_tan:%d", P_Motifuda.tan_count);
	DrawFormatString(1000, 390, GetColor(255, 0, 0), "P_tane:%d", P_Motifuda.tane_count);
	DrawFormatString(1000, 420, GetColor(255, 0, 0), "P_hikari:%d", P_Motifuda.hikari_count);
	DrawFormatString(1000, 450, GetColor(255, 0, 0), "E_kas:%d", E_Motifuda.kas_count);
	DrawFormatString(1000, 480, GetColor(255, 0, 0), "E_tan:%d", E_Motifuda.tan_count);
	DrawFormatString(1000, 510, GetColor(255, 0, 0), "E_tane:%d", E_Motifuda.tane_count);
	DrawFormatString(1000, 540, GetColor(255, 0, 0), "E_hikari:%d", E_Motifuda.hikari_count);

	DrawFormatString(305, 175, GetColor(255, 0, 0), "0:%d月", Field[0].month);
	DrawFormatString(615, 200, GetColor(255, 0, 0), "0kas:%d", Field[0].Kas);
	DrawFormatString(615, 215, GetColor(255, 0, 0), "0tan:%d", Field[0].Tan);
	DrawFormatString(615, 230, GetColor(255, 0, 0), "0tane:%d", Field[0].Tane);
	DrawFormatString(615, 245, GetColor(255, 0, 0), "0hikari:%d", Field[0].Hikari);

	DrawFormatString(370, 175, GetColor(255, 0, 0), "1:%d月", Field[1].month);
	DrawFormatString(680, 200, GetColor(255, 0, 0), "1kas:%d", Field[1].Kas);
	DrawFormatString(680, 215, GetColor(255, 0, 0), "1tan:%d", Field[1].Tan);
	DrawFormatString(680, 230, GetColor(255, 0, 0), "1tane:%d", Field[1].Tane);
	DrawFormatString(680, 245, GetColor(255, 0, 0), "1hikari:%d", Field[1].Hikari);

	DrawFormatString(440, 175, GetColor(255, 0, 0), "2:%d月", Field[2].month);
	DrawFormatString(760, 200, GetColor(255, 0, 0), "2kas:%d", Field[2].Kas);
	DrawFormatString(760, 215, GetColor(255, 0, 0), "2tan:%d", Field[2].Tan);
	DrawFormatString(760, 230, GetColor(255, 0, 0), "2tane:%d", Field[2].Tane);
	DrawFormatString(760, 245, GetColor(255, 0, 0), "2hikari:%d", Field[2].Hikari);

	DrawFormatString(510, 175, GetColor(255, 0, 0), "3:%d月", Field[3].month);
	DrawFormatString(840, 200, GetColor(255, 0, 0), "3kas:%d", Field[3].Kas);
	DrawFormatString(840, 215, GetColor(255, 0, 0), "3tan:%d", Field[3].Tan);
	DrawFormatString(840, 230, GetColor(255, 0, 0), "3tane:%d", Field[3].Tane);
	DrawFormatString(840, 245, GetColor(255, 0, 0), "3hikari:%d", Field[3].Hikari);

	DrawFormatString(305, 330, GetColor(255, 0, 0), "4:%d月", Field[4].month);
	DrawFormatString(615, 360, GetColor(255, 0, 0), "4kas:%d", Field[4].Kas);
	DrawFormatString(615, 375, GetColor(255, 0, 0), "4tan:%d", Field[4].Tan);
	DrawFormatString(615, 390, GetColor(255, 0, 0), "4tane:%d", Field[4].Tane);
	DrawFormatString(615, 405, GetColor(255, 0, 0), "4hikari:%d", Field[4].Hikari);

	DrawFormatString(370, 330, GetColor(255, 0, 0), "5:%d月", Field[5].month);
	DrawFormatString(680, 360, GetColor(255, 0, 0), "5kas:%d", Field[5].Kas);
	DrawFormatString(680, 375, GetColor(255, 0, 0), "5tan:%d", Field[5].Tan);
	DrawFormatString(680, 390, GetColor(255, 0, 0), "5tane:%d", Field[5].Tane);
	DrawFormatString(680, 405, GetColor(255, 0, 0), "5hikari:%d", Field[5].Hikari);

	DrawFormatString(440, 330, GetColor(255, 0, 0), "6:%d月", Field[6].month);
	DrawFormatString(760, 360, GetColor(255, 0, 0), "6kas:%d", Field[6].Kas);
	DrawFormatString(760, 375, GetColor(255, 0, 0), "6tan:%d", Field[6].Tan);
	DrawFormatString(760, 390, GetColor(255, 0, 0), "6tane:%d", Field[6].Tane);
	DrawFormatString(760, 405, GetColor(255, 0, 0), "6hikari:%d", Field[6].Hikari);

	DrawFormatString(510, 330, GetColor(255, 0, 0), "7:%d月", Field[7].month);
	DrawFormatString(840, 360, GetColor(255, 0, 0), "7kas:%d", Field[7].Kas);
	DrawFormatString(840, 375, GetColor(255, 0, 0), "7tan:%d", Field[7].Tan);
	DrawFormatString(840, 390, GetColor(255, 0, 0), "7tane:%d", Field[7].Tane);
	DrawFormatString(840, 405, GetColor(255, 0, 0), "7hikari:%d", Field[7].Hikari);

	DrawFormatString(580, 175, GetColor(255, 0, 0), "8:%d月", Field[8].month);
	DrawFormatString(920, 200, GetColor(255, 0, 0), "8kas:%d", Field[8].Kas);
	DrawFormatString(920, 215, GetColor(255, 0, 0), "8tan:%d", Field[8].Tan);
	DrawFormatString(920, 230, GetColor(255, 0, 0), "8tane:%d", Field[8].Tane);
	DrawFormatString(920, 245, GetColor(255, 0, 0), "8hikari:%d", Field[8].Hikari);

	DrawFormatString(580, 330, GetColor(255, 0, 0), "9:%d月", Field[9].month);
	DrawFormatString(920, 360, GetColor(255, 0, 0), "9kas:%d", Field[9].Kas);
	DrawFormatString(920, 375, GetColor(255, 0, 0), "9tan:%d", Field[9].Tan);
	DrawFormatString(920, 390, GetColor(255, 0, 0), "9tane:%d", Field[9].Tane);
	DrawFormatString(920, 405, GetColor(255, 0, 0), "9hikari:%d", Field[9].Hikari);



	DrawFormatString(80, 500, GetColor(255, 255, 255), "%d月", Player[0].month);
	DrawFormatString(160, 500, GetColor(255, 255, 255), "%d月", Player[1].month);
	DrawFormatString(240, 500, GetColor(255, 255, 255), "%d月", Player[2].month);
	DrawFormatString(320, 500, GetColor(255, 255, 255), "%d月", Player[3].month);
	DrawFormatString(400, 500, GetColor(255, 255, 255), "%d月", Player[4].month);
	DrawFormatString(480, 500, GetColor(255, 255, 255), "%d月", Player[5].month);
	DrawFormatString(560, 500, GetColor(255, 255, 255), "%d月", Player[6].month);
	DrawFormatString(640, 500, GetColor(255, 255, 255), "%d月", Player[7].month);

	DrawFormatString(80, 20, GetColor(255, 0, 0), "%d月", Enemy[0].month);
	DrawFormatString(160, 20, GetColor(255, 0, 0), "%d月", Enemy[1].month);
	DrawFormatString(240, 20, GetColor(255, 0, 0), "%d月", Enemy[2].month);
	DrawFormatString(320, 20, GetColor(255, 0, 0), "%d月", Enemy[3].month);
	DrawFormatString(400, 20, GetColor(255, 0, 0), "%d月", Enemy[4].month);
	DrawFormatString(480, 20, GetColor(255, 0, 0), "%d月", Enemy[5].month);
	DrawFormatString(560, 20, GetColor(255, 0, 0), "%d月", Enemy[6].month);
	DrawFormatString(640, 20, GetColor(255, 0, 0), "%d月", Enemy[7].month);

	DrawFormatString(1000, 140, GetColor(255, 0, 0), "E_hikari[0].X:%d", E_Motifuda.hikari[0].x);
	DrawFormatString(1000, 180, GetColor(255, 0, 0), "E_hikari[0].Y:%d", E_Motifuda.hikari[0].y);


	DrawFormatString(1000, 250, GetColor(255, 0, 0), "F_count:%d", FieldCount);
	DrawFormatString(1000, 200, GetColor(255, 0, 0), "E_count:%d", E_count);
	DrawFormatString(1000, 300, GetColor(255, 0, 0), "P_hand:%d", P_count);
	DrawFormatString(1000, 200, GetColor(255, 0, 0), "Phase:%d", Phase);
	DrawFormatString(1000, 100, GetColor(255, 0, 0), "toricount:%d", toricount);
	DrawFormatString(700, 20, GetColor(255, 0, 0), " マウス座標：X座標 %d Y座標 %d ", MouseX, MouseY);
	DrawFormatString(700, 480, GetColor(255, 0, 0), "%d月", torifuda[toricount].month);
	DrawFormatString(700, 300, GetColor(255, 0, 0), "stickX:%d", PAD_INPUT::GetLStick().ThumbX);*/
	//DrawRotaGraph(E_Motifuda.hikari[0].x, E_Motifuda.hikari[0].y,0.5f,0,Fuda[12].Img, TRUE);
	//DrawRotaGraph(E_Motifuda.tan[1].x, E_Motifuda.tan[1].y,0.5f,0 Fuda[34].Img, TRUE);
	//DrawRotaGraph(E_Motifuda.tane[2].x, E_Motifuda.tane[2].y,0.5f,0, Fuda[27].Img, TRUE);
	//DrawRotaGraph(E_Motifuda.hikari[3].x, E_Motifuda.hikari[3].y, 0.5f,Fuda[45].Img, TRUE);

	switch (Phase)
	{
	case 0: //親決め
		DrawRotaGraph(280, 100, 0.6f, 0, oyagime.E_Img, FALSE);
		//DrawFormatString(FudaX + 300, FudaY + 120, GetColor(255, 0, 0), "%d月", E_judge);
		DrawRotaGraph(280, 400, 0.7f, 0, oyagime.P_Img, FALSE);
		/*DrawFormatString(FudaX + 300, FudaY + 420, GetColor(255, 0, 0), "%d月", P_judge);*/
		if (oyagime.P_month < oyagime.E_month){
			DrawFormatString(300, 360, GetColor(255, 0, 0), "あなたが親（先手）です");
		}
		else if(oyagime.E_month < oyagime.P_month){
			DrawFormatString(300, 360, GetColor(255, 0, 0), "相手が親（先手）です");
		}
		break;
	case 1://札配布
	case 2:
	case 3:
		//山札
		DrawRotaGraph(200, 345, 0.6f, 0, UraImg, TRUE);
		//DrawFormatString(200, 245, GetColor(255, 0, 0), "%d月", Y_month);
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
		DrawFormatString(100, 200, GetColor(255, 255, 255), "%d", Enemy[0].month);
		//Field上
		if (Field[0].display == TRUE) {
			DrawRotaGraph(Field[0].FudaX, Field[0].FudaY, 0.6f, 0, Field[0].Img, TRUE);
		}
		if (Field[1].display == TRUE) {
			DrawRotaGraph(Field[1].FudaX, Field[1].FudaY, 0.6f, 0, Field[1].Img, TRUE);
		}
		if (Field[2].display == TRUE) {
			DrawRotaGraph(Field[2].FudaX, Field[2].FudaY, 0.6f, 0, Field[2].Img, TRUE);
		}
		if (Field[3].display == TRUE) {
			DrawRotaGraph(Field[3].FudaX, Field[3].FudaY, 0.6f, 0, Field[3].Img, TRUE);
		}
		if (Field[4].display == TRUE) {
			DrawRotaGraph(Field[4].FudaX, Field[4].FudaY, 0.6f, 0, Field[4].Img, TRUE);
		}
		if (Field[5].display == TRUE) {
			DrawRotaGraph(Field[5].FudaX, Field[5].FudaY, 0.6f, 0, Field[5].Img, TRUE);
		}
		if (Field[6].display == TRUE) {
			DrawRotaGraph(Field[6].FudaX, Field[6].FudaY, 0.6f, 0, Field[6].Img, TRUE);
		}
		if (Field[7].display == TRUE) {
			DrawRotaGraph(Field[7].FudaX, Field[7].FudaY, 0.6f, 0, Field[7].Img, TRUE);
		}
		if (Field[8].display == TRUE) {
			DrawRotaGraph(Field[8].FudaX, Field[8].FudaY, 0.6f, 0, Field[8].Img, TRUE);
		}
		if (Field[9].display == TRUE) {
			DrawRotaGraph(Field[9].FudaX, Field[9].FudaY, 0.6f, 0, Field[9].Img, TRUE);
		}
		//プレイヤー
		DrawBox(P_CursorX, P_CursorY, P_CursorX + 70, P_CursorY + 110, GetColor(255, 0, 0), FALSE);
		//敵
		DrawBox(E_CursorX, E_CursorY, E_CursorX + 70, E_CursorY + 110, GetColor(255, 0, 0), FALSE);

		DrawCircle(P_CenterX, P_CenterY, 20, GetColor(0, 0, 255), TRUE);
	case 4:
		if (E_Win == TRUE && P_Win == FALSE) {
			SetFontSize(24);
			DrawFormatString(400, 310, GetColor(255, 255, 255), "相手の勝ちです!!  Score:%d",E_Score);
		}
		else if (P_Win == TRUE && E_Win == FALSE) {
			SetFontSize(24);
			DrawFormatString(400, 310, GetColor(255, 255, 255), "あなたの勝ちです!!  Score:%d",P_Score);
		}
}
	if (Judgefuda.display == TRUE) {
		DrawRotaGraph(700, 400, 0.6f, 0, Judgefuda.Img, TRUE);
	}
	if (yamafuda.display == TRUE) {
		DrawRotaGraph(250, 345, 0.6f, 0, yamafuda.Img, TRUE);
	}
	if (torifuda[0].display == TRUE) {
		DrawRotaGraph(torifuda[0].FudaX, torifuda[0].FudaY, 0.6f, 0, torifuda[0].Img, TRUE);
	}
	if (torifuda[1].display == TRUE) {
		DrawRotaGraph(torifuda[1].FudaX, torifuda[1].FudaY, 0.6f, 0, torifuda[1].Img, TRUE);
	}
	if (torifuda[2].display == TRUE) {
		DrawRotaGraph(torifuda[2].FudaX, torifuda[2].FudaY, 0.6f, 0, torifuda[2].Img, TRUE);
	}
	if (torifuda[3].display == TRUE) {
		DrawRotaGraph(torifuda[3].FudaX, torifuda[3].FudaY, 0.6f, 0, torifuda[3].Img, TRUE);
	}

	    //光札の持ち札表示
		DrawRotaGraph(P_Motifuda.hikari[0].x, P_Motifuda.hikari[0].y, 0.5f, 0, P_Motifuda.hikari[0].Img, TRUE);
		DrawRotaGraph(P_Motifuda.hikari[1].x, P_Motifuda.hikari[1].y, 0.5f, 0, P_Motifuda.hikari[1].Img, TRUE);
		DrawRotaGraph(P_Motifuda.hikari[2].x, P_Motifuda.hikari[2].y, 0.5f, 0, P_Motifuda.hikari[2].Img, TRUE);
		DrawRotaGraph(P_Motifuda.hikari[3].x, P_Motifuda.hikari[3].y, 0.5f, 0, P_Motifuda.hikari[3].Img, TRUE);
		DrawRotaGraph(P_Motifuda.hikari[4].x, P_Motifuda.hikari[4].y, 0.5f, 0, P_Motifuda.hikari[4].Img, TRUE);
		//タネ札の持ち札表示
		DrawRotaGraph(P_Motifuda.tane[0].x, P_Motifuda.tane[0].y, 0.5f, 0, P_Motifuda.tane[0].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tane[1].x, P_Motifuda.tane[0].y, 0.5f, 0, P_Motifuda.tane[1].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tane[2].x, P_Motifuda.tane[0].y, 0.5f, 0, P_Motifuda.tane[2].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tane[3].x, P_Motifuda.tane[0].y, 0.5f, 0, P_Motifuda.tane[3].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tane[4].x, P_Motifuda.tane[0].y, 0.5f, 0, P_Motifuda.tane[4].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tane[5].x, P_Motifuda.tane[0].y, 0.5f, 0, P_Motifuda.tane[5].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tane[6].x, P_Motifuda.tane[0].y, 0.5f, 0, P_Motifuda.tane[6].Img, TRUE);
		//タン札の持ち札表示
		DrawRotaGraph(P_Motifuda.tan[0].x, P_Motifuda.tan[0].y, 0.5f, 0, P_Motifuda.tan[0].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tan[1].x, P_Motifuda.tan[1].y, 0.5f, 0, P_Motifuda.tan[1].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tan[2].x, P_Motifuda.tan[2].y, 0.5f, 0, P_Motifuda.tan[2].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tan[3].x, P_Motifuda.tan[3].y, 0.5f, 0, P_Motifuda.tan[3].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tan[4].x, P_Motifuda.tan[4].y, 0.5f, 0, P_Motifuda.tan[4].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tan[5].x, P_Motifuda.tan[5].y, 0.5f, 0, P_Motifuda.tan[5].Img, TRUE);
		DrawRotaGraph(P_Motifuda.tan[6].x, P_Motifuda.tan[6].y, 0.5f, 0, P_Motifuda.tan[6].Img, TRUE);
		//カス札の表示
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
		//光札の持ち札表示
		DrawRotaGraph(E_Motifuda.hikari[0].x, E_Motifuda.hikari[0].y, 0.5f, 0, E_Motifuda.hikari[0].Img, TRUE);
		DrawRotaGraph(E_Motifuda.hikari[1].x, E_Motifuda.hikari[1].y, 0.5f, 0, E_Motifuda.hikari[1].Img, TRUE);
		DrawRotaGraph(E_Motifuda.hikari[2].x, E_Motifuda.hikari[2].y, 0.5f, 0, E_Motifuda.hikari[2].Img, TRUE);
		DrawRotaGraph(E_Motifuda.hikari[3].x, E_Motifuda.hikari[3].y, 0.5f, 0, E_Motifuda.hikari[3].Img, TRUE);
		DrawRotaGraph(E_Motifuda.hikari[4].x, E_Motifuda.hikari[4].y, 0.5f, 0, E_Motifuda.hikari[4].Img, TRUE);
		//タネ札の持ち札表示
		DrawRotaGraph(E_Motifuda.tane[0].x, E_Motifuda.tane[0].y, 0.5f, 0, E_Motifuda.tane[0].Img, TRUE);
		DrawRotaGraph(E_Motifuda.tane[1].x, E_Motifuda.tane[0].y, 0.5f, 0, E_Motifuda.tane[1].Img, TRUE);
		DrawRotaGraph(E_Motifuda.tane[2].x, E_Motifuda.tane[0].y, 0.5f, 0, E_Motifuda.tane[2].Img, TRUE);
		DrawRotaGraph(E_Motifuda.tane[3].x, E_Motifuda.tane[0].y, 0.5f, 0, E_Motifuda.tane[3].Img, TRUE);
		DrawRotaGraph(E_Motifuda.tane[4].x, E_Motifuda.tane[0].y, 0.5f, 0, E_Motifuda.tane[4].Img, TRUE);
		DrawRotaGraph(E_Motifuda.tane[5].x, E_Motifuda.tane[0].y, 0.5f, 0, E_Motifuda.tane[5].Img, TRUE);
		DrawRotaGraph(E_Motifuda.tane[6].x, E_Motifuda.tane[0].y, 0.5f, 0, E_Motifuda.tane[6].Img, TRUE);
		//タン札の持ち札表示
		DrawRotaGraph(E_Motifuda.tan[0].x, E_Motifuda.tan[0].y, 0.5f, 0, E_Motifuda.tan[0].Img, TRUE);
		DrawRotaGraph(E_Motifuda.tan[1].x, E_Motifuda.tan[1].y, 0.5f, 0, E_Motifuda.tan[1].Img, TRUE);
		DrawRotaGraph(E_Motifuda.tan[2].x, E_Motifuda.tan[2].y, 0.5f, 0, E_Motifuda.tan[2].Img, TRUE);
		DrawRotaGraph(E_Motifuda.tan[3].x, E_Motifuda.tan[3].y, 0.5f, 0, E_Motifuda.tan[3].Img, TRUE);
		DrawRotaGraph(E_Motifuda.tan[4].x, E_Motifuda.tan[4].y, 0.5f, 0, E_Motifuda.tan[4].Img, TRUE);
		DrawRotaGraph(E_Motifuda.tan[5].x, E_Motifuda.tan[5].y, 0.5f, 0, E_Motifuda.tan[5].Img, TRUE);
		DrawRotaGraph(E_Motifuda.tan[6].x, E_Motifuda.tan[6].y, 0.5f, 0, E_Motifuda.tan[6].Img, TRUE);
		//カス札の表示
		DrawRotaGraph(E_Motifuda.kas[0].x, E_Motifuda.kas[0].y, 0.5f, 0, E_Motifuda.kas[0].Img, TRUE);
		DrawRotaGraph(E_Motifuda.kas[1].x, E_Motifuda.kas[1].y, 0.5f, 0, E_Motifuda.kas[1].Img, TRUE);
		DrawRotaGraph(E_Motifuda.kas[2].x, E_Motifuda.kas[2].y, 0.5f, 0, E_Motifuda.kas[2].Img, TRUE);
		DrawRotaGraph(E_Motifuda.kas[3].x, E_Motifuda.kas[3].y, 0.5f, 0, E_Motifuda.kas[3].Img, TRUE);
		DrawRotaGraph(E_Motifuda.kas[4].x, E_Motifuda.kas[4].y, 0.5f, 0, E_Motifuda.kas[4].Img, TRUE);
		DrawRotaGraph(E_Motifuda.kas[5].x, E_Motifuda.kas[5].y, 0.5f, 0, E_Motifuda.kas[5].Img, TRUE);
		DrawRotaGraph(E_Motifuda.kas[6].x, E_Motifuda.kas[6].y, 0.5f, 0, E_Motifuda.kas[6].Img, TRUE);
		DrawRotaGraph(E_Motifuda.kas[7].x, E_Motifuda.kas[7].y, 0.5f, 0, E_Motifuda.kas[7].Img, TRUE);
		DrawRotaGraph(E_Motifuda.kas[8].x, E_Motifuda.kas[8].y, 0.5f, 0, E_Motifuda.kas[8].Img, TRUE);
		DrawRotaGraph(E_Motifuda.kas[9].x, E_Motifuda.kas[9].y, 0.5f, 0, E_Motifuda.kas[9].Img, TRUE);
		DrawRotaGraph(E_Motifuda.kas[10].x, E_Motifuda.kas[10].y, 0.5f, 0, E_Motifuda.kas[10].Img, TRUE);
		DrawRotaGraph(E_Motifuda.kas[11].x, E_Motifuda.kas[11].y, 0.5f, 0, E_Motifuda.kas[11].Img, TRUE);
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
			Field[s].display = TRUE;
			FieldCount++;
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
//親決め
void Hanafuda:: OyaGime()
{
	do {
		int num = rand() % 47;
		oyagime.P_Img = Fuda[num].Img;
		oyagime.P_month = Fuda[num].month;
		int n = rand() % 47;
		oyagime.E_Img = Fuda[n].Img;
		oyagime.E_month = Fuda[n].Img;
	} while (oyagime.E_month == oyagime.P_month);
	if (oyagime.E_month < oyagime.P_month) {
		E_Score = 1;
		P_Score = 0;
		E_turn = TRUE;
		P_turn = FALSE;	
	}
	else if (oyagime.P_month < oyagime.E_month) {
		E_Score = 0;
		P_Score = 1;
		E_turn = FALSE;
		P_turn = TRUE;
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
//手番
void Hanafuda::P_ban()  //順番の時の処理 手札を選ぶ→場と判定→取り札か捨て札か判定する
{
	MoveJudge = 0;
	i = 0;
	// 操作間隔時間
	stick_x = PAD_INPUT::GetLStick().ThumbX;
	const int max_input_margin = 10;
	// スティックの感度
	const int stick_sensitivity = 20000;
	select = 0;
	P_MoveCursor = TRUE;

	Tefudalocation();
	//Cursor = TRUE;
	if (input_margin < max_input_margin) {
		input_margin++;
	}
	else {
		// スティックのY座標を取得
		if (std::abs(stick_x) > stick_sensitivity) {
			// スティックが右に移動した場合
			if (stick_x > 0 && P_MoveCursor == TRUE) {
				P_CursorX += 80;
				P_CenterX += 80;
			}
			// スティックが左に移動した場合
			else if (stick_x < 0 && P_MoveCursor == TRUE) {
				P_CursorX -= 80;
				P_CenterX -= 80;
			}
			if (P_CenterX < 45) {
				P_CursorX = 45;
				P_CenterX = 80;
			}
			if (P_CenterX > 640) {
				P_CursorX = 605;
				P_CenterX = 640;

			}
		}
		input_margin = 0;
	}
}
//敵
void Hanafuda::E_ban()
{
	MoveJudge = 1;
	i = 0;
	// 操作間隔時間
	stick_x = PAD_INPUT::GetLStick().ThumbX;
	const int max_input_margin = 10;
	// スティックの感度
	const int stick_sensitivity = 20000;
	select = 0;
	E_MoveCursor = TRUE;

	Tefudalocation();
	E_Cursor = TRUE;
	if (input_margin < max_input_margin) {
		input_margin++;
	}
	else {
		// スティックのY座標を取得
		if (std::abs(stick_x) > stick_sensitivity) {
			// スティックが右に移動した場合
			if (stick_x > 0 && E_MoveCursor == TRUE) {
				E_CursorX += 80;
				E_CenterX += 80;
			}
			// スティックが左に移動した場合
			else if (stick_x < 0 && E_MoveCursor == TRUE) {
				E_CursorX -= 80;
				E_CenterX -= 80;
			}
			if (E_CenterX < 45) {
				E_CursorX = 45;
				E_CenterX = 80;
			}
			if (E_CenterX > 640) {
				E_CursorX = 605;
				E_CenterX = 640;

			}
		}
		input_margin = 0;
	}
}
void Hanafuda::location()
{
	{
		int a = 0;
		switch (count) {
		case 0:
			a = 0;
			//取り札のカウントを0に
			toricount = 0;
			do {
				if (Judgefuda.month == Field[a].month) {
					torifuda[toricount].Img = Judgefuda.Img; //toricountは0
					torifuda[toricount].month = Judgefuda.month;
					torifuda[toricount].Hikari = Judgefuda.Hikari;
					torifuda[toricount].Tane = Judgefuda.Tane;
					torifuda[toricount].Tan = Judgefuda.Tan;
					torifuda[toricount].Kas = Judgefuda.Kas;
					Judgefuda = { 0 };
					torifuda[toricount].display = TRUE;
					toricount += 1;
					torifuda[toricount].Img = Field[a].Img; //toricountは１以上にする
					torifuda[toricount].month = Field[a].month;
					torifuda[toricount].Hikari = Field[a].Hikari;
					torifuda[toricount].Tane = Field[a].Tane;
					torifuda[toricount].Tan = Field[a].Tan;
					torifuda[toricount].Kas = Field[a].Kas;
					Field[a].display = FALSE;
					Field[a].Img = 0;
					Field[a].month = 0;
					torifuda[toricount].display = TRUE;
					toricount += 1;
					FieldCount--;
					break;
				}
				a++;
			} while (a <= FieldCount);
			if (a > FieldCount) {
				Sute = 0;
				Sutefuda();
				break;
			}
			break;
		case 1://山札から出したとき
			a = 0;
			//手札から出したとき（場に取れる物が複数あった時用の修正必要）
			do {
				if (yamafuda.month == Field[a].month)
				{
					torifuda[toricount].Img = Field[a].Img;
					torifuda[toricount].month = Field[a].month;
					torifuda[toricount].Hikari = Field[a].Hikari;
					torifuda[toricount].Tane = Field[a].Tane;
					torifuda[toricount].Tan = Field[a].Tan;
					torifuda[toricount].Kas = Field[a].Kas;
					FieldCount--;
					Field[a].display = FALSE;
					Field[a].Img = 0;
					Field[a].month = 0;
					torifuda[toricount].display = TRUE;
					toricount += 1;
					torifuda[toricount].Img = yamafuda.Img;
					torifuda[toricount].month = yamafuda.month;
					torifuda[toricount].Hikari = yamafuda.Hikari;
					torifuda[toricount].Tane = yamafuda.Tane;
					torifuda[toricount].Tan = yamafuda.Tan;
					torifuda[toricount].Kas = yamafuda.Kas;
					torifuda[toricount].display = TRUE;
					yamafuda = { 0 };
					toricount += 1;
					break;
				}
				a++;
			} while (a <= FieldCount);
			if (a > FieldCount) {
				Sute = 1;
				Sutefuda();
				break;
			}
			break;
		}

	}

}
//手札からどれをだすか
void Hanafuda::Tefudalocation()
{
	switch (MoveJudge)
	{
	case 0:
		if (P_CenterX > 45 && P_CenterX < 115 && PAD_INPUT::OnButton(XINPUT_BUTTON_B)) { //１枚目
				P_MoveCursor = FALSE;
				Judgefuda.Img = Player[0].Img;
				Judgefuda.month = Player[0].month;
				Judgefuda.Hikari = Player[0].Hikari;
				Judgefuda.Tan = Player[0].Tan;
				Judgefuda.Tane = Player[0].Tane;
				Judgefuda.Kas = Player[0].Kas;
				Judgefuda.display = TRUE;
				Player[0].display = FALSE;
				Player[0] = { 0 };
				count = 0;
				P_count--;
				location();
				Hiku();
			}
		else if (P_CenterX > 125 && P_CenterX < 195 && PAD_INPUT::OnButton(XINPUT_BUTTON_B)) { //２枚目
				Judgefuda.Img = Player[1].Img;
				Judgefuda.month = Player[1].month;
				Judgefuda.Hikari = Player[1].Hikari;
				Judgefuda.Tan = Player[1].Tan;
				Judgefuda.Tane = Player[1].Tane;
				Judgefuda.Kas = Player[1].Kas;
				Judgefuda.display = TRUE;
				Player[1].display = FALSE;
				Player[1] = { 0 };
				count = 0;
				P_count--;
				location();
				Hiku();

		}
		else if (P_CenterX > 215 && P_CenterX < 275 && PAD_INPUT::OnButton(XINPUT_BUTTON_B)) { //３枚目
				Judgefuda.Img = Player[2].Img;
				Judgefuda.month = Player[2].month;
				Judgefuda.Hikari = Player[2].Hikari;
				Judgefuda.Tan = Player[2].Tan;
				Judgefuda.Tane = Player[2].Tane;
				Judgefuda.Kas = Player[2].Kas;
				Judgefuda.display = TRUE;
				Player[2].display = FALSE;
				Player[2] = { 0 };
				count = 0;
				P_count--;
				location();
				Hiku();
			}
		else if (P_CenterX > 285 && P_CenterX < 355 && PAD_INPUT::OnButton(XINPUT_BUTTON_B)) { //４枚目
				Judgefuda.Img = Player[3].Img;
				Judgefuda.month = Player[3].month;
				Judgefuda.Hikari = Player[3].Hikari;
				Judgefuda.Tan = Player[3].Tan;
				Judgefuda.Tane = Player[3].Tane;
				Judgefuda.Kas = Player[3].Kas;
				Judgefuda.display = TRUE;
				Player[3].display = FALSE;
				Player[3] = { 0 };
				count = 0;
				P_count--;
				location();
				Hiku();
		}
		else if (P_CenterX > 365 && P_CenterX < 435 && PAD_INPUT::OnButton(XINPUT_BUTTON_B)) { //５枚目
				Judgefuda.Img = Player[4].Img;
				Judgefuda.month = Player[4].month;
				Judgefuda.Hikari = Player[4].Hikari;
				Judgefuda.Tan = Player[4].Tan;
				Judgefuda.Tane = Player[4].Tane;
				Judgefuda.Kas = Player[4].Kas;
				Judgefuda.display = TRUE;
				Player[4].display = FALSE;
				Player[4] = { 0 };
				count = 0;
				P_count--;
				location();
				Hiku();
		}
		else if (P_CenterX > 445 && P_CenterX < 515 && PAD_INPUT::OnButton(XINPUT_BUTTON_B)) { //６枚目
				Judgefuda.Img = Player[5].Img;
				Judgefuda.month = Player[5].month;
				Judgefuda.Hikari = Player[5].Hikari;
				Judgefuda.Tan = Player[5].Tan;
				Judgefuda.Tane = Player[5].Tane;
				Judgefuda.Kas = Player[5].Kas;
				Judgefuda.display = 1;
				Player[5].display = FALSE;
				Player[5] = { 0 };
				count = 0;
				P_count--;
				location();
				Hiku();
		}
		else if (P_CenterX > 525 && P_CenterX < 595 && PAD_INPUT::OnButton(XINPUT_BUTTON_B)) { //７枚目
				Judgefuda.Img = Player[6].Img;
				Judgefuda.month = Player[6].month;
				Judgefuda.Hikari = Player[6].Hikari;
				Judgefuda.Tane = Player[6].Tane;
				Judgefuda.Tan = Player[6].Tan;
				Judgefuda.Kas = Player[6].Kas;
				Judgefuda.display = TRUE;
				Player[6].display = FALSE;
				Player[6] = { 0 };
				count = 0;
				P_count--;
				location();
				Hiku();
				break;
			}
		else if (P_CenterX > 605 && P_CenterX < 675 && PAD_INPUT::OnButton(XINPUT_BUTTON_B)) { //８枚目
				Judgefuda.Img = Player[7].Img;
				Judgefuda.month = Player[7].month;
				Judgefuda.Hikari = Player[7].Hikari;
				Judgefuda.Tan = Player[7].Tan;
				Judgefuda.Tane = Player[7].Tane;
				Judgefuda.Kas = Player[7].Kas;
				Judgefuda.display = TRUE;
				Player[7].display = FALSE;
				Player[7] = { 0 };
				count = 0;
				P_count--;
				location();
				Hiku();
				break;
			}
			break;
	case 1:
		if (E_CenterX > 45 && E_CenterX < 115  && PAD_INPUT::OnButton(XINPUT_BUTTON_B)) { //１枚目
				E_MoveCursor = FALSE;
				Judgefuda.Img = Enemy[0].Img;
				Judgefuda.month = Enemy[0].month;
				Judgefuda.Hikari = Enemy[0].Hikari;
				Judgefuda.Tan = Enemy[0].Tan;
				Judgefuda.Tane = Enemy[0].Tane;
				Judgefuda.Kas = Enemy[0].Kas;
				Judgefuda.display = TRUE;
				Enemy[0].display = FALSE;
				Enemy[0] = { 0 };
				count = 0;
				E_count--;
				location();
				Hiku();
				break;
			}
		else if (E_CenterX > 125 && E_CenterX < 195 && PAD_INPUT::OnButton(XINPUT_BUTTON_B)) { //２枚目
				Judgefuda.Img = Enemy[1].Img;
				Judgefuda.month = Enemy[1].month;
				Judgefuda.Hikari = Enemy[1].Hikari;
				Judgefuda.Tan = Enemy[1].Tan;
				Judgefuda.Tane = Enemy[1].Tane;
				Judgefuda.Kas = Enemy[1].Kas;
				Judgefuda.display = TRUE;
				Enemy[1].display = FALSE;
				Enemy[1] = { 0 };
				count = 0;
				E_count--;
				location();
				Hiku(); 
				break;

			}
		else if (E_CenterX > 215 && E_CenterX < 275 && PAD_INPUT::OnButton(XINPUT_BUTTON_B)) { //３枚目
				Judgefuda.Img = Enemy[2].Img;
				Judgefuda.month = Enemy[2].month;
				Judgefuda.Hikari = Enemy[2].Hikari;
				Judgefuda.Tan = Enemy[2].Tan;
				Judgefuda.Tane = Enemy[2].Tane;
				Judgefuda.Kas = Enemy[2].Kas;
				Judgefuda.display = TRUE;
				Enemy[2].display = FALSE;
				Enemy[2] = { 0 };
				E_count--;
				count = 0;
				location();
				Hiku();
				break;
		}
		else if (E_CenterX > 285 && E_CenterX < 355 && PAD_INPUT::OnButton(XINPUT_BUTTON_B)) { //４枚目
				Judgefuda.Img = Enemy[3].Img;
				Judgefuda.month = Enemy[3].month;
				Judgefuda.Hikari = Enemy[3].Hikari;
				Judgefuda.Tan = Enemy[3].Tan;
				Judgefuda.Tane = Enemy[3].Tane;
				Judgefuda.Kas = Enemy[3].Kas;
				Judgefuda.display = TRUE;
				Enemy[3].display = FALSE;
				Enemy[3] = { 0 };
				count = 0;
				E_count--;
				location();
				Hiku();
				break;
		}
		else if (E_CenterX > 365 && E_CenterX < 435 && PAD_INPUT::OnButton(XINPUT_BUTTON_B)) { //５枚目
				Judgefuda.Img = Enemy[4].Img;
				Judgefuda.month = Enemy[4].month;
				Judgefuda.Hikari = Enemy[4].Hikari;
				Judgefuda.Tan = Enemy[4].Tan;
				Judgefuda.Tane = Enemy[4].Tane;
				Judgefuda.Kas = Enemy[4].Kas;
				Judgefuda.display = TRUE;
				Enemy[4].display = FALSE;
				Enemy[4] = { 0 };
				count = 0;
				E_count--;
				location();
				Hiku(); 
				break;
		}
		else if (E_CenterX > 445 && E_CenterX < 515 && PAD_INPUT::OnButton(XINPUT_BUTTON_B)) { //６枚目
				Judgefuda.Img = Enemy[5].Img;
				Judgefuda.month = Enemy[5].month;
				Judgefuda.Hikari = Enemy[5].Hikari;
				Judgefuda.Tan = Enemy[5].Tan;
				Judgefuda.Tane = Enemy[5].Tane;
				Judgefuda.Kas = Enemy[5].Kas;
				Judgefuda.display = 1;
				Enemy[5].display = FALSE;
				Enemy[5] = { 0 };
				count = 0;
				E_count--;
				location();
				Hiku();
				break;
		}
		else if (E_CenterX > 525 && E_CenterX < 595 && PAD_INPUT::OnButton(XINPUT_BUTTON_B)) { //７枚目
				Judgefuda.Img = Enemy[6].Img;
				Judgefuda.month = Enemy[6].month;
				Judgefuda.Hikari = Enemy[6].Hikari;
				Judgefuda.Tane = Enemy[6].Tane;
				Judgefuda.Tan = Enemy[6].Tan;
				Judgefuda.Kas = Enemy[6].Kas;
				Judgefuda.display = TRUE;
				Enemy[6].display = FALSE;
				Enemy[6] = { 0 };
				count = 0;
				E_count--;
				location();
				Hiku();
				break;
		}
		else if (E_CenterX > 605 && E_CenterX < 675 && PAD_INPUT::OnButton(XINPUT_BUTTON_B)) { //８枚目
				Judgefuda.Img = Enemy[7].Img;
				Judgefuda.month = Enemy[7].month;
				Judgefuda.Hikari = Enemy[7].Hikari;
				Judgefuda.Tan = Enemy[7].Tan;
				Judgefuda.Tane = Enemy[7].Tane;
				Judgefuda.Kas = Enemy[7].Kas;
				Judgefuda.display = TRUE;
				Enemy[7].display = FALSE;
				Enemy[7] = { 0 };
				count = 0;
				E_count--;
				location();
				Hiku();
				break;
			}
		break;
	}
}
//山札から引く
void Hanafuda::Hiku(){
	yamafuda.Img = Fuda[yama[x]].Img;
	yamafuda.month = Fuda[yama[x]].month;
	yamafuda.Kas = Fuda[yama[x]].Kas;
	yamafuda.Tan = Fuda[yama[x]].Tan;
	yamafuda.Tane = Fuda[yama[x]].Tane;
	yamafuda.Hikari = Fuda[yama[x]].Hikari;
	Y_month = yamafuda.month;
	yamafuda.display = TRUE;
	x++;
	count = 1;
	location();
	Move();
}
void Hanafuda::Sutefuda()
{
	int i = 0;
	switch (Sute)
	{
	case 0: //手札から
		i = 0;
		do{
			if (Field[i].month == 0) {
				Field[i].Img = Judgefuda.Img;
				Field[i].month = Judgefuda.month;
				Field[i].Hikari = Judgefuda.Hikari;
				Field[i].Tane = Judgefuda.Tane;
				Field[i].Tan = Judgefuda.Kas;
				Field[i].Kas = Judgefuda.Kas;
				Field[i].display = TRUE;
				Judgefuda.display = FALSE;
				Judgefuda = { 0 };
				FieldCount++;
				break;
			}
			i++;
		} while (i <= FieldCount);
		if (i > FieldCount) {
			Field[FieldCount].Img = Judgefuda.Img;
			Field[FieldCount].month = Judgefuda.month;
			Field[FieldCount].Hikari = Judgefuda.Hikari;
			Field[FieldCount].Tane = Judgefuda.Tane;
			Field[FieldCount].Tan = Judgefuda.Kas;
			Field[FieldCount].Kas = Judgefuda.Kas;
			Field[FieldCount].display = TRUE;
			Judgefuda.display = FALSE;
			Judgefuda = { 0 };
			FieldCount++;
			break;
		}
		break;
	case 1: //山札から
		i = 0;
	do{
			if (Field[i].display == FALSE) {
				Field[i].Img = yamafuda.Img;
				Field[i].month = yamafuda.month;
				Field[i].Hikari = yamafuda.Hikari;
				Field[i].Tane = yamafuda.Tane;
				Field[i].Tan = yamafuda.Tan;
				Field[i].Kas = yamafuda.Kas;
				Field[i].display = TRUE;
				yamafuda = { 0 };
				FieldCount++;
				break;
			}
			i++;
	} while (i <= FieldCount);
	if (i > FieldCount) {
		Field[FieldCount].Img = yamafuda.Img;
		Field[FieldCount].month = yamafuda.month;
		Field[FieldCount].Hikari = yamafuda.Hikari;
		Field[FieldCount].Tane = yamafuda.Tane;
		Field[FieldCount].Tan = yamafuda.Kas;
		Field[FieldCount].Kas = yamafuda.Kas;
		Field[FieldCount].display = TRUE;
		yamafuda.display = FALSE;
		yamafuda = { 0 };
		FieldCount++;
		break;
		}
	break;
	}

}

void Hanafuda::Judge()
{
	if (P_Score > E_Score) {
		P_Win = TRUE;
		E_Win = FALSE;
	}
	else if (P_Score < E_Score) {
		P_Win = FALSE;
		E_Win = TRUE;
	}
}

//役判定
void Hanafuda::Tane()
{
	if (P_Motifuda.tane_count >= 5) {
		P_Motifuda.TaneYaku = TRUE;
		P_Score += 1;
	}
	if (E_Motifuda.tane_count >= 5) {
		E_Motifuda.TaneYaku = TRUE;
		E_Score += 1;
	}
}
void Hanafuda::Tan()
{
	if (P_Motifuda.tan_count >= 5) {
		P_Motifuda.TanYaku = TRUE;
		P_Score += 1;
	}
	if (E_Motifuda.tan_count >= 5) {
		E_Motifuda.TanYaku = TRUE;
		E_Score += 1;
	}
}
void Hanafuda::Kas()
{
	if (P_Motifuda.kas_count >= 5) {
		P_Motifuda.KasYaku = TRUE;
		P_Score += 1;
	}
	if (E_Motifuda.kas_count >= 5) {
		E_Motifuda.KasYaku = TRUE;
		E_Score += 1;
	}
}
//取り札を持ち札に移動
void Hanafuda::Move() { 
	switch (MoveJudge) {
	case 0: // プレイヤーの場合
		//光札
		if (torifuda[0].Hikari == TRUE && P_Motifuda.hikari_count < 4) {
			P_Motifuda.hikari[P_Motifuda.hikari_count].Img = torifuda[0].Img;
			P_Motifuda.hikari[0].display = TRUE;
			P_Motifuda.hikari_count += 1;
		}
		if (torifuda[1].Hikari == TRUE && P_Motifuda.hikari_count < 4) {
			P_Motifuda.hikari[P_Motifuda.hikari_count].Img = torifuda[1].Img;
			P_Motifuda.hikari[P_Motifuda.hikari_count].display = TRUE;
			P_Motifuda.hikari_count += 1;
		}
		if (torifuda[2].Hikari == TRUE && P_Motifuda.hikari_count < 4) {
			P_Motifuda.hikari[P_Motifuda.hikari_count].Img = torifuda[2].Img;
			P_Motifuda.hikari[P_Motifuda.hikari_count].display = TRUE;
			P_Motifuda.hikari_count += 1;
		}
		if (torifuda[3].Hikari == TRUE && P_Motifuda.hikari_count < 4) {
			P_Motifuda.hikari[P_Motifuda.hikari_count].Img = torifuda[3].Img;
			P_Motifuda.hikari[P_Motifuda.hikari_count].display = TRUE;
			P_Motifuda.hikari_count += 1;
		}
		if (torifuda[4].Hikari == TRUE && P_Motifuda.hikari_count < 4) {
			P_Motifuda.hikari[P_Motifuda.hikari_count].Img = torifuda[4].Img;
			P_Motifuda.hikari[P_Motifuda.hikari_count].display = TRUE;
			P_Motifuda.hikari_count += 1;
		}
		if (torifuda[5].Hikari == TRUE && P_Motifuda.hikari_count < 4) {
			P_Motifuda.hikari[P_Motifuda.hikari_count].Img = torifuda[5].Img;
			P_Motifuda.hikari[P_Motifuda.hikari_count].display = TRUE;
			P_Motifuda.hikari_count += 1;
		}
		if (torifuda[6].Hikari == TRUE && P_Motifuda.hikari_count < 4) {
			P_Motifuda.hikari[P_Motifuda.hikari_count].Img = torifuda[6].Img;
			P_Motifuda.hikari[P_Motifuda.hikari_count].display = TRUE;
			P_Motifuda.hikari_count += 1;
		}
		if (torifuda[7].Hikari == TRUE && P_Motifuda.hikari_count < 4) {
			P_Motifuda.hikari[P_Motifuda.hikari_count].Img = torifuda[7].Img;
			P_Motifuda.hikari[P_Motifuda.hikari_count].display = TRUE;
			P_Motifuda.hikari_count += 1;
		}
		//タネ札
		if (torifuda[0].Tane == TRUE) {
			P_Motifuda.tane[P_Motifuda.tane_count].Img = torifuda[0].Img;
			P_Motifuda.tane[P_Motifuda.tane_count].display = TRUE;
			P_Motifuda.tane_count += 1;
		}
		if (torifuda[1].Tane == TRUE) {
			P_Motifuda.tane[P_Motifuda.tane_count].Img = torifuda[1].Img;
			P_Motifuda.tane[P_Motifuda.tane_count].display = TRUE;
			P_Motifuda.tane_count += 1;
		}
		if (torifuda[2].Tane == TRUE) {
			P_Motifuda.tane[P_Motifuda.tane_count].Img = torifuda[2].Img;
			P_Motifuda.tane[P_Motifuda.tane_count].display = TRUE;
			P_Motifuda.tane_count += 1;
		}
		if (torifuda[3].Tane == TRUE) {
			P_Motifuda.tane[P_Motifuda.tane_count].Img = torifuda[3].Img;
			P_Motifuda.tane[3].display = TRUE;
			P_Motifuda.tane_count += 1;
		}
		if (torifuda[4].Tane == TRUE) {
			P_Motifuda.tane[P_Motifuda.tane_count].Img = torifuda[4].Img;
			P_Motifuda.tane[P_Motifuda.tane_count].display = TRUE;
			P_Motifuda.tane_count += 1;
		}
		if (torifuda[5].Tane == TRUE) {
			P_Motifuda.tane[P_Motifuda.tane_count].Img = torifuda[5].Img;
			P_Motifuda.tane[P_Motifuda.tane_count].display = TRUE;
			P_Motifuda.tane_count += 1;
		}
		if (torifuda[6].Tane == TRUE) {
			P_Motifuda.tane[6].Img = torifuda[6].Img;
			P_Motifuda.tane[P_Motifuda.tane_count].display = TRUE;
			P_Motifuda.tane_count += 1;
		}
		if (torifuda[7].Tane == TRUE) {
			P_Motifuda.tane[P_Motifuda.tane_count].Img = torifuda[7].Img;
			P_Motifuda.tane[P_Motifuda.tane_count].display = TRUE;
			P_Motifuda.tane_count += 1;
		}
		//タン
		if (torifuda[0].Tan == TRUE) {
			P_Motifuda.tan[P_Motifuda.tan_count].Img = torifuda[0].Img;
			P_Motifuda.tan_count += 1;
			P_Motifuda.tan[P_Motifuda.tan_count].display = TRUE;
		}
		if (torifuda[1].Tan == TRUE) {
			P_Motifuda.tan[P_Motifuda.tan_count].Img = torifuda[1].Img;
			P_Motifuda.tan_count += 1;
			P_Motifuda.tan[P_Motifuda.tan_count].display = TRUE;
		}
		if (torifuda[2].Tan == TRUE) {
			P_Motifuda.tan[P_Motifuda.tan_count].Img = torifuda[2].Img;
			P_Motifuda.tan_count += 1;
			P_Motifuda.tan[P_Motifuda.tan_count].display = TRUE;
		}
		if (torifuda[3].Tan == TRUE) {
			P_Motifuda.tan[P_Motifuda.tan_count].Img = torifuda[3].Img;
			P_Motifuda.tan_count += 1;
			P_Motifuda.tan[P_Motifuda.tan_count].display = TRUE;
		}
		if (torifuda[4].Tan == TRUE) {
			P_Motifuda.tan[P_Motifuda.tan_count].Img = torifuda[4].Img;
			P_Motifuda.tan[P_Motifuda.tan_count].display = TRUE;
			P_Motifuda.tan_count += 1;
		}
		if (torifuda[5].Tan == TRUE) {
			P_Motifuda.tan[P_Motifuda.tan_count].Img = torifuda[5].Img;
			P_Motifuda.tan[P_Motifuda.tan_count].display = TRUE;
			P_Motifuda.tan_count += 1;
		}
		if (torifuda[6].Tan == TRUE) {
			P_Motifuda.tan[P_Motifuda.tan_count].Img = torifuda[6].Img;
			P_Motifuda.tan[P_Motifuda.tan_count].display = TRUE;
			P_Motifuda.tan_count += 1;
		}
		if (torifuda[7].Tan == TRUE) {
			P_Motifuda.tan[P_Motifuda.tan_count].Img = torifuda[7].Img;
			P_Motifuda.tan[P_Motifuda.tan_count].display = TRUE;
			P_Motifuda.tan_count += 1;
		}
		//カス
		if (torifuda[0].Kas == TRUE) {
			P_Motifuda.kas[P_Motifuda.kas_count].Img = torifuda[0].Img;
			P_Motifuda.kas[P_Motifuda.kas_count].display = TRUE;
			P_Motifuda.kas_count += 1;
		}
		if (torifuda[1].Kas == TRUE) {
			P_Motifuda.kas[P_Motifuda.kas_count].Img = torifuda[1].Img;
			P_Motifuda.kas[P_Motifuda.kas_count].display = TRUE;
			P_Motifuda.kas_count += 1;
		}
		if (torifuda[2].Kas == TRUE)
		{
			P_Motifuda.kas[P_Motifuda.kas_count].Img = torifuda[2].Img;
			P_Motifuda.kas[P_Motifuda.kas_count].display = TRUE;
			P_Motifuda.kas_count += 1;
		}
		if (torifuda[3].Kas == TRUE) {
			P_Motifuda.kas[P_Motifuda.kas_count].Img = torifuda[3].Img;
			P_Motifuda.kas[P_Motifuda.kas_count].display = TRUE;
			P_Motifuda.kas_count += 1;
		}
		if (torifuda[4].Kas == TRUE) {
			P_Motifuda.kas[P_Motifuda.kas_count].Img = torifuda[4].Img;
			P_Motifuda.kas[P_Motifuda.kas_count].display = TRUE;
			P_Motifuda.kas_count += 1;
		}
		if (torifuda[5].Kas == TRUE) {
			P_Motifuda.kas[P_Motifuda.kas_count].Img = torifuda[5].Img;
			P_Motifuda.kas[P_Motifuda.kas_count].display = TRUE;
			P_Motifuda.kas_count += 1;
		}
		if (torifuda[6].Kas == TRUE) {
			P_Motifuda.kas[P_Motifuda.kas_count].Img = torifuda[6].Img;
			P_Motifuda.kas[P_Motifuda.kas_count].display = TRUE;
			P_Motifuda.kas_count += 1;
		}
		if (torifuda[7].Kas == TRUE) {
			P_Motifuda.kas[P_Motifuda.kas_count].Img = torifuda[7].Img;
			P_Motifuda.kas[P_Motifuda.kas_count].display = TRUE;
			P_Motifuda.kas_count += 1;
		}
		if (P_turn == TRUE && E_turn == FALSE && Phase == 2) {
			P_turn = FALSE;
			E_turn = TRUE;
			Phase = 3;
			MoveJudge = 1;
		}
		break;
		//敵の場合
	case 1:
		//光札
		if (torifuda[0].Hikari == TRUE && E_Motifuda.hikari_count < 4) {
			E_Motifuda.hikari[E_Motifuda.hikari_count].Img = torifuda[0].Img;
			E_Motifuda.hikari[0].display = TRUE;
			E_Motifuda.hikari_count++;
		}
		if (torifuda[1].Hikari == TRUE && E_Motifuda.hikari_count < 4) {
			E_Motifuda.hikari[E_Motifuda.hikari_count].Img = torifuda[1].Img;
			E_Motifuda.hikari[E_Motifuda.hikari_count].display = TRUE;
			E_Motifuda.hikari_count++;
		}
		if (torifuda[2].Hikari == TRUE && E_Motifuda.hikari_count < 4) {
			E_Motifuda.hikari[E_Motifuda.hikari_count].Img = torifuda[2].Img;
			E_Motifuda.hikari[E_Motifuda.hikari_count].display = TRUE;
			E_Motifuda.hikari_count++;
		}
		if (torifuda[3].Hikari == TRUE && E_Motifuda.hikari_count < 4) {
			E_Motifuda.hikari[E_Motifuda.hikari_count].Img = torifuda[3].Img;
			E_Motifuda.hikari[E_Motifuda.hikari_count].display = TRUE;
			E_Motifuda.hikari_count++;
		}
		if (torifuda[4].Hikari == TRUE && E_Motifuda.hikari_count < 4) {
			E_Motifuda.hikari[E_Motifuda.hikari_count].Img = torifuda[4].Img;
			E_Motifuda.hikari[E_Motifuda.hikari_count].display = TRUE;
			E_Motifuda.hikari_count++;
		}
		if (torifuda[5].Hikari == TRUE && E_Motifuda.hikari_count < 4) {
			E_Motifuda.hikari[E_Motifuda.hikari_count].Img = torifuda[5].Img;
			E_Motifuda.hikari[E_Motifuda.hikari_count].display = TRUE;
			E_Motifuda.hikari_count += 1;
		}
		if (torifuda[6].Hikari == TRUE && E_Motifuda.hikari_count < 4) {
			E_Motifuda.hikari[E_Motifuda.hikari_count].Img = torifuda[6].Img;
			E_Motifuda.hikari[E_Motifuda.hikari_count].display = TRUE;
			E_Motifuda.hikari_count += 1;
		}
		if (torifuda[7].Hikari == TRUE && E_Motifuda.hikari_count < 4) {
			E_Motifuda.hikari[E_Motifuda.hikari_count].Img = torifuda[7].Img;
			E_Motifuda.hikari[E_Motifuda.hikari_count].display = TRUE;
			E_Motifuda.hikari_count += 1;
		}
		//タネ札
		if (torifuda[0].Tane == TRUE) {
			E_Motifuda.tane[E_Motifuda.tane_count].Img = torifuda[0].Img;
			E_Motifuda.tane[E_Motifuda.tane_count].display = TRUE;
			E_Motifuda.tane_count += 1;
		}
		if (torifuda[1].Tane == TRUE) {
			E_Motifuda.tane[E_Motifuda.tane_count].Img = torifuda[1].Img;
			E_Motifuda.tane[E_Motifuda.tane_count].display = TRUE;
			E_Motifuda.tane_count += 1;
		}
		if (torifuda[2].Tane == TRUE) {
			E_Motifuda.tane[E_Motifuda.tane_count].Img = torifuda[2].Img;
			E_Motifuda.tane[E_Motifuda.tane_count].display = TRUE;
			E_Motifuda.tane_count += 1;
		}
		if (torifuda[3].Tane == TRUE) {
			E_Motifuda.tane[E_Motifuda.tane_count].Img = torifuda[3].Img;
			E_Motifuda.tane[3].display = TRUE;
			E_Motifuda.tane_count += 1;
		}
		if (torifuda[4].Tane == TRUE) {
			E_Motifuda.tane[E_Motifuda.tane_count].Img = torifuda[4].Img;
			E_Motifuda.tane[E_Motifuda.tane_count].display = TRUE;
			E_Motifuda.tane_count += 1;
		}
		if (torifuda[5].Tane == TRUE) {
			E_Motifuda.tane[E_Motifuda.tane_count].Img = torifuda[5].Img;
			E_Motifuda.tane[E_Motifuda.tane_count].display = TRUE;
			E_Motifuda.tane_count += 1;
		}
		if (torifuda[6].Tane == TRUE) {
			E_Motifuda.tane[6].Img = torifuda[6].Img;
			E_Motifuda.tane[E_Motifuda.tane_count].display = TRUE;
			E_Motifuda.tane_count += 1;
		}
		if (torifuda[7].Tane == TRUE) {
			E_Motifuda.tane[E_Motifuda.tane_count].Img = torifuda[7].Img;
			E_Motifuda.tane[E_Motifuda.tane_count].display = TRUE;
			E_Motifuda.tane_count += 1;
		}
		//タン
		if (torifuda[0].Tan == TRUE) {
			E_Motifuda.tan[E_Motifuda.tan_count].Img = torifuda[0].Img;
			E_Motifuda.tan_count += 1;
			E_Motifuda.tan[E_Motifuda.tan_count].display = TRUE;
		}
		if (torifuda[1].Tan == TRUE) {
			E_Motifuda.tan[E_Motifuda.tan_count].Img = torifuda[1].Img;
			E_Motifuda.tan_count += 1;
			E_Motifuda.tan[E_Motifuda.tan_count].display = TRUE;
		}
		if (torifuda[2].Tan == TRUE) {
			E_Motifuda.tan[E_Motifuda.tan_count].Img = torifuda[2].Img;
			E_Motifuda.tan_count += 1;
			E_Motifuda.tan[E_Motifuda.tan_count].display = TRUE;
		}
		if (torifuda[3].Tan == TRUE) {
			E_Motifuda.tan[E_Motifuda.tan_count].Img = torifuda[3].Img;
			E_Motifuda.tan_count += 1;
			E_Motifuda.tan[E_Motifuda.tan_count].display = TRUE;
		}
		if (torifuda[4].Tan == TRUE) {
			E_Motifuda.tan[E_Motifuda.tan_count].Img = torifuda[4].Img;
			E_Motifuda.tan[E_Motifuda.tan_count].display = TRUE;
			E_Motifuda.tan_count += 1;
		}
		if (torifuda[5].Tan == TRUE) {
			E_Motifuda.tan[E_Motifuda.tan_count].Img = torifuda[5].Img;
			E_Motifuda.tan[E_Motifuda.tan_count].display = TRUE;
			E_Motifuda.tan_count += 1;
		}
		if (torifuda[6].Tan == TRUE) {
			E_Motifuda.tan[E_Motifuda.tan_count].Img = torifuda[6].Img;
			E_Motifuda.tan[E_Motifuda.tan_count].display = TRUE;
			E_Motifuda.tan_count += 1;
			torifuda[6].Img = 0;
		}
		if (torifuda[7].Tan == TRUE) {
			E_Motifuda.tan[E_Motifuda.tan_count].Img = torifuda[7].Img;
			E_Motifuda.tan[E_Motifuda.tan_count].display = TRUE;
			E_Motifuda.tan_count += 1;
		}
		//カス
		if (torifuda[0].Kas == TRUE) {
			E_Motifuda.kas[E_Motifuda.kas_count].Img = torifuda[0].Img;
			E_Motifuda.kas[E_Motifuda.kas_count].display = TRUE;
			E_Motifuda.kas_count += 1;
		}
		if (torifuda[1].Kas == TRUE) {
			E_Motifuda.kas[E_Motifuda.kas_count].Img = torifuda[1].Img;
			E_Motifuda.kas[E_Motifuda.kas_count].display = TRUE;
			E_Motifuda.kas_count += 1;
		}
		if (torifuda[2].Kas == TRUE)
		{
			E_Motifuda.kas[E_Motifuda.kas_count].Img = torifuda[2].Img;
			E_Motifuda.kas[E_Motifuda.kas_count].display = TRUE;
			E_Motifuda.kas_count += 1;
		}
		if (torifuda[3].Kas == TRUE) {
			E_Motifuda.kas[E_Motifuda.kas_count].Img = torifuda[3].Img;
			E_Motifuda.kas[E_Motifuda.kas_count].display = TRUE;
			E_Motifuda.kas_count += 1;
		}
		if (torifuda[4].Kas == TRUE) {
			E_Motifuda.kas[E_Motifuda.kas_count].Img = torifuda[4].Img;
			E_Motifuda.kas[E_Motifuda.kas_count].display = TRUE;
			E_Motifuda.kas_count += 1;
		}
		if (torifuda[5].Kas == TRUE) {
			E_Motifuda.kas[E_Motifuda.kas_count].Img = torifuda[5].Img;
			E_Motifuda.kas[E_Motifuda.kas_count].display = TRUE;
			E_Motifuda.kas_count += 1;
		}
		if (torifuda[6].Kas == TRUE) {
			E_Motifuda.kas[E_Motifuda.kas_count].Img = torifuda[6].Img;
			E_Motifuda.kas[E_Motifuda.kas_count].display = TRUE;
			E_Motifuda.kas_count += 1;
		}
		if (torifuda[7].Kas == TRUE) {
			E_Motifuda.kas[E_Motifuda.kas_count].Img = torifuda[7].Img;
			E_Motifuda.kas[E_Motifuda.kas_count].display = TRUE;
			E_Motifuda.kas_count += 1;
		}
		if (E_turn == TRUE && P_turn == FALSE && Phase == 3 ) {
			E_turn = FALSE;
			P_turn = TRUE;
			Phase = 2;
		}
		break;
	}
	Judgefuda.display = FALSE;
	yamafuda.display = FALSE;
	for (int i = 0; i < 8; i++) {
		torifuda[i].Img = 0;
		torifuda[i].month = 0;
	}
}
