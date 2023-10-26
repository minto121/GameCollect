#include "Checkermain.h"
#include "DxLib.h"
#include "PadInput.h"

Checkermain::Checkermain() {

	Boardimg = LoadGraph("../images/Checkers/banmen.png");
	PieceB = LoadGraph("../images/Checkers/WK.png");
	PieceW = LoadGraph("../images/Checkers/BK.png");
	Checkerback = LoadGraph("../images/Checkers/back.png");
	selectX = 0;
	selectY = 0;
}

Checkermain::~Checkermain()
{
}


AbstractScene* Checkermain::Update()
{
	InitBlock();
	g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;
	//ãˆÚ“®
	if (g_KeyFlg & PAD_INPUT_UP) {
		if (selectY >= 0 && selectY <= 7) {
			selectY = selectY - 1;
		}
		if (selectY < 0) {
			selectY = 7;
		}
	}
	//‰ºˆÚ“®
	if (g_KeyFlg & PAD_INPUT_DOWN) {
		if (selectY >=0  && selectY < 8) {
			selectY = selectY + 1;
		}
		if (selectY > 7 ) {
			selectY = 0;
		}
	}
	//‰EˆÚ“®
	if (g_KeyFlg & PAD_INPUT_LEFT) {
		if (selectX >= 0 && selectX <= 7) {
			selectX = selectX - 1;
		}
		if (selectX < 0) {
			selectX = 7;
		}
	}
	//¶ˆÚ“®
	if (g_KeyFlg & PAD_INPUT_RIGHT) {
		if (selectX >= 0 && selectX < 8) {
			selectX = selectX + 1;
		}
		if (selectX > 7) {
			selectX = 0;
		}
	}
	return this;
}

void Checkermain::Draw() const
{
	
	DrawGraph(0, 0, Checkerback, FALSE);
	DrawGraph(180, 0, Boardimg, TRUE);
	DrawRotaGraph(480, 110,2,0, PieceB, TRUE);
	DrawRotaGraph(480, 610, 2, 0, PieceW, TRUE);
	DrawFormatString(0, 0, 0x000000, "%d", selectY);
	DrawFormatString(0,30, 0x000000, "%d", selectX);
	DrawBox(372 + (selectX*71), 72 + (selectY * 71), 445+ (selectX * 71), 145 + (selectY * 71), GetColor(0, 250, 0), FALSE);    // ŽlŠpŒ`‚ð•`‰æ

	
}

void Checkermain::InitBlock() const
{
	/*for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[x][y] == 0) {
			
			}
		
		}
	}*/
}

