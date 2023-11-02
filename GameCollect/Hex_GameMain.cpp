#include"DxLib.h"
#include"Hex_GameMain.h"
#include"Padinput.h"

//コンストラクタ
Hex::Hex() {
	BanImg = LoadGraph("../images/Hex/Hex_11×11.png");
	BlueHexImg = LoadGraph("../images/Hex/hexagon-B50.png");
	RedHexImg = LoadGraph("../images/Hex/hexagon-R50.png");
	SelectX = 615;
	SelectY = 335;
	//GameInit();
}

//描画以外
AbstractScene* Hex::Update() {
	//GameInit();

	return this;
}

//描画のみ
void Hex::Draw()const {
	DrawGraph(0, 0, BanImg, FALSE);
	//DrawGraph(615, 335, RedHexImg, TRUE);
	//DrawStage();
}

//初期化
void Hex::GameInit() {
	//ステージ初期化
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 13; j++) {
			if ((j == 0 && i == 0) || (j == 12 && i == 12)) {
				gStage[i][j].flg = 4;	//黒
			}
			else if (j == 0 || j == 12) {
				gStage[i][j].flg = 2;
			}
			else if (i == 0 || i == 12) {
				gStage[i][j].flg = 3;
			}
			else {
				gStage[i][j].flg = 1;
				gStage[i][j].x = (j - 1) * 50;
				gStage[i][j].y = (i - 1) * 50;
				gStage[i][j].w = 50;
				gStage[i][j].h = 50;
			}
		}
	}
}

//タイルを置く場所の移動
void Hex::Select() {
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{

	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{

	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{

	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{

	}
}

void Hex::DrawStage() const {
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 13; j++) {
			if (gStage[i][j].flg == 2) {
				//DrawGraph(gStage[i][j].x, gStage[i][j].y, RedHexImg, TRUE);
				//DrawGraph(615, 335, RedHexImg, TRUE);

			}
			else if (gStage[i][j].flg == 3) {
				DrawGraph(gStage[i][j].x, gStage[i][j].y, BlueHexImg, TRUE);
			}
		}
	}
}