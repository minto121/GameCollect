#include "Mankara.h"
#include"DxLib.h"
#include"PadInput.h"
Mankara::Mankara()
{
	Board = LoadGraph("../images/mancala/MancalaBoard.png");
	Background = LoadGraph("../images/Mancala/BackGround02.png");
	/* RedStone = 1;
	 BlueStone = 1;
	 GreenStone = 1;
	 YellowStone = 1;*/

	for (int i = 0; i < 8; i++) {
		redStone[i]=0;
	}

	for (int i = 0; i < 8; i++) {
		blueStone[i]=1;
	}

	for (int i = 0; i < 8; i++) {
		greenStone[i]=2;
	}

	for (int i = 0; i < 8; i++) {
		yellowStone[i]=3;
	}
	
	for (int i = 0; i < 8; i++) {
		purpleStone[i]=4;
	}
	
	for (int i = 0; i < 8; i++) {
		whiteStone[i]=5;
	}



	for (int y = 0; y < 6; y++) {
		P1Pocket[y]=10;
	}

	for (int y = 0; y < 6; y++) {
		P2Pocket[y]=10;
	}
	
}

 AbstractScene* Mankara:: Update()
{

	 // 相手のターンはプレイヤーは動かない
	 if (PAD_INPUT::OnButton(XINPUT_BUTTON_X)) {
		 P2Turn = 1;
		 P1Turn = 0;
	 }
	 // プレイヤーのターンは相手は動かない
	 if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y)) {
		 P1Turn = 1;
		 P2Turn = 0;
	 }

	return this;
}

void Mankara::Draw()const
{
	DrawGraph(0, 0, Background, TRUE);
	DrawGraph(30,30,Board,TRUE);
	
	for (int i = 0; i < 8; i++) {
		DrawFormatString(100 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", redStone[i]);
		DrawFormatString(200 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", blueStone[i]);
		DrawFormatString(300 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", greenStone[i]);
		DrawFormatString(400 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", yellowStone[i]);
		DrawFormatString(500 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", purpleStone[i]);
		DrawFormatString(600 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", whiteStone[i]);

	}


	for (int i = 0; i < 6; i++) {
		DrawFormatString(700 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", P1Pocket[i]);
		DrawFormatString(800 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", P2Pocket[i]);
	}
	

	// ターン切り替え
	if (P2Turn == 1 ) {
		DrawFormatString(200,200,GetColor(255,255,255),"2P TURN");
	}

	if (P1Turn == 1) {
		DrawFormatString(200, 200, GetColor(255, 255, 255), "1P TURN");
	}


	
}
