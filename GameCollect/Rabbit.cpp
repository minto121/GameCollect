#include"RabbitAndHounds.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Rabbit.h"

Rabbit::Rabbit()
{
	BackGroundImg = LoadGraph("images/RabbitAndHounds/RabbitAndHoundsBoard.png");

	//3Dモデルの読込
	/*HoundImg = MV1LoadModel("Dog_Model.mv1");
	RabbitImg = MV1LoadModel("Rabbit_Model.mv1");*/

	RabbitImg[2] = LoadGraph("images/RabbitAndHounds/Rabbit.png");
	if (LoadDivGraph("images/RabbitAndHounds/Rabbit.png", 18, 6, 2, 2, 3, RabbitImg)) {}

	// テクスチャの読み込み
	//R_texture = LoadGraph("images/RabbitAndHounds/Textures/Coloe_Textures/T_PigHead_00.TGA");

	rabbit_X = 0;
	rabbit_Y = 0;

	VECTOR position{};
	Ax = Aposition = 150; // x座標
	Ay = Aposition= 340; // y座標
	//A = Aposition = 0.0f;   // z座標


	//rabbitFlg = FALSE;
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
	/*if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		rabbitFlg = TRUE;

			if (rabbitFlg == TRUE && PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
				rabbit_Y -= 200;
			}
			if (rabbitFlg == TRUE && PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
				rabbit_Y += 200;
			}
			if (rabbitFlg == TRUE && PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
				rabbit_X -= 250;
			}
			if (rabbitFlg == TRUE && PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
				rabbit_X += 250;
			}
	}*/

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
		rabbit_Y -= 200;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
		rabbit_Y += 200;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		rabbit_X -= 250;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		rabbit_X += 250;
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

	//ウサギと猟犬を描画
	/*DrawBox(200 + rabbit_X, 250 + rabbit_Y, 300 + rabbit_X - 1, 350 + rabbit_Y - 1, GetColor(0, 0, 255), RabbitImg);
	DrawCircle(hound_X, hound_Y, hound_X - 1, hound_Y - 1, GetColor(0, 0, 255), HoundImg);*/


	//DrawCircle(125, 375, 50, 0x00ff00, TRUE);
	//DrawCircle(375, 375, 50, 0x00ff00, TRUE);
	//DrawCircle(625, 375, 50, 0x00ff00, TRUE);
	//DrawCircle(875, 375, 50, 0x00ff00, TRUE);
	//DrawCircle(1125, 375, 50, 0x00ff00, TRUE);


	//猟犬の駒(仮)
	DrawBox(890, 140, 960, 210, 0x0000ff, TRUE);     //上
	DrawBox(1100, 350, 1150, 400, 0x0000ff, TRUE);   //真ん中
	DrawBox(900, 550, 950, 600, 0x0000ff, TRUE);     //下

	//ウサギの駒(仮)
	DrawBox(150 + rabbit_X, 340 + rabbit_Y, 200 + rabbit_X, 390 + rabbit_Y, 0xff0000, TRUE);
	//DrawBox(A + rabbit_X, A + rabbit_Y, (A + 50) + rabbit_X, (A + 50) + rabbit_Y, 0xff0000, TRUE);

	DrawString(Ax, Ay, ("A"), 0xff0000);

	//DrawGraph(150 + rabbit_X, 340 + rabbit_Y, 0xff0000, RabbitImg[2]);
}