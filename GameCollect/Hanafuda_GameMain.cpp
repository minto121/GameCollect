#include"DxLib.h"
#include"Hanafuda_GameMain.h"
#include"Math.h"
#include"Time.h"
#include"PadInput.h"
#include"stdlib.h"
Hanafuda::Hanafuda()
{
	Stage = LoadGraph("images/Hanafuda/BG_Dummy.png");
	UraImg = LoadGraph("images/Hanafuda/HanafudaCard_Back.png");
	if(LoadDivGraph("images/Hanafuda/HanafudaCard.png", 48,8,6,128,256,FudaImg)){}

	//for (int i = 0; i < 48; i++) {
	//	Fuda.fuda[i] = FudaImg[i]; //構造体の領域に札の画像を格納
	//}
	E_fudaImg = FudaImg[0];
	P_fudaImg = FudaImg[0];
	MouseX = 0;
	MouseY = 0;
	i = 0;
	j = 0;
	OyaGimeflg = 0; //親決めのフラグ
	Startflg = 0;
	P_FudaX = 80;
	P_FudaY = 500;
	E_FudaX = 80;
	E_FudaY = 150;
	Judgeflg = 0; //親決め用フラグ
	Playerflg = 0;
	P_judge = 0;
	E_judge = 0;
	Partnerflg = 0;
	shuffleflg = 0;
	Phase = 0;
	Monthflg = 0;
	tick = 0;
	Gameflg = 0;
	n = 0;
	b = 0;
	Fieldflg = 0;
	P_shuffleflg = 0;
	E_shuffleflg = 0;
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
		OyaGime();
		if (CheckHitKey(KEY_INPUT_0)) {
			Phase = 1;
			tick = 0;
		}
		break;
	case 1: //札配布
		shuffleFuda();
		if (CheckHitKey(KEY_INPUT_P)) {
			Phase = 2;
		}
		break;
	}
	return this;
}
void Hanafuda::Draw()const
{
	//DrawRotaGraph(/*FudaX +*/ 280, /*FudaY +*/ 100, 0.7f, 0, Fuda.fuda[47], FALSE);
	//DrawRotaGraph(400, 400, 0.7f, 0, Fuda.fuda[2], FALSE);
	//DrawFormatString(0, 40, GetColor(255, 0, 0), "shuffle:%d", shuffleflg);
	SetFontSize(12);
	DrawFormatString(700, 60, GetColor(255, 0, 0), "Fieldflg:%d", Fieldflg);
	DrawFormatString(700, 80, GetColor(255, 0, 0), "P_shuffleflg:%d", P_shuffleflg);
	DrawFormatString(700, 100, GetColor(255, 0, 0), "P_shuffleflg:%d", P_shuffleflg);
	DrawFormatString(700, 0, GetColor(255, 0, 0), "Phase:%d", Phase);
	DrawFormatString(700, 20, GetColor(255, 0, 0), " マウス座標：X座標 %d Y座標 %d ", MouseX, MouseY);
	switch (Phase)
	{
	case 0: //親決め
			DrawRotaGraph( 280, 100, 0.6f, 0, E_fudaImg, FALSE);
			//DrawFormatString(FudaX + 300, FudaY + 120, GetColor(255, 0, 0), "%d月", E_judge);
			DrawRotaGraph(280, 400,0.7f,0, P_fudaImg, FALSE);
			/*DrawFormatString(FudaX + 300, FudaY + 420, GetColor(255, 0, 0), "%d月", P_judge);*/
			/*f (Judgeflg == 1)
				DrawFormatString(300, 360, GetColor(255, 0, 0), "あなたが親（先手）です");
			}
			else {
				DrawFormatString(300, 360, GetColor(255, 0, 0), "相手が親（先手）です");
			}*/
			break;
	case 1:
	case 2:
	case 3://札配布
		//DrawFormatString(400, 150, GetColor(255, 0, 0), "P_numhand[0]:%d", P_numhand[0]);
		//DrawFormatString(400, 400, GetColor(255, 0, 0), "P_numhand[1]:%d", P_numhand[1]);
	 
			//Player
			DrawRotaGraph(80,  600, 0.6f, 0, P_numhand[0], TRUE);
			DrawRotaGraph(160, 600, 0.6f, 0, P_numhand[1], TRUE);
			DrawRotaGraph(240, 600, 0.6f, 0, P_numhand[2], TRUE);
			DrawRotaGraph(320, 600, 0.6f, 0, P_numhand[3], TRUE);
			DrawRotaGraph(400, 600, 0.6f, 0, P_numhand[4], TRUE);
			DrawRotaGraph(480, 600, 0.6f, 0, P_numhand[5], TRUE);
			DrawRotaGraph(560, 600, 0.6f, 0, P_numhand[6], TRUE);
			DrawRotaGraph(640, 600, 0.6f, 0, P_numhand[7], TRUE);
			//Enemy
			DrawRotaGraph(80,  100, 0.6f, 0, E_numhand[0], TRUE);
			DrawRotaGraph(160, 100, 0.6f, 0, E_numhand[1], TRUE);
			DrawRotaGraph(240, 100, 0.6f, 0, E_numhand[2], TRUE);
			DrawRotaGraph(320, 100, 0.6f, 0, E_numhand[3], TRUE);
			DrawRotaGraph(400, 100, 0.6f, 0, E_numhand[4], TRUE);
			DrawRotaGraph(480, 100, 0.6f, 0, E_numhand[5], TRUE);
			DrawRotaGraph(560, 100, 0.6f, 0, E_numhand[6], TRUE);
			DrawRotaGraph(640, 100, 0.6f, 0, E_numhand[7], TRUE);
			//Field1
			DrawRotaGraph(400, 250, 0.6f, 0, Field[0], TRUE);
			DrawRotaGraph(480, 250, 0.6f, 0, Field[1], TRUE);
			DrawRotaGraph(560, 250, 0.6f, 0, Field[2], TRUE);
			DrawRotaGraph(640, 250, 0.6f, 0, Field[3], TRUE);
			//Field2
			DrawRotaGraph(400, 400, 0.6f, 0, Field[4], TRUE);
			DrawRotaGraph(480, 400, 0.6f, 0, Field[5], TRUE);
			DrawRotaGraph(560, 400, 0.6f, 0, Field[6], TRUE);
			DrawRotaGraph(640, 400, 0.6f, 0, Field[7], TRUE);
		break;
	case 4: //親番	
		break;
	case 5: //子番
		break;
	case 6:  //リザルト
		break;
		}
}


void Hanafuda:: OyaGime()
{
	tick++;
	if (OyaGimeflg == 0 && tick == 1) {
		srand(time(NULL));
		int num = rand() % 47;
		E_fudaImg = FudaImg[num];
		int n = rand() % 47;
		P_fudaImg = FudaImg[n];
		OyaGimeflg = 1;
	}
}
void Hanafuda::shuffleFuda()
{
	int count = 0;
	int c = 0;
	int range = 48;
	int min = 0;
	int a;
	int x2, y2;
	int s = 0;
	int x = 0;
	int y = 0;
	srand(time(NULL));
	if(CheckHitKey(KEY_INPUT_1) || PAD_INPUT::OnButton(XINPUT_BUTTON_A)){
			for (x = 0; x < FUDA; x++) {
					do {
						s = rand() % range + min;
						Field[x] = FudaImg[s];
						for (y = 0; y < x; y++) {
								if (Field[x] == Field[y]) break;
								}
					} while (x != y);
				}
			}

	if (CheckHitKey(KEY_INPUT_2) || PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		P_shuffleflg++;
		if (P_shuffleflg == 1) {
			for (x = 0; x < FUDA; x++) {
				do {
					s = rand() % range + min;
					P_numhand[x] = FudaImg[s];
					s = rand() % range + min;
					E_numhand[x] = FudaImg[s];
					for (y = 0; y < x; y++) {
						if(P_numhand[x] == P_numhand[y] || P_numhand[x] == Field[y] || P_numhand[x] == E_numhand[y]
							|| E_numhand[x] == E_numhand[y] || E_numhand[x] == P_numhand[y] || E_numhand[x] == Field[y])break;
					}
				} while (x != y);
			}
		}
	}
	/*if (CheckHitKey(KEY_INPUT_3) || PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		E_shuffleflg++;
		if (E_shuffleflg == 1) {
			for (x = 0; x < FUDA; x++) {
				do {
					s = rand() % range + min;
					E_numhand[x] = FudaImg[s];
					for (x2 = 0; x2 < x; x2++) {
						if(E_numhand[x] == E_numhand[x2] || E_numhand[x] == P_numhand[x2]
						|| E_numhand[x] == Field[x2]) break;
					}
				} while (x != x2);
			}
		}
	}*/
}	
//void Hanafuda::Month() { //月判定
//	//プレイヤー月判定
//	switch (i) {
//	case 0:
//	case 1:
//	case 2:
//	case 3:
//		P_judge = 1;
//		break;
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//		P_judge = 2;
//		break;
//	case 8:
//	case 9:
//	case 10:
//	case 11:
//		P_judge = 3;
//		break;
//	case 12:
//	case 13:
//	case 14:
//	case 15:
//		P_judge = 4;
//		break;
//	case 16:
//	case 17:
//	case 18:
//	case 19:
//		P_judge = 5;
//		break;
//	case 20:
//	case 21:
//	case 22:
//	case 23:
//		P_judge = 6;
//		break;
//	case 24:
//	case 25:
//	case 26:
//	case 27:
//		P_judge = 7;
//		break;
//	case 28:
//	case 29:
//	case 30:
//	case 31:
//		P_judge = 8;
//		break;
//	case 32:
//	case 33:
//	case 34:
//	case 35:
//		P_judge = 9;
//		break;
//	case 36:
//	case 37:
//	case 38:
//	case 39:
//		P_judge = 10;
//		break;
//	case 40:
//	case 41:
//	case 42:
//	case 43:
//		P_judge = 11;
//		break;
//	case 44:
//	case 45:
//	case 46:
//	case 47:
//		P_judge = 12;
//		break;
//	}
//	//AI用月判定
//	switch (j) {
//	case 0:
//	case 1:
//	case 2:
//	case 3:
//		E_judge = 1;
//		break;
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//		E_judge = 2;
//		break;
//	case 8:
//	case 9:
//	case 10:
//	case 11:
//		E_judge = 3;
//		break;
//	case 12:
//	case 13:
//	case 14:
//	case 15:
//		E_judge = 4;
//		break;
//	case 16:
//	case 17:
//	case 18:
//	case 19:
//		E_judge = 5;
//		break;
//	case 20:
//	case 21:
//	case 22:
//	case 23:
//		E_judge = 6;
//		break;
//	case 24:
//	case 25:
//	case 26:
//	case 27:
//		E_judge = 7;
//		break;
//	case 28:
//	case 29:
//	case 30:
//	case 31:
//		E_judge = 8;
//		break;
//	case 32:
//	case 33:
//	case 34:
//	case 35:
//		E_judge = 9;
//		break;
//	case 36:
//	case 37:
//	case 38:
//	case 39:
//		E_judge = 10;
//		break;
//	case 40:
//	case 41:
//	case 42:
//	case 43:
//		E_judge = 11;
//		break;
//	case 44:
//	case 45:
//	case 46:
//	case 47:
//		E_judge = 12;
//		break;
//	}
