#include "Mankara.h"
#include"DxLib.h"
#include"PadInput.h"
Mankara::Mankara()
{
	Board = LoadGraph("../images/mancala/MancalaBoard.png");
	Background = LoadGraph("../images/Mancala/BackGround02.png");

	P1BigPocket = 0;
	P2BigPocket = 0;
	Pocket1P = DrawCircle(P1Pocket[0] + 50, P1Pocket[0] + 50, GetColor(255, 0, 0),TRUE);

	//for (int i = 0; i < 8; i++) {
	//	Stone[i].x = 500;
	//	Stone[i].y = 500;br
	//	Stone[i].detection = 1;
	//	Stone[i].Event = 0;
	//	Stone[i].count = 0;
	//	Stone[i].Flg = 0;
	//}

	for (int i = 0; i < 8; i++) {
		redStone[i]++;
	}

	for (int i = 0; i < 8; i++) {
		blueStone[i]++;
	}

	for (int i = 0; i < 8; i++) {
		greenStone[i]++;
	}

	for (int i = 0; i < 8; i++) {
		yellowStone[i]++;
	}
	
	for (int i = 0; i < 8; i++) {
		purpleStone[i]++;
	}
	
	for (int i = 0; i < 8; i++) {
		whiteStone[i]++;
	}

	P1Pocket[0] = 1;
	P2Pocket[0] = 1;

	for (int y = 0; y < 6; y++) {
		P1Pocket[y]+=1;
	}

	for (int y = 0; y < 6; y++) {
		P2Pocket[y]+=1;
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
	DrawGraph(100, 100, P1Pocket[0], TRUE);

	DrawBox(100, 100, 225, 550, GetColor(255, 0, 0), TRUE);

	DrawBox(255, 385, 355, 600, GetColor(255, 0, 0), TRUE);
	DrawBox(385, 385, 485, 600, GetColor(255, 0, 0), TRUE);
	DrawBox(515, 385, 615, 600, GetColor(255, 0, 0), TRUE);
	DrawBox(645, 385, 745, 600, GetColor(255, 0, 0), TRUE);
	DrawBox(770, 385, 870, 600, GetColor(255, 0, 0), TRUE);
	DrawBox(900, 385, 1000, 600, GetColor(255, 0, 0), TRUE);


	DrawBox(1030, 150, 1160, 600, GetColor(255, 0, 0), TRUE);

	DrawBox(255, 85, 355, 300, GetColor(255, 0, 0), TRUE);
	DrawBox(385, 85, 485, 300, GetColor(255, 0, 0), TRUE);
	DrawBox(515, 85, 615, 300, GetColor(255, 0, 0), TRUE);
	DrawBox(645, 85, 745, 300, GetColor(255, 0, 0), TRUE);
	DrawBox(770, 85, 870, 300, GetColor(255, 0, 0), TRUE);
	DrawBox(900, 85, 1000, 300, GetColor(255, 0, 0), TRUE);


	for (int i = 0; i < 8; i++) {
		//DrawFormatString(100 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", redStone[i]);
		//DrawFormatString(200 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", blueStone[i]);
		//DrawFormatString(300 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", greenStone[i]);
		//DrawFormatString(400 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", yellowStone[i]);
		//DrawFormatString(500 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", purpleStone[i]);
		//DrawFormatString(600 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", whiteStone[i]);

	}

	for (int i = 0; i < 6; i++) {
		DrawFormatString(700 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", P1Pocket[i]);
		DrawFormatString(900 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", P2Pocket[i]);
	}
	
	DrawCircle(500, 500, GetColor(0, 0, 0), P1Pocket[0], FALSE);

	// ターン切り替え
	if (P2Turn == 1 ) {
		DrawFormatString(200,200,GetColor(255,255,255),"2P TURN");
	}

	if (P1Turn == 1) {
		DrawFormatString(200, 200, GetColor(255, 255, 255), "1P TURN");
	}



	// 1p用石の移動

	if (P1Turn == 1) {
		if (P1Pocket[0] == TRUE) {

		}
		else if (P1Pocket[1] == TRUE) {

		}
		else if (P1Pocket[2] == TRUE) {

		}
		else if (P1Pocket[3] == TRUE) {

		}
		else if (P1Pocket[4] == TRUE) {

		}
		else if (P1Pocket[5] == TRUE) {
		
		}
		else if (P1Pocket[6] == TRUE) {

		}

	} 
	
	// ２P用石の移動

	if (P2Turn == 1) {

		if (P2Pocket[0] == TRUE) {

		}
		else if (P2Pocket[1] == TRUE) {

		}
		else if (P2Pocket[2] == TRUE) {

		}
		else if (P2Pocket[3] == TRUE) {

		}
		else if (P2Pocket[4] == TRUE) {

		}
		else if (P2Pocket[5] == TRUE) {
		
		}
		else if (P2Pocket[6] == TRUE) {

		}
	}
	
}
