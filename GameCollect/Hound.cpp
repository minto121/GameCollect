#include"RabbitAndHounds.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Hound.h"

Hound::Hound()
{
	BackGroundImg = LoadGraph("images/RabbitAndHounds/RabbitAndHoundsBoard.png");
	cursorImg = LoadGraph("images/RabbitAndHounds/cursor.png");

	//3Dモデルの読込
	/*HoundImg = MV1LoadModel("Dog_Model.mv1");
	RabbitImg = MV1LoadModel("Rabbit_Model.mv1");*/

	// テクスチャの読み込み
	//R_texture = LoadGraph("images/RabbitAndHounds/Textures/Coloe_Textures/T_PigHead_00.TGA");

	cursorFlg = 5;				//カーソルフラグ初期化

	RabbitFlg = 9;				//ウサギフラグ初期化
	RabbitDrawflg = TRUE;		//ウサギ描画フラグ初期化
	RabbitMoveflg = 0;			//ウサギ移動フラグ初期化

	HoundFlg1 = 5;				//猟犬フラグ初期化
	HoundFlg2 = 1;
	HoundFlg3 = 11;

	HoundDrawflg1 = TRUE;		//猟犬描画フラグ初期化
	HoundDrawflg2 = TRUE;
	HoundDrawflg3 = TRUE;
	
	HoundMoveflg1 = 0;			//猟犬移動フラグ初期化
	HoundMoveflg2 = 0;
	HoundMoveflg3 = 0;

	RabbitTurnflg = 0;			//ウサギターンフラグ初期化
	HoundTurnflg = 1;			//猟犬ターンフラグ初期化

	RabbitWinflg = FALSE;		//ウサギの勝利条件フラグ
	HoundWinflg = FALSE;		//猟犬の勝利条件フラグ

	//ステージ初期化
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == 0 && j == 0) {
				bord[i][j].flg = 0; //入れないフラグ
				bord[i][j].x = 150;  //左上
				bord[i][j].y = 100;
			}
			else if (i == 4 && j == 0) {
				bord[i][j].flg = 4; //入れないフラグ
				bord[i][j].x = 1080;  //右上
				bord[i][j].y = 100;
			}
			else if (i == 0 && j == 2) {
				bord[i][j].flg = 10; //入れないフラグ
				bord[i][j].x = 150;  //左下
				bord[i][j].y = 575;
			}
			else if (i == 4 && j == 2) {
				bord[i][j].flg = 14;  //入れないフラグ
				bord[i][j].x = 1080;  //右下
				bord[i][j].y = 575;
			}
			else if (i == 1 && j == 0) {
				bord[i][j].flg = 1;  //入れるフラグ
				bord[i][j].x = 390;  //上段　左
				bord[i][j].y = 95;
			}
			else if (i == 2 && j == 0) {
				bord[i][j].flg = 2;  //入れるフラグ
				bord[i][j].x = 625;  //上段　真ん中
				bord[i][j].y = 95;
			}
			else if (i == 3 && j == 0) {
				bord[i][j].flg = 3;  //入れるフラグ
				bord[i][j].x = 860;  //上段　右
				bord[i][j].y = 95;
			}
			else if (i == 0 && j == 1) {
				bord[i][j].flg = 5;  //入れるフラグ
				bord[i][j].x = 150;  //中段　左端
				bord[i][j].y = 335;
			}
			else if (i == 1 && j == 1) {
				bord[i][j].flg = 6;  //入れるフラグ
				bord[i][j].x = 390;  //中段　左
				bord[i][j].y = 335;
			}
			else if (i == 2 && j == 1) {
				bord[i][j].flg = 7;  //入れるフラグ
				bord[i][j].x = 625;  //中段　真ん中
				bord[i][j].y = 335;
			}
			else if (i == 3 && j == 1) {
				bord[i][j].flg = 8;  //入れるフラグ
				bord[i][j].x = 865;  //中段　右
				bord[i][j].y = 335;
			}
			else if (i == 4 && j == 1) {
				bord[i][j].flg = 9; //入れるフラグ
				bord[i][j].x = 1080;  //中段　右端
				bord[i][j].y = 335;
			}
			else if (i == 1 && j == 2) {
				bord[i][j].flg = 11; //入れるフラグ
				bord[i][j].x = 390;  //下段　左
				bord[i][j].y = 575;
			}
			else if (i == 2 && j == 2) {
				bord[i][j].flg = 12; //入れるフラグ
				bord[i][j].x = 625;  //下段　真ん中
				bord[i][j].y = 575;
			}
			else if (i == 3 && j == 2) {
				bord[i][j].flg = 13; //入れるフラグ
				bord[i][j].x = 860;  //下段　右
				bord[i][j].y = 575;
			}
		}
	}
}

Hound::~Hound()
{
	// モデルハンドルの削除
	/*MV1DeleteModel(HoundImg);
	MV1DeleteModel(RabbitImg);*/
}

AbstractScene* Hound::Update()
{
	//カーソル移動処理
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
	//ウサギのターン
	if (RabbitTurnflg == 1)
	{
		//Aボタンでウサギを選択する
		if (RabbitMoveflg == 0)
		{
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
			{
				if (RabbitFlg == cursorFlg)
				{
					RabbitMoveflg = 1;
				}
				else
				{
					RabbitMoveflg = 0;
				}
			}
		}
		else if (RabbitMoveflg == 1)	//選択したウサギを動かす
		{
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
				RabbitFlg = cursorFlg;
				if (RabbitFlg == HoundFlg1 || RabbitFlg == HoundFlg2 || RabbitFlg == HoundFlg3 || RabbitFlg < 1 || RabbitFlg == 0 || RabbitFlg == 4) {
					RabbitFlg += 5;
				}
			}
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
				RabbitFlg = cursorFlg;
				if (RabbitFlg == HoundFlg1 || RabbitFlg == HoundFlg2 || RabbitFlg == HoundFlg3 || RabbitFlg > 14 || RabbitFlg == 14 || RabbitFlg == 10) {
					RabbitFlg -= 5;
				}
			}
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
				RabbitFlg = cursorFlg;
				if (RabbitFlg == HoundFlg1 || RabbitFlg == HoundFlg2 || RabbitFlg == HoundFlg3 || RabbitFlg >= 14 || RabbitFlg == 4 || RabbitFlg == 10) {
					RabbitFlg -= 1;
				}
			}
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
				RabbitFlg = cursorFlg;
				if (RabbitFlg == HoundFlg1 || RabbitFlg == HoundFlg2 || RabbitFlg == HoundFlg3 || RabbitFlg == 0 || RabbitFlg == 10) {
					RabbitFlg += 1;
				}
			}
			else if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
			{
				RabbitMoveflg = 0;

				RabbitTurnflg = 0;
				HoundTurnflg = 1;
			}
		}
	}

	//猟犬のターン
	if (HoundTurnflg == 1)
	{
		//Aボタンで猟犬を選択する
		if (HoundMoveflg1 == 0)
		{
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
			{
				if (HoundFlg1 == cursorFlg)
				{
					HoundMoveflg1 = 1;
				}
				else 
				{
					HoundMoveflg1 = 0;
				}
			}
		}
		else if (HoundMoveflg1 == 1)	//選択した猟犬1を動かす
		{
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
				HoundFlg1 = cursorFlg;
				if (HoundFlg1 == RabbitFlg || HoundFlg1 == HoundFlg2 || HoundFlg1 == HoundFlg3 || HoundFlg1 < 1 || HoundFlg1 == 0 || HoundFlg1 == 4) {
					HoundFlg1 += 5;
				}
			}
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
				HoundFlg1 = cursorFlg;
				if (HoundFlg1 == RabbitFlg || HoundFlg1 == HoundFlg2 || HoundFlg1 == HoundFlg3 || HoundFlg1 > 14 || HoundFlg1 == 14 || HoundFlg1 == 10) {
					HoundFlg1 -= 5;
				}
			}
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
				HoundFlg1 = cursorFlg;
				if (HoundFlg1 == RabbitFlg || HoundFlg1 == HoundFlg2 || HoundFlg1 == HoundFlg3 || HoundFlg1 >= 14 || HoundFlg1 == 4 || HoundFlg1 == 10) {
					HoundFlg1 -= 1;
				}
			}
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
			{
				HoundMoveflg1 = 0;

				RabbitTurnflg = 1;
				HoundTurnflg = 0;
			}
		}

		//Aボタンで猟犬を選択する2
		if (HoundMoveflg2 == 0)
		{
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
			{
				if (HoundFlg2 == cursorFlg)
				{
					HoundMoveflg2 = 1;
				}
				else 
				{
					HoundMoveflg2 = 0;
				}
			}
		}
		else if (HoundMoveflg2 == 1)	//選択した猟犬2を動かす
		{
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
				HoundFlg2 = cursorFlg;
				if (HoundFlg2 == RabbitFlg || HoundFlg2 == HoundFlg1 || HoundFlg2 == HoundFlg3 || HoundFlg2 < 1 || HoundFlg2 == 0 || HoundFlg2 == 4) {
					HoundFlg2 += 5;
				}
			}
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
				HoundFlg2 = cursorFlg;
				if (HoundFlg2 == RabbitFlg || HoundFlg2 == HoundFlg1 || HoundFlg2 == HoundFlg3 || HoundFlg2 > 14 || HoundFlg2 == 14 || HoundFlg2 == 10) {
					HoundFlg2 -= 5;
				}
			}
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
				HoundFlg2 = cursorFlg;
				if (HoundFlg2 == RabbitFlg || HoundFlg2 == HoundFlg1 || HoundFlg2 == HoundFlg3 || HoundFlg2 >= 14 || HoundFlg2 == 4 || HoundFlg2 == 10) {
					HoundFlg2 -= 1;
				}
			}
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
			{
				HoundMoveflg2 = 0;

				RabbitTurnflg = 1;
				HoundTurnflg = 0;
			}
		}

		//Aボタンで猟犬を選択する3
		if (HoundMoveflg3 == 0)
		{
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
			{
				if (HoundFlg3 == cursorFlg)
				{
					HoundMoveflg3 = 1;
				}
				else 
				{
					HoundMoveflg3 = 0;
				}
			}
		}
		else if (HoundMoveflg3 == 1)	//選択した猟犬3を動かす
		{
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
				HoundFlg3 = cursorFlg;
				if (HoundFlg3 == RabbitFlg || HoundFlg3 == HoundFlg1 || HoundFlg3 == HoundFlg2 || HoundFlg3 < 1 || HoundFlg3 == 0 || HoundFlg3 == 4) {
					HoundFlg3 += 5;
				}
			}

			if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
				HoundFlg3 = cursorFlg;
				if (HoundFlg3 == RabbitFlg || HoundFlg3 == HoundFlg1 || HoundFlg3 == HoundFlg2 || HoundFlg3 > 14 || HoundFlg3 == 14 || HoundFlg3 == 10) {
					HoundFlg3 -= 5;
				}
			}

			if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
				HoundFlg3 = cursorFlg;

				if (HoundFlg3 == RabbitFlg || HoundFlg3 == HoundFlg1 || HoundFlg3 == HoundFlg2 || HoundFlg3 >= 14 || HoundFlg3 == 4 || HoundFlg3 == 10) {
					HoundFlg3 -= 1;
				}
			}

			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
			{
				HoundMoveflg3 = 0;

				RabbitTurnflg = 1;
				HoundTurnflg = 0;
			}
		}
	}

	GameJudge();

	return this;
}

void Hound::GameJudge()
{
	//猟犬の勝利条件
	if (RabbitFlg == 9)
	{
		if (HoundFlg1 == 3 || HoundFlg2 == 3 || HoundFlg3 == 3)
		{
			if (HoundFlg1 == 8 || HoundFlg2 == 8 || HoundFlg3 == 8)
			{
				if (HoundFlg1 == 13 || HoundFlg2 == 13 || HoundFlg3 == 13)
				{
					if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
					{
						HoundWinflg = TRUE;
					}
				}
			}
		}
		else
		{
			HoundWinflg = FALSE;
		}
	}
	else
	{
		HoundWinflg = FALSE;
	}

	//ウサギの勝利条件
	/*if ((PAD_INPUT::OnButton(XINPUT_BUTTON_A)))
	{
		RabbitWinflg = TRUE;
	}*/

	/*if (RabbitFlg == 3 || RabbitFlg == 8 || RabbitFlg == 13)
	{
		if (HoundFlg1 != 2 || HoundFlg2 != 2 || HoundFlg3 != 2 && HoundFlg1 != 7 || HoundFlg2 != 7 || HoundFlg3 != 7 && HoundFlg1 != 12 || HoundFlg2 != 12 || HoundFlg3 != 12 &&
			HoundFlg1 != 1 || HoundFlg2 != 1 || HoundFlg3 != 1 && HoundFlg1 != 6 || HoundFlg2 != 6 || HoundFlg3 != 6 && HoundFlg1 != 11 || HoundFlg2 != 11 || HoundFlg3 != 11 &&
			HoundFlg1 != 5 || HoundFlg2 != 5 || HoundFlg3 != 5)
		{
			if ((PAD_INPUT::OnButton(XINPUT_BUTTON_A)))
			{
				RabbitWinflg = TRUE;
			}
		}
	}
	else
	{
		RabbitWinflg = FALSE;
	}*/


	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			if (RabbitFlg == 3 || RabbitFlg == 8 || RabbitFlg == 13)
			{
				bord[3][j] = a;
				bord[i][j] = RabbitFlg;
				if (bord[3][j] < HoundFlg1)
				{
					if ((PAD_INPUT::OnButton(XINPUT_BUTTON_A)))
					{
						RabbitWinflg = TRUE;
					}
				}
			}
			else
			{
				RabbitWinflg = FALSE;
			}
		}
	}

}

void Hound::Draw() const
{
	//背景画像
	DrawGraph(0, 0, BackGroundImg, TRUE);
	//タイトル
	DrawString(10, 20, "プレイヤー操作は猟犬", 0x000000);

	//SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -1000), VGet(0, 0, 0));

	//// 画面に映る位置に３Ｄモデルを移動
	//MV1SetPosition(RabbitImg, VGet(320.0f, -300.0f, 600.0f));
	//MV1SetScale(RabbitImg, VGet(1, 1, 1)); // モデルのスケールを設定
	//MV1SetRotationXYZ(RabbitImg, VGet(0, 0, 0)); // モデルの回転を設定

	// テクスチャの設定
	//SetUseTextureToShader(0, R_texture);

	//MV1SetPosition(HoundImg, VGet(320.0f, -300.0f, 600.0f));

	//3Dモデルの描画
	//MV1DrawModel(RabbitImg);
	//MV1DrawModel(HoundImg);

	//カーソル・ウサギ・猟犬の動き
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {

			//カーソル表示
			if (cursorFlg == 1 && bord[i][j].flg == 1) {
				DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
			}
			else if (cursorFlg == 2 && bord[i][j].flg == 2) {
				DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
			}
			else if (cursorFlg == 3 && bord[i][j].flg == 3) {
				DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
			}
			else if (cursorFlg == 5 && bord[i][j].flg == 5) {   //初期位置
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

			//ウサギの描画
			if (RabbitDrawflg == TRUE) {
				if (RabbitFlg == 1 && bord[i][j].flg == 1) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				if (RabbitFlg == 2 && bord[i][j].flg == 2) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				if (RabbitFlg == 3 && bord[i][j].flg == 3) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				if (RabbitFlg == 5 && bord[i][j].flg == 5) {	
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				if (RabbitFlg == 6 && bord[i][j].flg == 6) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				if (RabbitFlg == 7 && bord[i][j].flg == 7) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				if (RabbitFlg == 8 && bord[i][j].flg == 8) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				if (RabbitFlg == 9 && bord[i][j].flg == 9) {		//初期位置
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				if (RabbitFlg == 11 && bord[i][j].flg == 11) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				if (RabbitFlg == 12 && bord[i][j].flg == 12) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
				if (RabbitFlg == 13 && bord[i][j].flg == 13) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
			}

			//猟犬1の描画
			if (HoundDrawflg1 == TRUE) {
				if (HoundFlg1 == 1 && bord[i][j].flg == 1) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (HoundFlg1 == 2 && bord[i][j].flg == 2) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (HoundFlg1 == 3 && bord[i][j].flg == 3) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (HoundFlg1 == 5 && bord[i][j].flg == 5) {	//初期位置
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (HoundFlg1 == 6 && bord[i][j].flg == 6) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (HoundFlg1 == 7 && bord[i][j].flg == 7) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (HoundFlg1 == 8 && bord[i][j].flg == 8) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (HoundFlg1 == 9 && bord[i][j].flg == 9) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (HoundFlg1 == 11 && bord[i][j].flg == 11) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (HoundFlg1 == 12 && bord[i][j].flg == 12) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (HoundFlg1 == 13 && bord[i][j].flg == 13) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
			}
			
			//猟犬2の描画
			if (HoundDrawflg2 == TRUE) {
				if (HoundFlg2 == 1 && bord[i][j].flg == 1) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg2 == 2 && bord[i][j].flg == 2) {	//初期位置
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
			}
			
			//猟犬3の描画
			if (HoundDrawflg3 == TRUE) {
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
				else if (HoundFlg3 == 11 && bord[i][j].flg == 11) {		//初期位置
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg3 == 12 && bord[i][j].flg == 12) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg3 == 13 && bord[i][j].flg == 13) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
			}
		}
	}

	if (HoundTurnflg == 1)
	{
		SetFontSize(40);
		DrawString(500, 10, "猟犬のターン", 0x000000);
	}
	else if (RabbitTurnflg == 1)
	{
		SetFontSize(40);
		DrawString(500, 10, "ウサギのターン", 0x000000);
	}

	SetFontSize(30);
	if (HoundWinflg == TRUE)
	{
		DrawString(10, 50, "猟犬の勝ち", 0x000000);
	}
	else if (RabbitWinflg == TRUE)
	{
		DrawString(10, 50, "ウサギの勝ち", 0x000000);
	}
	

	SetFontSize(20);
	/*DrawFormatString(200, 10, 0x000000, "cursorFlg:%d", cursorFlg);
	DrawFormatString(400, 10, 0x000000, "HoundFlg1:%d", HoundFlg1);
	DrawFormatString(600, 10, 0x000000, "HoundFlg2:%d", HoundFlg2);
	DrawFormatString(800, 10, 0x000000, "HoundFlg3:%d", HoundFlg3);

	DrawFormatString(1000, 10, 0x000000, "HoundMoveflg1:%d", HoundMoveflg1);
	DrawFormatString(1000, 50, 0x000000, "HoundMoveflg2:%d", HoundMoveflg2);
	DrawFormatString(1000, 90, 0x000000, "HoundMoveflg3:%d", HoundMoveflg3);

	DrawFormatString(1000, 130, 0x000000, "RabbitMoveflg:%d", RabbitMoveflg);*/

	/*DrawFormatString(200, 40, 0x000000, "RabbitTurnflg:%d", RabbitTurnflg);
	DrawFormatString(400, 40, 0x000000, "HoundTurnflg:%d", HoundTurnflg);*/
}