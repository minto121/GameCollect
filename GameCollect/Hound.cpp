#include"RabbitAndHounds.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Hound.h"

Hound::Hound()
{
	BackGroundImg = LoadGraph("images/RabbitAndHounds/RabbitAndHoundsBoard.png");
	cursorImg = LoadGraph("images/RabbitAndHounds/cursor.png");

	//3Dモデルの読込
	HoundImg = MV1LoadModel("Dog_Model.mv1");
	RabbitImg = MV1LoadModel("Rabbit_Model.mv1");

	// テクスチャの読み込み
	R_texture = LoadGraph("images/RabbitAndHounds/Textures/Coloe_Textures/T_PigHead_00.TGA");

	hound_X = 0;
	hound_Y = 0;

	HoundFlg1 = 5;
	HoundFlg2 = 1;
	HoundFlg3 = 11;

	HoundMoveflg1 = FALSE;
	HoundMoveflg2 = FALSE;
	HoundMoveflg3 = FALSE;

	cursorFlg = 5;

	//ステージ初期化
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == 0 && j == 0) {
				bord[i][j].flg = 16; //入れないフラグ
				bord[i][j].x = 150;  //左上
				bord[i][j].y = 100;
			}
			else if (i == 4 && j == 0) {
				bord[i][j].flg = 16; //入れないフラグ
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
	// 猟犬を移動
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
	//	HoundFlg -= 5;
	//}
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
	//	HoundFlg += 5;
	//}
	///*if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
	//	HoundFlg -= 1;
	//}*/
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
	//	HoundFlg += 1;
	//}

	//カーソル
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
		cursorFlg -= 5;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
		cursorFlg += 5;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		cursorFlg -= 1;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		cursorFlg += 1;
	}

	if (HoundFlg1 == cursorFlg && PAD_INPUT::OnPressed(XINPUT_BUTTON_A)) {
		HoundMoveflg1 = TRUE;

		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
			HoundFlg1 -= 5;
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
			HoundFlg1 += 5;
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
			HoundFlg1 += 1;
		}
	}

	if (HoundFlg2 == cursorFlg && PAD_INPUT::OnPressed(XINPUT_BUTTON_A)) {
		HoundMoveflg2 = TRUE;

		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
			HoundFlg2 -= 5;
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
			HoundFlg2 += 5;
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
			HoundFlg2 += 1;
		}
	}
	
	if (HoundFlg3 == cursorFlg && PAD_INPUT::OnPressed(XINPUT_BUTTON_A)) {
		HoundMoveflg3 = TRUE;

		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
			HoundFlg3 -= 5;
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
			HoundFlg3 += 5;
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
			HoundFlg3 += 1;
		}
	}

	return this;
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

	//// テクスチャの設定
	//SetUseTextureToShader(0, R_texture);

	////MV1SetPosition(HoundImg, VGet(320.0f, -300.0f, 600.0f));

	////3Dモデルの描画
	//MV1DrawModel(RabbitImg);
	//MV1DrawModel(HoundImg);

	//猟犬の駒(仮)
	//DrawBox(390, 95, 440, 145, 0x0000ff, TRUE);     //上
	//DrawBox(150, 335, 200, 385, 0x0000ff, TRUE);   //真ん中
	//DrawBox(390, 575, 440, 625, 0x0000ff, TRUE);     //下

	//プレイヤー表示
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

			//猟犬1の描画
			if (HoundMoveflg1 == TRUE) {
				if (HoundFlg1 == 1 && bord[i][j].flg == 1) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 2 && bord[i][j].flg == 2) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 3 && bord[i][j].flg == 3) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 5 && bord[i][j].flg == 5) {	//初期位置
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 6 && bord[i][j].flg == 6) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 7 && bord[i][j].flg == 7) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 8 && bord[i][j].flg == 8) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 9 && bord[i][j].flg == 9) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 11 && bord[i][j].flg == 11) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 12 && bord[i][j].flg == 12) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 13 && bord[i][j].flg == 13) {
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x0000ff, TRUE);
				}
				else if (HoundFlg1 == 0 && HoundFlg1 == 5 && HoundFlg1 == 10 && HoundFlg1 == 15) {   //いけないマス表示
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
			}
			
			//猟犬2の描画
			if (HoundMoveflg2 == TRUE) {
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
				else if (HoundFlg2 == 0 && HoundFlg2 == 5 && HoundFlg2 == 10 && HoundFlg2 == 15) {   //いけないマス表示
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
			}
			
			//猟犬3の描画
			if (HoundMoveflg3 == TRUE) {
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
				else if (HoundFlg3 == 0 && HoundFlg3 == 5 && HoundFlg3 == 10 && HoundFlg3 == 15) {   //いけないマス表示
					DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xff0000, TRUE);
				}
			}
		}
	}
	//カーソル
	/*for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			
		}
	}*/

	//カーソル
	//for (int i = 0; i < 5; i++) {
	//	for (int j = 0; j < 3; j++) {
	//		if (HoundFlg == 1 && bord[i][j].flg == 1) {
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//		else if (HoundFlg == 2 && bord[i][j].flg == 2) {
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//		else if (HoundFlg == 3 && bord[i][j].flg == 3) {
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//		else if (HoundFlg == 5 && bord[i][j].flg == 5) {   //初期位置
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//		else if (HoundFlg == 6 && bord[i][j].flg == 6) {
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//		else if (HoundFlg == 7 && bord[i][j].flg == 7) {
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//		else if (HoundFlg == 8 && bord[i][j].flg == 8) {
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//		else if (HoundFlg == 9 && bord[i][j].flg == 9) {
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//		else if (HoundFlg == 11 && bord[i][j].flg == 11) {
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//		else if (HoundFlg == 12 && bord[i][j].flg == 12) {
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//		else if (HoundFlg == 13 && bord[i][j].flg == 13) {
	//			DrawGraph(bord[i][j].x - 10, bord[i][j].y - 10, cursorImg, TRUE);
	//		}
	//	}
	//}
	
	SetFontSize(20);
	DrawFormatString(200, 10, 0x000000, "cursorFlg:%d", cursorFlg);
	DrawFormatString(400, 10, 0x000000, "HoundFlg1:%d", HoundFlg1);
	DrawFormatString(600, 10, 0x000000, "HoundFlg2:%d", HoundFlg2);
	DrawFormatString(800, 10, 0x000000, "HoundFlg3:%d", HoundFlg3);

}