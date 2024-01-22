#include"RabbitAndHounds.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Rabbit.h"

Rabbit::Rabbit()
{
	BackGroundImg = LoadGraph("images/RabbitAndHounds/RabbitAndHoundsBoard.png");
	cursorImg = LoadGraph("images/RabbitAndHounds/cursor.png");

	//3Dモデルの読込
	/*HoundImg = MV1LoadModel("Dog_Model.mv1");
	RabbitImg = MV1LoadModel("Rabbit_Model.mv1");*/

	//RabbitImg[1] = LoadGraph("../images/RabbitAndHounds/Rabbit.png");
	//LoadDivGraph("images/RabbitAndHounds/Rabbit.png", 2, 2, 1, 256, 512, RabbitImg);

	// テクスチャの読み込み
	//R_texture = LoadGraph("images/RabbitAndHounds/Textures/Coloe_Textures/T_PigHead_00.TGA");

	RabbitFlg = 5;
	RabbitDrawflg = TRUE;
	RabbitMoveflg = 0;

	cursorFlg = 5;		//カーソルフラグ初期化

	//ステージ初期化
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 3; j++) {
			if (i == 0 && j == 0) {
				bord[i][j].flg = 16; //入れないフラグ
				bord[i][j].x = 150;  //左上
				bord[i][j].y = 100; 
			}
			else if (i == 4 && j == 0) {
				bord[i][j].flg =16; //入れないフラグ
				bord[i][j].x = 1080;  //右上
				bord[i][j].y = 100;
			}
			else if (i == 0 && j == 2) {
				bord[i][j].flg = 16; //入れないフラグ
				bord[i][j].x = 150;  //左下
				bord[i][j].y = 575;
			}
			else if (i == 4 && j == 2) {
				bord[i][j].flg = 16;  //入れないフラグ
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

			//ウサギの描画
			if (RabbitDrawflg == TRUE) {
				if (RabbitFlg == 1 && bord[i][j].flg == 1) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (RabbitFlg == 2 && bord[i][j].flg == 2) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (RabbitFlg == 3 && bord[i][j].flg == 3) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (RabbitFlg == 5 && bord[i][j].flg == 5) {	//初期位置
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (RabbitFlg == 6 && bord[i][j].flg == 6) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (RabbitFlg == 7 && bord[i][j].flg == 7) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (RabbitFlg == 8 && bord[i][j].flg == 8) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (RabbitFlg == 9 && bord[i][j].flg == 9) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (RabbitFlg == 11 && bord[i][j].flg == 11) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (RabbitFlg == 12 && bord[i][j].flg == 12) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				if (RabbitFlg == 13 && bord[i][j].flg == 13) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
			}
		}
	}
}

Rabbit::~Rabbit()
{
	// モデルハンドルの削除
	/*MV1DeleteModel(HoundImg);
	MV1DeleteModel(RabbitImg);*/
}

AbstractScene* Rabbit::Update()
{	
	//// ウサギを移動
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
	//	RabbitFlg -= 5;
	//}
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
	//	RabbitFlg += 5;
	//}
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
	//	RabbitFlg -= 1;
	//}
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
	//	RabbitFlg += 1;
	//}

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

	return this;
}

void Rabbit::Draw() const
{
	//背景画像
	DrawGraph(0, 0, BackGroundImg, TRUE);

	//タイトル
	DrawString(10, 20, "プレイヤー操作はウサギ", 0x000000);

	/*SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -1000), VGet(0, 0, 0));*/

	// 画面に映る位置に３Ｄモデルを移動
	//MV1SetPosition(RabbitImg, VGet(320.0f, -300.0f, 600.0f));
	//MV1SetScale(RabbitImg, VGet(1, 1, 1)); // モデルのスケールを設定
	//MV1SetRotationXYZ(RabbitImg, VGet(0, 0, 0)); // モデルの回転を設定

	// テクスチャの設定
	/*SetUseTextureToShader(0, R_texture);*/

	//MV1SetPosition(HoundImg, VGet(320.0f, -300.0f, 600.0f));

	//3Dモデルの描画
	/*MV1DrawModel(RabbitImg);
	MV1DrawModel(HoundImg);*/

	//猟犬の駒(仮)
	//DrawBox(890, 140, 960, 210, 0x0000ff, TRUE);     //上
	//DrawBox(1080, 350, 1130, 400, 0x0000ff, TRUE);   //真ん中
	//DrawBox(900, 550, 950, 600, 0x0000ff, TRUE);     //下

	//ウサギの駒(仮)
	//DrawBox(150 + rabbit_X, 340 + rabbit_Y, 200 + rabbit_X, 390 + rabbit_Y, 0xff0000, RabbitImg[2]);
	//DrawGraph(100, 250, rabbitimg, TRUE);

	//カーソル表示
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
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
		}
	}

	SetFontSize(20);
	DrawFormatString(200, 10, 0x000000, "rabbitFlg:%d", RabbitFlg);

	
}