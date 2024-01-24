#include "Connect4.h"
#include"PadInput.h"

Connect4::Connect4()
{
	if ((gStageImg = LoadGraph("images/SixBallPazzle/Board2.png")) == -1);	//ステージ画像読込
	if ((gCursorImg = LoadGraph("images/SixBallPazzle/Arrow.png")) == -1);	//矢印画像読込
	//if ((gBallImg = LoadGraph("images/SixBallPazzle/ball.png")) == -1);		//ボールの分割画像読込

	//配列の初期化
	/*for (int x; x < 6; x++) {
		for (int y; y < 7; y++) {
			Stage[x][y] = 0;
		}
	}*/

}

Connect4::~Connect4()
{
}

AbstractScene* Connect4::Update()
{
	/****** カーソルの移動処理 *******/
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
		if (++Num > 7) Num = 1;	//右へ
	}

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
		if (--Num < 1) Num = 7;	//左へ
	}

	Cursor = Num * 130;	//カーソルのX座標を増やす
	
	/******** Aボタンで赤色か黄色に切り替わる *******/
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {
		
	}

	return this;
}

void Connect4::Draw() const
{
	DrawGraph(0, 0, gStageImg, TRUE);		//ステージ画像
	DrawGraph(Cursor, 0, gCursorImg, TRUE);	//カーソル画像

	DrawFormatString(0, 100, 0xf0f0f0, "%d", Cursor);
	DrawFormatString(0, 200, 0xf0f0f0, "%c", Notation);
	//DrawFormatString(0, 300, 0xf0f0f0, "%d", Cursor);
	//DrawFormatString(0, 400, 0xf0f0f0, "%d", Cursor);

}
	
