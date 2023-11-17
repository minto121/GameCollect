#include"DxLib.h"
#include"Hex_GameMain.h"
#include"Padinput.h"

//コンストラクタ
Hex::Hex() {
	BackImg = LoadGraph("images/Hex/Background02.png");
	BlueHexImg = LoadGraph("images/Hex/hexagon-B50.png");
	RedHexImg = LoadGraph("images/Hex/hexagon-R50.png");
	BlackHexImg = LoadGraph("images/Hex/hexagon-Black50.png");
	GreenHexImg = LoadGraph("images/Hex/hexagon-G50.png");
	HexImg = LoadGraph("images/Hex/hexagon-50.png");
	Select_i = 6;
	Select_j = 6;
	CheckFlg = 0;
	CheckCnt = 0;
	ClearFlg = 0;
	GameInit();
}
	
//描画以外
AbstractScene* Hex::Update() {
	if (ClearFlg == 0) {
		Select();
		Check_P();
		Check_E();
	}
	else if (ClearFlg == 1) {

	}
	else if (ClearFlg == 2) {

	}
	return this;
}

//描画のみ
void Hex::Draw()const {

	if (ClearFlg == 0) {
		//背景画像
		DrawGraph(0, 0, BackImg, FALSE);

		DrawStage();

		DrawGraph(gStage[Select_i][Select_j].x, gStage[Select_i][Select_j].y, GreenHexImg, TRUE);
	}
	else if (ClearFlg == 1) {
		DrawGraph(0, 0, BackImg, FALSE);
	}
	else if (ClearFlg == 2) {
		DrawGraph(615, 335, GreenHexImg, TRUE);
	}
}

//初期化
void Hex::GameInit() {
	//ステージ初期化
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 13; j++) {
			if (j == 0 && i == 0 || j == 12 && i == 12) {
				gStage[i][j].flg = 3;	//黒
			}
			else if (i == 0 && j != 12 || i == 12) {
				gStage[i][j].flg = 5;
			}
			else if (j == 0 || j == 12) {
				gStage[i][j].flg = 4;
			}
			else {
				gStage[i][j].flg = 0;
			}
			gStage[i][j].x = (j + i - 1) * -30 + 945;	
			gStage[i][j].y = (j - i - 1) * -17 + 320;	
		}
	}
}

//タイルを置く場所の移動&設置
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
			//Select_i = 6;
			//Select_j = 6;
		}
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_B))
	{
		if (gStage[Select_i][Select_j].flg == 0) {
			gStage[Select_i][Select_j].flg = 2;
			//Select_i = 6;
			//Select_j = 6;
		}
	}
}

//ステージ描画
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
	for (int i = 1; i < 12; i++) {
		CheckCnt = CheckFlg;
		for (int j = 1; j < 12; j++) {
			if (gStage[j][i].flg == 1) {
				CheckFlg++;
				break;
			}
		}
		if (CheckFlg == CheckCnt) {
			break;
		}
	}
	if (CheckCnt >= 11) {
		ClearFlg = 1;
	}
}

void Hex::Check_E() {
	for (int i = 1; i < 12; i++) {
		CheckCnt = CheckFlg;
		for (int j = 1; j < 12; j++) {
			if (gStage[i][j].flg == 2) {
				CheckFlg++;
				break;
			}
		}
		if (CheckFlg == CheckCnt) {
			break;
		}
	}
	if (CheckCnt >= 11) {
		ClearFlg = 2;
	}
}