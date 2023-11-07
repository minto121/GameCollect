#include"RabbitAndHounds.h"
#include "DxLib.h"
#include "PadInput.h"
#include<iostream>

static int MenuNumber = 0;
int Cursor_X = 0;

RabbitAndHounds::RabbitAndHounds()
{
	BackGroundImg = LoadGraph("images/RabbitAndHounds/BackGround01.png");
	//3Dモデルの読込
	/*HoundImg = MV1LoadModel("Dog_Model.mv1");
	RabbitImg = MV1LoadModel("Rabbit_Model.mv1");*/

	////ウサギ座標
	//rabbit_X = 100, rabbit_Y = 100;
	//rabbitSpeed = 2;

	////猟犬座標
	//hound_X = 400, hound_Y = 400;
	//houndSpeed = 1;

	Cursor_X = 0;

	Player = 0;
}

RabbitAndHounds::~RabbitAndHounds()
{
	// モデルハンドルの削除
	/*MV1DeleteModel(HoundImg);
	MV1DeleteModel(RabbitImg);*/
}

AbstractScene* RabbitAndHounds::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		Cursor_X = 480;
		if (XINPUT_BUTTON_A)
		{
			Player = 1;
		}
	}
	
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		Cursor_X = -10;
		if (XINPUT_BUTTON_A)
		{
			Player = 2;
		}
	}
		return this;
}

//void RabbitAndHounds::RabbitPiece()
//{
//	//ウサギ座標
//	rabbit_X = 100, rabbit_Y = 100;
//
//	// ウサギを移動
//	if (CheckHitKey(KEY_INPUT_UP)) {
//		rabbit_Y -= rabbitSpeed;
//	}
//	if (CheckHitKey(KEY_INPUT_DOWN)) {
//		rabbit_Y += rabbitSpeed;
//	}
//	if (CheckHitKey(KEY_INPUT_LEFT)) {
//		rabbit_X -= rabbitSpeed;
//	}
//	if (CheckHitKey(KEY_INPUT_RIGHT)) {
//		rabbit_X += rabbitSpeed;
//	}
//}
//
//void RabbitAndHounds::HoundIPiece()
//{
//	// 猟犬を移動
//	if (rabbit_X < hound_X) {
//		hound_X -= houndSpeed;
//	}
//	if (rabbit_X > hound_X) {
//		hound_X += houndSpeed;
//	}
//	if (rabbit_Y < hound_Y) {
//		hound_Y -= houndSpeed;
//	}
//	if (rabbit_Y > hound_Y) {
//		hound_Y += houndSpeed;
//	}
//}

void RabbitAndHounds::Draw() const
{
	//タイトル
	DrawString(10, 20, "ウサギと猟犬", 0xffffff);
	//背景画像
	DrawGraph(0, 0, BackGroundImg, TRUE);

	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -1000), VGet(0, 0, 0));

	// 画面に映る位置に３Ｄモデルを移動
	MV1SetPosition(HoundImg, VGet(320.0f, -300.0f, 600.0f));
	MV1SetPosition(RabbitImg, VGet(320.0f, -300.0f, 600.0f));

	//3Dモデルの描画
	MV1DrawModel(HoundImg);
	MV1DrawModel(RabbitImg);

	// ウサギと猟犬を描画
	DrawBox(rabbit_X, rabbit_Y, rabbit_X-1, rabbit_Y-1, GetColor(0, 0, 255), TRUE);
	DrawCircle(hound_X, hound_Y, hound_X-1, hound_Y-1, GetColor(0, 0, 255), TRUE);

	

	// 描画する文字列のサイズを設定
	SetFontSize(50);
	DrawString(300, 350, "ウサギ", 0xffffff);
	DrawString(800, 350, "猟犬", 0xffffff);

	//カーソル描画
	DrawTriangle(260 + Cursor_X, 360, 290 + Cursor_X, 380, 260 + Cursor_X, 400, GetColor(255, 0, 0), TRUE);

	//プレイヤー操作決め
	if (Player != 1) {
		DrawString(100, 100, "プレイヤーはウサギ", 0xffffff);
	}
	else {
		DrawString(600, 100, "プレイヤーは猟犬", 0xffffff);
	}

}
