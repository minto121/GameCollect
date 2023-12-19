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

	RabbitImg[2] = LoadGraph("../images/RabbitAndHounds/Rabbit.png");
	if (LoadDivGraph("images/RabbitAndHounds/Rabbit.png", 2, 2, 1, 32, 64, RabbitImg));
	RabbitImg[2] = rabbitimg;

	// テクスチャの読み込み
	//R_texture = LoadGraph("images/RabbitAndHounds/Textures/Coloe_Textures/T_PigHead_00.TGA");

	rabbit_X = 0;
	rabbit_Y = 0;


	//ステージ初期化
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 3; j++) {
			if (i == 0 && j == 0) {
				bord[i][j].flg = -1; //入れないフラグ
				bord[i][j].x = 150;  //左上
				bord[i][j].y = 100; 
			}
			else if (i == 4 && j == 0) {
				bord[i][j].flg = -1; //入れないフラグ
				bord[i][j].x = 1080;  //右上
				bord[i][j].y = 100;
			}
			else if (i == 0 && j == 2) {
				bord[i][j].flg = -1; //入れないフラグ
				bord[i][j].x = 150;  //左下
				bord[i][j].y = 575;
			}
			else if (i == 4 && j == 2) {
				bord[i][j].flg = -1;  //入れないフラグ
				bord[i][j].x = 1080;  //右下
				bord[i][j].y = 575;
			}
			else if (i == 1 && j == 0) {
				bord[i][j].flg = 2;  //入れるフラグ
				bord[i][j].x = 390;  //上段　左
				bord[i][j].y = 95;
			}
			else if (i == 2 && j == 0) {
				bord[i][j].flg = 3;  //入れるフラグ
				bord[i][j].x = 625;  //上段　真ん中
				bord[i][j].y = 95;
			}
			else if (i == 3 && j == 0) {
				bord[i][j].flg = 4;  //入れるフラグ
				bord[i][j].x = 860;  //上段　右
				bord[i][j].y = 95;
			}
			else if (i == 0 && j == 1) {
				bord[i][j].flg = 6;  //入れるフラグ
				bord[i][j].x = 150;  //中段　左端
				bord[i][j].y = 335;
			}
			else if (i == 1 && j == 1) {
				bord[i][j].flg = 7;  //入れるフラグ
				bord[i][j].x = 390;  //中段　左
				bord[i][j].y = 335;
			}
			else if (i == 2 && j == 1) {
				bord[i][j].flg = 8;  //入れるフラグ
				bord[i][j].x = 625;  //中段　真ん中
				bord[i][j].y = 335;
			}
			else if (i == 3 && j == 1) {
				bord[i][j].flg = 9;  //入れるフラグ
				bord[i][j].x = 865;  //中段　右
				bord[i][j].y = 335;
			}
			else if (i == 4 && j == 1) {
				bord[i][j].flg = 10; //入れるフラグ
				bord[i][j].x = 1080;  //中段　右端
				bord[i][j].y = 335;
			}
			else if (i == 1 && j == 2) {
				bord[i][j].flg = 12; //入れるフラグ
				bord[i][j].x = 390;  //下段　左
				bord[i][j].y = 575;
			}
			else if (i == 2 && j == 2) {
				bord[i][j].flg = 13; //入れるフラグ
				bord[i][j].x = 625;  //下段　真ん中
				bord[i][j].y = 575;
			}
			else if (i == 3 && j == 2) {
				bord[i][j].flg = 14; //入れるフラグ
				bord[i][j].x = 860;  //下段　右
				bord[i][j].y = 575;
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
	// ウサギを移動
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
		rabbit_Y -= 230;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
		rabbit_Y += 230;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		rabbit_X -= 250;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		rabbit_X += 250;
	}

	// ウサギを移動
	/*if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
		rabbit_Y = bord[5][3].flg;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
		rabbit_Y = bord[5][3].flg;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		rabbit_X = bord[5][3].flg;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		rabbit_X = bord[5][3].flg;
	}*/
	
	//画面から出ないようにする
	if (rabbit_X < 100 || rabbit_X > 1100 || rabbit_Y < -300 || rabbit_Y > 400)
	{
		rabbit_X = 0;
		rabbit_Y = 0;
	}

	//switch (bord[5][3].flg)
	//{
	//	case 0:
	//		if (bord[5][3].flg = 0)
	//		{
	//			return 0;
	//		};
	//		break;
	//	/*case 1:
	//		if (bord[5][3].flg = -1)
	//		{
	//			return -1;
	//		};*/
	//		break;
	//	default:
	//		break;
	//}

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

	//ウサギと猟犬を描画
	/*DrawBox(200 + rabbit_X, 250 + rabbit_Y, 300 + rabbit_X - 1, 350 + rabbit_Y - 1, GetColor(0, 0, 255), RabbitImg);
	DrawCircle(hound_X, hound_Y, hound_X - 1, hound_Y - 1, GetColor(0, 0, 255), HoundImg);*/

	//猟犬の駒(仮)
	DrawBox(890, 140, 960, 210, 0x0000ff, TRUE);     //上
	DrawBox(1100, 350, 1150, 400, 0x0000ff, TRUE);   //真ん中
	DrawBox(900, 550, 950, 600, 0x0000ff, TRUE);     //下
	
	//カーソル
	//DrawGraph(-10 + rabbit_X, 250 + rabbit_Y, cursorImg, TRUE);

	//ウサギの駒(仮)
	DrawBox(150 + rabbit_X, 340 + rabbit_Y, 200 + rabbit_X, 390 + rabbit_Y, 0xff0000, RabbitImg[2]);
	DrawGraph(100, 250, rabbitimg, TRUE);

	/*if (bord[i][j].flg == 0) {
		DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x000000, TRUE);
	}
	else if (bord[i][j].flg == 1) {
		DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
	}*/

	//ボード
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			if (bord[i][j].flg == -1) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0x000000, TRUE);
			}
			else if (bord[i][j].flg == 2) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
			else if (bord[i][j].flg == 3) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
			else if (bord[i][j].flg == 4) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
			else if (bord[i][j].flg == 6) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
			else if (bord[i][j].flg == 7) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
			else if (bord[i][j].flg == 8) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
			else if (bord[i][j].flg == 9) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
			else if (bord[i][j].flg == 10) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
			else if (bord[i][j].flg == 12) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
			else if (bord[i][j].flg ==13) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
			else if (bord[i][j].flg == 14) {
				DrawBox(bord[i][j].x, bord[i][j].y, bord[i][j].x + 50, bord[i][j].y + 50, 0xffffff, TRUE);
			}
		}
	}

	DrawBox(bord[5][3].x, bord[5][3].y, 200 + bord[5][3].x, 390 + bord[5][3].y, 0xff0000, RabbitImg[2]);
}