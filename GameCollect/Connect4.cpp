#include "Connect4.h"
#include"PadInput.h"

Connect4::Connect4()
{
	if ((gStageImg = LoadGraph("images/SixBallPazzle/Board2.png")) == -1);
	if ((gCursorImg = LoadGraph("images/SixBallPazzle/Arrow.png")) == -1);

	//配列の初期化
	/*for (int x; x < 6; x++) {
		for (int y; y < 7; y++) {
			 Board[x][y] = 0;
		}
	}*/

	
}

Connect4::~Connect4()
{
}

AbstractScene* Connect4::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {

		if (++Num > 7) Num = 0;	//右へ
	}

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {

		if (--Num < 0) Num = 2;	//左へ
	}

	Cursor = Num * 150;
	
	return this;
}

void Connect4::Draw() const
{
	DrawGraph(0, 0, gStageImg, TRUE);	//ステージ画像
	//DrawGraph(100, 210 + Cursor, 170, 230 + Cursor, 140, 250 + Cursor, 0xff0000, TRUE);	//カーソル画像
	DrawGraph(150 + Cursor, 0, gCursorImg, TRUE);	//カーソル画像

}
