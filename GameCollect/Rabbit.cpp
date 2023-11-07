#include"RabbitAndHounds.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Rabbit.h"

Rabbit::Rabbit()
{
	BackGroundImg = LoadGraph("images/RabbitAndHounds/BackGround02.png");

	//3Dモデルの読込
	HoundImg = MV1LoadModel("Dog_Model.mv1");
	RabbitImg = MV1LoadModel("Rabbit_Model.mv1");
}

Rabbit::~Rabbit()
{
	// モデルハンドルの削除
	MV1DeleteModel(HoundImg);
	MV1DeleteModel(RabbitImg);
}

AbstractScene* Rabbit::Update()
{
	//ウサギ座標
	rabbit_X = 100, rabbit_Y = 100;

	// ウサギを移動
	if (CheckHitKey(KEY_INPUT_UP)) {
		rabbit_Y -= rabbitSpeed;
	}
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		rabbit_Y += rabbitSpeed;
	}
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		rabbit_X -= rabbitSpeed;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		rabbit_X += rabbitSpeed;
	}

	return this;
}

void Rabbit::Draw() const
{
	//背景画像
	DrawGraph(0, 0, BackGroundImg, TRUE);

	//タイトル
	DrawString(10, 20, "プレイヤー操作はウサギ", 0x000000);

	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -1000), VGet(0, 0, 0));

	// 画面に映る位置に３Ｄモデルを移動
	MV1SetPosition(HoundImg, VGet(320.0f, -300.0f, 600.0f));
	MV1SetPosition(RabbitImg, VGet(320.0f, -300.0f, 600.0f));

	//3Dモデルの描画
	MV1DrawModel(HoundImg);
	MV1DrawModel(RabbitImg);

	////ウサギと猟犬を描画
	//DrawBox(rabbit_X, rabbit_Y, rabbit_X - 1, rabbit_Y - 1, GetColor(0, 0, 255), RabbitImg);
	//DrawCircle(hound_X, hound_Y, hound_X - 1, hound_Y - 1, GetColor(0, 0, 255), TRUE);

	DrawBox(300, 350, 400, 450, GetColor(255, 0, 0), TRUE);
	DrawCircle(900, 400, 60, GetColor(0, 0, 255), TRUE);

}