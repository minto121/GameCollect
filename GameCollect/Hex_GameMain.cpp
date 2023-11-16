#include"DxLib.h"
#include"Hex_GameMain.h"
#include"Padinput.h"

//コンストラクタ
Hex::Hex() {
	BackImg = LoadGraph("images/Hex/Background02.png");
	BlueHexImg = LoadGraph("images/Hex/hexagon-B50.png");
	RedHexImg = LoadGraph("images/Hex/hexagon-R50.png");
	BlackHexImg = LoadGraph("images/Hex/hexagon-Black50.png");
	HexImg = LoadGraph("images/Hex/hexagon-50.png");
	SelectX = 615;
	SelectY = 335;
	Select_i = 6;
	Select_j = 6;
	GameInit();
}
	
//描画以外
AbstractScene* Hex::Update() {
	Select();
	return this;
}

//描画のみ
void Hex::Draw()const {
	DrawGraph(0, 0, BackImg, FALSE);
	DrawStage();
	DrawGraph(gStage[Select_i][Select_j].x, gStage[Select_i][Select_j].y, BlueHexImg, TRUE);
}

//初期化
void Hex::GameInit() {
	//ステージ初期化
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 13; j++) {
			if (j == 0 && i == 0 || j == 12 && i == 12) {
				gStage[i][j].flg = 4;	//黒
			}
			else if (i == 0 && j != 12 || i == 12 ) {
				gStage[i][j].flg = 2;
			}
			else if (j == 0 || j == 12) {
				gStage[i][j].flg = 1;
			}
			else {
				gStage[i][j].flg = 0;
			}
			gStage[i][j].x = (j + i - 1) * -30 + 945;	//945
			gStage[i][j].y = (j - i - 1) * -17 + 320;	//320
			//gStage[i][j].w = 50;
			//gStage[i][j].h = 50;
		}
	}
}

//タイルを置く場所の移動
void Hex::Select() {
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{
			Select_j = Select_j - 1;
			/*Select_i = Select_i - 1;*/
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
	{
			Select_i = Select_i - 1;
			Select_j = Select_j + 1;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
			Select_j = Select_j - 1;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT))
	{
			Select_j = Select_j + 1;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
			gStage[Select_i][Select_j].flg = 1;
	}
}

void Hex::DrawStage() const {
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 13; j++) {
			if (gStage[i][j].flg == 1) {
				DrawGraph(gStage[i][j].x, gStage[i][j].y, RedHexImg, TRUE);
			}
			else if (gStage[i][j].flg == 2) {
				DrawGraph(gStage[i][j].x, gStage[i][j].y, BlueHexImg, TRUE);
			}
			else if (gStage[i][j].flg == 0) {
				DrawGraph(gStage[i][j].x, gStage[i][j].y, HexImg, TRUE);
			}
			else if (gStage[i][j].flg == 4) {
				DrawGraph(gStage[i][j].x, gStage[i][j].y, BlackHexImg, TRUE);
			}
		}
	}
}