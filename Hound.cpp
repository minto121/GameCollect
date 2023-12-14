#include"RabbitAndHounds.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Hound.h"

Hound::Hound()
{
	BackGroundImg = LoadGraph("images/RabbitAndHounds/BackGround02.png");

	//3Dモデルの読込
	HoundImg = MV1LoadModel("Dog_Model.mv1");
	RabbitImg = MV1LoadModel("Rabbit_Model.mv1");

	// テクスチャの読み込み
	R_texture = LoadGraph("images/RabbitAndHounds/Textures/Coloe_Textures/T_PigHead_00.TGA");

	hound_X = 0;
	hound_Y = 0;

}

Hound::~Hound()
{
	// モデルハンドルの削除
	/*MV1DeleteModel(HoundImg);
	MV1DeleteModel(RabbitImg);*/
}

AbstractScene* Hound::Update()
{

	////ウサギ座標
	//rabbit_X = 100, rabbit_Y = 100;

	//if (PAD_INPUT::OnButton(KEY_INPUT_RIGHT) == true)
	//{
	//	rabbit_X = 200;
	//}

	// 猟犬を移動
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP)) {
		hound_Y -= 200;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN)) {
		hound_Y += 200;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		hound_X -= 200;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		hound_X += 200;
	}

	return this;
}

void Hound::Draw() const
{
	//背景画像
	DrawGraph(0, 0, BackGroundImg, TRUE);

	//タイトル
	DrawString(10, 20, "プレイヤー操作は猟犬", 0x000000);

	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -1000), VGet(0, 0, 0));

	// 画面に映る位置に３Ｄモデルを移動
	MV1SetPosition(RabbitImg, VGet(320.0f, -300.0f, 600.0f));
	MV1SetScale(RabbitImg, VGet(1, 1, 1)); // モデルのスケールを設定
	MV1SetRotationXYZ(RabbitImg, VGet(0, 0, 0)); // モデルの回転を設定

	// テクスチャの設定
	SetUseTextureToShader(0, R_texture);

	//MV1SetPosition(HoundImg, VGet(320.0f, -300.0f, 600.0f));

	//3Dモデルの描画
	MV1DrawModel(RabbitImg);
	MV1DrawModel(HoundImg);

	//ウサギと猟犬を描画
	/*DrawBox(200 + rabbit_X, 250 + rabbit_Y, 300 + rabbit_X - 1, 350 + rabbit_Y - 1, GetColor(0, 0, 255), RabbitImg);
	DrawCircle(hound_X, hound_Y, hound_X - 1, hound_Y - 1, GetColor(0, 0, 255), HoundImg);*/


	DrawCircle(325, 375, 50, 0x00ff00, TRUE);


	//猟犬の駒(仮)
	DrawBox(890, 140, 960, 210, 0x0000ff, TRUE);     //上
	DrawBox(1100, 350, 1150, 400, 0x0000ff, TRUE);   //真ん中
	DrawBox(900, 550, 950, 600, 0x0000ff, TRUE);     //下

	//ウサギの駒(仮)
	DrawBox(100 + hound_X, 350 + hound_Y, 150 + hound_X, 400 + hound_Y, 0xff0000, HoundImg);
}