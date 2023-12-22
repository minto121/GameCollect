#include"RabbitAndHounds.h"
#include "Rabbit.h"
#include "Hound.h"
#include "DxLib.h"
#include "PadInput.h"
#include<iostream>

static int MenuNumber = 0;
int Cursor_X = 0;

RabbitAndHounds::RabbitAndHounds()
{
	BackGroundImg = LoadGraph("images/RabbitAndHounds/BackGround01.png");
	//3Dモデルの読込
	//HoundImg = MV1LoadModel("Dog_Model.mv1");
	//RabbitImg = MV1LoadModel("Rabbit_Model.mv1");

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
	//十字キー右 
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		Cursor_X = 480;
		Player = 1;
	}
	//十字キー左
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		Cursor_X = -10;
		Player = 2;
	}
	
	//Aボタンを押してプレイヤーの操作する方を選ぶ
	if (Cursor_X <= 300 && PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true))
	{
		return new Rabbit();
	}
	else if (Cursor_X >= 300 && PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true))
	{
		return new Hound();
	}
		return this;
}

void RabbitAndHounds::Draw() const
{
	//タイトル
	DrawString(10, 20, "ウサギと猟犬", 0xffffff);
	//背景画像
	DrawGraph(0, 0, BackGroundImg, TRUE);

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
	else
	{
		DrawString(600, 100, "プレイヤーは猟犬", 0xffffff);
	}

}
