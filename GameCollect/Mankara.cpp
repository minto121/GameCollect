#include "Mankara.h"
#include"DxLib.h"
#include"PadInput.h"
Mankara::Mankara()
{
	StoneImg[6] = LoadDivGraph("images/Mancala/MancalaStone.png", 6, 6, 1, 32, 32, StoneImg);
	Board = LoadGraph("images/mancala/MancalaBoard.png");
	Background = LoadGraph("images/Mancala/BackGround02.png");
	//P1PocketImg = LoadGraph("images/Mancala/1PPocket.png");
	//P2PocketImg = LoadGraph("images/Mancala/2PPocket.png");

	P1BigPocket = 0;
	P2BigPocket = 0;

	Pocket_cnt = 0;

	P1Pocket[0] = 1;
	P2Pocket[0] = 1;
	// 初期石
	InitialStone = 4;
	Stone_cnt = 1;
	movePocket = 0;
	// ぴったりゴール用変数
	JustGoal = 0;

	for (int y = 0; y < 6; y++) {
		P1Pocket[y] += 1;
	}

	for (int y = 0; y < 6; y++) {
		P2Pocket[y] += 1;
	}

	// 石の画像処理(ポケット)
	for (int i = 0; i < 6; i++) {
		for (int y = 0; y < 6; y++) {
			gStone[y][i].img = StoneImg[y];//ポケット１
			gStone2[y][i].img = StoneImg[y];//ポケット１
		}
	}

	// 石の画像処理(ゴール)
	for (int i = 0; i < 30; i++) {
		for (int y = 0; y < 6; y++) {
			gGoal[y][i].img = StoneImg[y];//ポケット１
			
		}
	}


	for (int i = 0; i < 7; i++) {
		StonePocket[0][i] = InitialStone; // 1P（[1]）のポケット（[6]）の中にStone_cntの初期値（4）を格納
		StonePocket[1][i] = InitialStone; // 2P（[1]）のポケット（[6]）の中にStone_cntの初期値（4）を格納
	}

	for (int Pocket = 0; Pocket < 7;) {
		for (int i = 0; i < 4; i++) {
			P1StoneSave[Pocket][i] = gStone[Pocket][i].img;
			P2StoneSave[Pocket][i] = gStone[Pocket][i].img;
		}
		Pocket++;
	}

}

AbstractScene* Mankara::Update()
{
	// 相手のターンはプレイヤーは動かない
	if (P2Turn == 1) {
		P1Turn = 0;
	}

	// ターン切り替え
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_X)) {
		P2Turn = 1;
		P1Turn = 0;
	}

	// プレイヤーのターンは相手は動かない
	if (P1Turn == 1) {
		P2Turn = 0;
	}

	// ターン切り替え
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y)) {
		P1Turn = 1;
		P2Turn = 0;
	}


	if (P1Turn == 1) {
		// ポケットの選択
		// 右に移動
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
			Pocket_cnt++;
			if (Pocket_cnt > 5) {
				Pocket_cnt = 0;

			}
		} // 左に移動
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
			Pocket_cnt--;

			if (Pocket_cnt < 0) {
				Pocket_cnt = 5;
			}
		}
	}

	if (P2Turn == 1) {
		// ポケットの選択
		// 右に移動
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
			Pocket_cnt++;
			if (Pocket_cnt > 5) {
				Pocket_cnt = 0;
			}
		} // 左に移動
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
			Pocket_cnt--;
			if (Pocket_cnt < 0) {
				Pocket_cnt = 5;
			}
		}
	}

	MoveStone();

	//1P用石の移動処理
	if (P1Turn == 1) {
		if (Pocket_cnt == 0) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				// Aボタンで決定した時に選択したポケット以外をFALSEにする処理
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = TRUE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = FALSE;

			}
		}
		else if (Pocket_cnt == 1) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = TRUE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = FALSE;
			}
		}
		else if (Pocket_cnt == 2) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = TRUE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = FALSE;
			}
		}
		else if (Pocket_cnt == 3) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = TRUE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = FALSE;
			}
		}
		else if (Pocket_cnt == 4) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = TRUE;
				P1Pocket[5] = FALSE;
			}
		}
		else if (Pocket_cnt == 5) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = TRUE;
			}
		}
	}


	//2P用石の移動処理
	if (P2Turn == 1) {
		if (Pocket_cnt == 0) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = TRUE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = FALSE;

			}
		}
		else if (Pocket_cnt == 1) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = TRUE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = FALSE;
			}
		}
		else if (Pocket_cnt == 2) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = TRUE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = FALSE;
			}
		}
		else if (Pocket_cnt == 3) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = TRUE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = FALSE;
			}
		}
		else if (Pocket_cnt == 4) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = TRUE;
				P2Pocket[5] = FALSE;
			}
		}
		else if (Pocket_cnt == 5) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = TRUE;
			}
		}
	}

	return this;
}

void Mankara::Draw()const
{
	DrawGraph(0, 0, Background, TRUE);
	DrawGraph(30, 30, Board, TRUE);

	// -----------ここから石の初期配置--------------

	// 石（ポケット１）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(280, 380 + i * 20, gStone[i][0].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(310, 220 + i * 20, gStone[i][0].img, TRUE);
	}
	// 石（ポケット２）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(400, 380 + i * 20, gStone[i][1].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(430, 220 + i * 20, gStone[i][1].img, TRUE);
	}
	// 石（ポケット３）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(530, 380 + i * 20, gStone[i][2].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(560, 220 + i * 20, gStone[i][2].img, TRUE);
	}
	// 石（ポケット４）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(655, 380 + i * 20, gStone[i][3].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(685, 220 + i * 20, gStone[i][3].img, TRUE);
	}
	// 石（ポケット５）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(780, 380 + i * 20, gStone[i][4].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(810, 220 + i * 20, gStone[i][4].img, TRUE);
	}
	// 石（ポケット６）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(905, 380 + i * 20, gStone[i][5].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(935, 220 + i * 20, gStone[i][5].img, TRUE);
	}

	//// 2P石の初期配置
	// -----------ここから石の初期配置--------------

	// 石（ポケット１）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(905, 100 + i * 20, gStone[i][0].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(935, -60 + i * 20, gStone[i][0].img, TRUE);
	}
	// 石（ポケット２）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(780, 100 + i * 20, gStone[i][1].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(810, -60+ i * 20, gStone[i][1].img, TRUE);
	}
	// 石（ポケット３）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(655, 100 + i * 20, gStone[i][2].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(685, -60 + i * 20, gStone[i][2].img, TRUE);
	}
	// 石（ポケット４）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(530, 100 + i * 20, gStone[i][3].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(560, -60 + i * 20, gStone[i][3].img, TRUE);
	}
	// 石（ポケット５）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(400, 100 + i * 20, gStone[i][4].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(430, -60 + i * 20, gStone[i][4].img, TRUE);
	}
	// 石（ポケット６）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(280, 100 + i * 20, gStone[i][5].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(310, -60 + i * 20, gStone[i][5].img, TRUE);
	}


	// 石（ゴール）の初期配置
	for (int i = 0; i < 30; i++) {
		DrawGraph(1100, 140 + i * 20, gGoal[i][0].img, TRUE);
	}


	//------------- ここまで-----------------


	// ポケットを選択
	if (moveStone == 0) {
		// 選択したポケットに格納されている石を移動させる
		for (int i = 0; i < P1StoneSave[0][i += InitialStone]; i++) {
			DrawGraph(425 + i * 125, 550, P1StoneSave[moveStone][i], TRUE);
		}
	}
	else if (moveStone == 1) {
		// 選択したポケットに格納されている石を移動させる
		for (int i = 0; i < P1StoneSave[0][i += InitialStone]; i++) {
			DrawGraph(425 + i * 125, 550, P1StoneSave[moveStone][i], TRUE);
		}
	}// ポケットを選択
	else if (moveStone == 2) {
		// 選択したポケットに格納されている石を移動させる
		for (int i = 0; i < P1StoneSave[0][i += InitialStone]; i++) {
			DrawGraph(425 + i * 125, 550, P1StoneSave[moveStone][i], TRUE);
		}
	}
	else if (moveStone == 3) {
		// 選択したポケットに格納されている石を移動させる
		for (int i = 0; i < P1StoneSave[0][i += InitialStone]; i++) {
			DrawGraph(425 + i * 125, 550, P1StoneSave[moveStone][i], TRUE);
		}
	}
	// ポケットを選択
	else if (moveStone == 4) {
		// 選択したポケットに格納されている石を移動させる
		for (int i = 0; i < P1StoneSave[0][i += InitialStone]; i++) {
			DrawGraph(425 + i * 125, 550, P1StoneSave[moveStone][i], TRUE);
		}
	}
	else if (moveStone == 5) {
		// 選択したポケットに格納されている石を移動させる
		for (int i = 0; i < P1StoneSave[0][i += InitialStone]; i++) {
			DrawGraph(425 + i * 125, 550, P1StoneSave[moveStone][i], TRUE);
		}
	}


	// 1Pターン時の ポケット移動
	if (P1Turn == 1) {
		if (Pocket_cnt == 0) {
			/*	DrawGraph(255, 385, P1PocketImg, FALSE);*/
			DrawBox(255, 385, 355, 600, GetColor(0, 0, 255), FALSE);
			DrawBox(256, 386, 356, 601, GetColor(0, 0, 255), FALSE);
			DrawBox(257, 387, 357, 602, GetColor(0, 0, 255), FALSE);
		}
		else if (Pocket_cnt == 1) {
			DrawBox(385, 385, 485, 600, GetColor(0, 0, 255), FALSE);
			DrawBox(386, 386, 486, 601, GetColor(0, 0, 255), FALSE);
			DrawBox(387, 387, 487, 602, GetColor(0, 0, 255), FALSE);

		}
		else if (Pocket_cnt == 2) {
			DrawBox(515, 385, 615, 600, GetColor(0, 0, 255), FALSE);
			DrawBox(516, 386, 616, 601, GetColor(0, 0, 255), FALSE);
			DrawBox(517, 387, 617, 602, GetColor(0, 0, 255), FALSE);

		}
		else if (Pocket_cnt == 3) {
			DrawBox(645, 385, 745, 600, GetColor(0, 0, 255), FALSE);
			DrawBox(646, 386, 746, 601, GetColor(0, 0, 255), FALSE);
			DrawBox(647, 387, 747, 602, GetColor(0, 0, 255), FALSE);

		}
		else if (Pocket_cnt == 4) {
			DrawBox(770, 385, 870, 600, GetColor(0, 0, 255), FALSE);
			DrawBox(771, 386, 871, 601, GetColor(0, 0, 255), FALSE);
			DrawBox(772, 387, 872, 602, GetColor(0, 0, 255), FALSE);

		}
		else if (Pocket_cnt == 5) {
			DrawBox(900, 385, 1000, 600, GetColor(0, 0, 255), FALSE);
			DrawBox(901, 386, 1001, 601, GetColor(0, 0, 255), FALSE);
			DrawBox(902, 387, 1002, 602, GetColor(0, 0, 255), FALSE);
		}

	}


	// 2Pターン時のポケット移動
	if (P2Turn == 1) {
		if (Pocket_cnt == 0) {
			DrawBox(900, 85, 1000, 300, GetColor(255, 0, 0), FALSE);
			DrawBox(901, 86, 1001, 301, GetColor(255, 0, 0), FALSE);
			DrawBox(902, 87, 1002, 302, GetColor(255, 0, 0), FALSE);
		}
		else if (Pocket_cnt == 1) {
			DrawBox(255, 85, 355, 300, GetColor(255, 0, 0), FALSE);
			DrawBox(256, 86, 356, 301, GetColor(255, 0, 0), FALSE);
			DrawBox(257, 87, 357, 302, GetColor(255, 0, 0), FALSE);
		}
		else if (Pocket_cnt == 2) {
			DrawBox(385, 85, 485, 300, GetColor(255, 0, 0), FALSE);
			DrawBox(386, 86, 486, 301, GetColor(255, 0, 0), FALSE);
			DrawBox(387, 87, 487, 302, GetColor(255, 0, 0), FALSE);

		}
		else if (Pocket_cnt == 3) {
			DrawBox(515, 85, 615, 300, GetColor(255, 0, 0), FALSE);
			DrawBox(516, 86, 616, 301, GetColor(255, 0, 0), FALSE);
			DrawBox(517, 87, 617, 302, GetColor(255, 0, 0), FALSE);

		}
		else if (Pocket_cnt == 4) {
			DrawBox(645, 85, 745, 300, GetColor(255, 0, 0), FALSE);
			DrawBox(646, 86, 746, 301, GetColor(255, 0, 0), FALSE);
			DrawBox(647, 87, 747, 302, GetColor(255, 0, 0), FALSE);

		}
		else if (Pocket_cnt == 5) {
			DrawBox(770, 85, 870, 300, GetColor(255, 0, 0), FALSE);
			DrawBox(771, 86, 871, 301, GetColor(255, 0, 0), FALSE);
			DrawBox(772, 87, 872, 302, GetColor(255, 0, 0), FALSE);

		}

	}

	////ポケットの中に値が入っているか
	//for (int i = 0; i < 6; i++) {
	//	DrawFormatString(300 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", P1Pocket[i]);
	//	DrawFormatString(500 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", P2Pocket[i]);
	//}


	// ゴールに入った石の数
	DrawBox(1075, 85, 1110, 120, GetColor(200, 200, 255), TRUE);
	DrawBox(1075, 85, 1110, 120, GetColor(0, 0, 255), FALSE);
	DrawFormatString(1090, 95, GetColor(0, 0, 0), "%d", P1BigPocket);
	DrawFormatString(1085, 60, GetColor(0, 0, 255), "1P");

	DrawBox(135, 565, 170, 605, GetColor(255, 200, 200), TRUE);
	DrawBox(135, 565, 170, 605, GetColor(255, 0, 0), FALSE);
	DrawFormatString(150, 570, GetColor(255, 0, 0), "%d", P2BigPocket);
	DrawFormatString(150, 610, GetColor(255, 0, 0), "2P");


	// ターン切り替え
	if (P2Turn == 1) {
		DrawFormatString(200, 200, GetColor(255, 255, 255), "2P TURN");
	}

	if (P1Turn == 1) {
		DrawFormatString(200, 200, GetColor(255, 255, 255), "1P TURN");
	}
}

void Mankara::MoveStone()
{
	// 画像移動用
	if (PlayerPocket >= 0) {
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {

			StoneFlg = TRUE;

			if (StoneFlg == TRUE) {
				moveStone = PlayerPocket;

			}
		}
	}
	if (PartnerPocket >= 0) {
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {

			StoneFlg = TRUE;

			if (StoneFlg == TRUE) {
				moveStone2 = PartnerPocket;

			}
		}
	}

	//　画像移動時の数的処理
	if (P1Turn == TRUE) {

		// ポケットを選択
		if (moveStone == 0) {
		}
		else if (moveStone == 1) {
		}
		else if (moveStone == 2) {		
		}
		else if (moveStone == 3) {
		}
		else if (moveStone == 4) {
			
		}
		else if (moveStone == 5) {			
		}
	}
}
