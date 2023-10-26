#include"DxLib.h"
#include"Hanafuda_GameMain.h"
#include"Math.h"
#include"Time.h"
#include"PadInput.h"




Hanafuda::Hanafuda()
{
	Stage = LoadGraph("images/Hanafuda/BG_Dummy.png");
	UraImg = LoadGraph("images/Hanafuda/HanafudaCard_Back.png");
	U_Img = UraImg;
	if(LoadDivGraph("images/Hanafuda/HanafudaCard.png", 48,8,6,128,256,FudaImg)){}

	for (int i = 0; i < 48; i++) {
		Fuda.fuda[i] = FudaImg[i]; //構造体の領域に札の画像を格納
	}
	E_fudaImg = FudaImg[0];
	P_fudaImg = FudaImg[0];
	F_Img = FudaImg[0];
	MouseX = 0;
	MouseY = 0;
	i = 0;
	j = 0;
	OyaGimeflg = 0; //親決めのフラグ
	Startflg = 0;
	FudaX = 0;
	FudaY = 0;
	Judgeflg = 0; //親決め用フラグ
	Playerflg = 0;
	P_judge = 0;
	E_judge = 0;
	Partnerflg = 0;
	shuffleflg = 0;
	Phase = 0;
	Monthflg = 0;
}
Hanafuda::~Hanafuda()
{
	DeleteGraph(Stage);
	//DeleteGraph(HudaImg);
}

AbstractScene* Hanafuda::Update()
{
	GetMousePoint(&MouseX, &MouseY);
	
	switch (Phase)
	{
	case 0:
		if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true))
		{
			Phase = 1;
		}
		break;
	case 1: //親決め
			OyaGime();
		break;
	case 2: //札配布
		if (/*shuffleflg == 1 || */PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
			shuffleFuda();
			Phase++;
		}
		break;
	case 3: //親番
		break;
	case 4: //子番
		break;
	case 5: //リザルト
		break;
	}
	
	return this;
}
void Hanafuda::Draw()const
{
	//DrawRotaGraph(/*FudaX +*/ 280, /*FudaY +*/ 100, 0.7f, 0, Fuda.fuda[47], FALSE);
	//DrawRotaGraph(400, 400, 0.7f, 0, Fuda.fuda[2], FALSE);

	DrawFormatString(0, 0, GetColor(255, 0, 0), "Phase:%d", Phase);
	DrawFormatString(0, 20, GetColor(255, 0, 0), " マウス座標：X座標 %d Y座標 %d ", MouseX, MouseY);
	switch (Phase)
	{
	case 1: //親決め
		if (Judgeflg == 0) {
			DrawRotaGraph(FudaX + 280, FudaY + 100, 0.7f, 0, E_fudaImg, FALSE);
			DrawFormatString(FudaX + 300, FudaY + 120, GetColor(255, 0, 0), "%d月", E_judge);
			DrawRotaGraph(FudaX + 280, FudaY + 400, 0.7f, 0, P_fudaImg, FALSE);
			DrawFormatString(FudaX + 300, FudaY + 420, GetColor(255, 0, 0), "%d月", P_judge);
			if (Judgeflg == 1 && Monthflg == 1) {
				DrawFormatString(300, 360, GetColor(255, 0, 0), "あなたが親（先手）です");
			}
			else {
				DrawFormatString(300, 360, GetColor(255, 0, 0), "相手が親（先手）です");
			}
			break;
	case 2:  //札配布
		break;
	case 3: //親番
		break;
	case 4: //子番
		break;
	case 5:  //リザルト
		break;
		}
		/*DrawRotaGraph(100, 350, 0.7f, 0, U_Img, TRUE);
		DrawBox(100, 580, 740, 700, GetColor(255, 0, 0), FALSE);
		DrawRotaGraph(140, 640, 0.6f, 0, F_Img, TRUE);
		DrawRotaGraph(220, 640, 0.6f, 0, F_Img, TRUE);
		DrawRotaGraph(300, 640, 0.6f, 0, F_Img, TRUE);
		DrawRotaGraph(380, 640, 0.6f, 0, F_Img, TRUE);
		DrawRotaGraph(460, 640, 0.6f, 0, F_Img, TRUE);
		DrawRotaGraph(540, 640, 0.6f, 0, F_Img, TRUE);
		DrawRotaGraph(620, 640, 0.6f, 0, F_Img, TRUE);
		DrawRotaGraph(700, 640, 0.6f, 0, F_Img, TRUE);
		DrawGraph(0, 0, Stage, TRUE);
		DrawGraph(200, 200, UraImg, FALSE);
		DrawRotaGraph(FudaX + 100, FudaY + 100, 0.7f, 0, FudaImg[0], FALSE);
		DrawGraph(100, 100, Stage, FALSE);*/
	}
}


void Hanafuda:: OyaGime()
{
	
		srand(time(NULL));
		j = rand() % 48;
		E_fudaImg= FudaImg[j];
		srand(time(NULL));
		i = rand() % 48;
		P_fudaImg = FudaImg[i];
		Month();
		if (CheckHitKey(KEY_INPUT_0)) {
			Judgeflg = 1;
			Monthflg = 1;
		}
}
void Hanafuda::shuffleFuda()
{
	//*float H_FudaX = 100;
	//float H_FudaY = 350;*/

	srand(time(NULL));
	i = rand() % 48;


}