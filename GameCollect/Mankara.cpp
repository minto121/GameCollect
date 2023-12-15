#include "Mankara.h"
#include"DxLib.h"
#include"PadInput.h"
Mankara::Mankara()
{
	StoneImg[6] = LoadDivGraph("images/Mancala/MancalaStone.png", 6, 6, 1, 32, 32, StoneImg);
	Board = LoadGraph("images/mancala/MancalaBoard.png");
	Background = LoadGraph("images/Mancala/BackGround02.png");

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

	MoveStoneFlg = FALSE;
	MoveStoneFlg2 = FALSE;
	MoveStoneFlg3 = FALSE;
	MoveStoneFlg4 = FALSE;
	MoveStoneFlg5 = FALSE;
	MoveStoneFlg6 = FALSE;

	MoveStoneFlg7 = FALSE;
	MoveStoneFlg8 = FALSE;
	MoveStoneFlg9 = FALSE;
	MoveStoneFlg10 = FALSE;
	MoveStoneFlg11 = FALSE;
	MoveStoneFlg12 = FALSE;

	for (int y = 0; y < 6; y++) {
		P1Pocket[y] = 0;
	}

	for (int y = 0; y < 6; y++) {
		P2Pocket[y] = 0;
	}

	// 石の画像処理(ポケット)
	for (int i = 0; i < 6; i++) {
		for (int y = 0; y < 6; y++) {
			gStone[y][i].img = StoneImg[y], P1Pocket[i];//ポケット１
			gStone2[y][i].img = StoneImg[y],P2Pocket[i] ;//ポケット１
		}
	}

	// 石の画像処理(ゴール)
	for (int i = 0; i < 30; i++) {
		for (int y = 0; y < 6; y++) {
			gGoal[y][i].img = StoneImg[y];//ポケット１
			
		}
	}


	for (int i = 0; i < 12; i++) {
		StonePocket[i] = InitialStone; // 1P（[1]）のポケット（[6]）の中にStone_cntの初期値（4）を格納
	}

	for (int pocket = 0; pocket < 6;) {
		P1StoneSave[pocket] = 4;
		P2StoneSave[pocket] = 4;
		pocket++;
	}

	for (int i = 4; i < 16; i++) {
		gStone[i][0].img = FALSE ;
		gStone[i][1].img = FALSE ;
		gStone[i][2].img = FALSE ;
		gStone[i][3].img = FALSE ;
		gStone[i][4].img = FALSE ;
		gStone[i][5].img = FALSE ;
	}
	for (int i = 4; i < 16; i++) {
		gStone2[i][0].img = FALSE;
		gStone2[i][1].img = FALSE;
		gStone2[i][2].img = FALSE;
		gStone2[i][3].img = FALSE;
		gStone2[i][4].img = FALSE;
		gStone2[i][5].img = FALSE;
	}
	for (int i = 0; i < 30; i++) {
		gGoal[0][i].img = FALSE ;
		gGoal[1][i].img = FALSE ;
		
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
				Pocket_cnt = 5;

			}
		} // 左に移動
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
			Pocket_cnt--;
			if (Pocket_cnt < 0) {
				Pocket_cnt = 0;
			}
		}
	}

	if (P2Turn == 1) {
		// ポケットの選択
		// 右に移動
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
			Pocket_cnt--;
			if (Pocket_cnt < 0) {
				Pocket_cnt = 0;
			}
		} // 左に移動
		else if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
			Pocket_cnt++;
			if (Pocket_cnt > 5) {
				Pocket_cnt = 5;
			}
		}
	}

	

	//1P用石の移動処理
	if (P1Turn == 1) {
		if (Pocket_cnt == 0) {
			if (MoveStoneFlg == TRUE) {
				// Aボタンで決定した時に選択したポケット以外をFALSEにする処理
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = TRUE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = FALSE;
				MoveStoneFlg = FALSE;
			}
		}
		else if (Pocket_cnt == 1) {
			if (MoveStoneFlg2 == TRUE) {
					PlayerPocket = Pocket_cnt;
					P1Pocket[0] = FALSE;
					P1Pocket[1] = TRUE;
					P1Pocket[2] = FALSE;
					P1Pocket[3] = FALSE;
					P1Pocket[4] = FALSE;
					P1Pocket[5] = FALSE;
					MoveStoneFlg2 = FALSE;
			}
		}
		else if (Pocket_cnt == 2) {
			if (MoveStoneFlg3 == TRUE) {
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = TRUE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = FALSE;
				MoveStoneFlg3 = FALSE;
			}
		}
		else if (Pocket_cnt == 3) {
			if (MoveStoneFlg4 == TRUE) {
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = TRUE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = FALSE;
				MoveStoneFlg4 = FALSE;
			}
		}
		else if (Pocket_cnt == 4) {
			if (MoveStoneFlg5 == TRUE) {
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = TRUE;
				P1Pocket[5] = FALSE;
				MoveStoneFlg5 = FALSE;
			}
		}
		else if (Pocket_cnt == 5) {
			if (MoveStoneFlg6 == TRUE) {
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = TRUE;
				MoveStoneFlg6 = FALSE;
			}
		}
	}


	if (P2Turn == 1) {
		if (Pocket_cnt == 0) {
			if (MoveStoneFlg7 == TRUE) {
				// Aボタンで決定した時に選択したポケット以外をFALSEにする処理
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = TRUE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = FALSE;
				MoveStoneFlg7 = FALSE;
			}
		}
		else if (Pocket_cnt == 1) {
			if (MoveStoneFlg8 == TRUE) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = TRUE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = FALSE;
				MoveStoneFlg8 = FALSE;
			}
		}
		else if (Pocket_cnt == 2) {
			if (MoveStoneFlg9 == TRUE) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = TRUE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = FALSE;
				MoveStoneFlg9 = FALSE;
			}
		}
		else if (Pocket_cnt == 3) {
			if (MoveStoneFlg10 == TRUE) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = TRUE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = FALSE;
				MoveStoneFlg10 = FALSE;
			}
		}
		else if (Pocket_cnt == 4) {
			if (MoveStoneFlg11 == TRUE) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = TRUE;
				P2Pocket[5] = FALSE;
				MoveStoneFlg11 = FALSE;
			}
		}
		else if (Pocket_cnt == 5) {
			if (MoveStoneFlg12 == TRUE) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = TRUE;
				MoveStoneFlg12 = FALSE;
			}
		}
	}


	MoveStone();
	WinLose();
	return this;
}

void Mankara::Draw()const
{
	DrawGraph(0, 0, Background, TRUE);
	DrawGraph(30, 30, Board, TRUE);

	// -----------ここから石の初期配置--------------

	// 石（ポケット１）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(340, 440 + i * 20, gStone[i][0].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(370, 280 + i * 20, gStone[i][0].img, TRUE);
	}
	// 石（ポケット２）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(460, 440 + i * 20, gStone[i][1].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(490, 280 + i * 20, gStone[i][1].img, TRUE);
	}
	// 石（ポケット３）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(590, 440 + i * 20, gStone[i][2].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(620, 280 + i * 20, gStone[i][2].img, TRUE);
	}
	// 石（ポケット４）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(715, 440 + i * 20, gStone[i][3].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(745, 280 + i * 20, gStone[i][3].img, TRUE);
	}
	// 石（ポケット５）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(840, 440 + i * 20, gStone[i][4].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(870, 280 + i * 20, gStone[i][4].img, TRUE);
	}
	// 石（ポケット６）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(965, 440 + i * 20, gStone[i][5].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(995, 280 + i * 20, gStone[i][5].img, TRUE);
	}

	//// 2P石の初期配置
	// -----------ここから石の初期配置--------------

	// 石（ポケット１）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(965, 200 + i * 20, gStone[i][0].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(995, 40 + i * 20, gStone[i][0].img, TRUE);
	}
	// 石（ポケット２）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(840, 200 + i * 20, gStone[i][1].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(870, 40 + i * 20, gStone[i][1].img, TRUE);
	}
	// 石（ポケット３）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(715, 200 + i * 20, gStone[i][2].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(745, 40 + i * 20, gStone[i][2].img, TRUE);
	}
	// 石（ポケット４）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(590, 200 + i * 20, gStone[i][3].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(620, 40 + i * 20, gStone[i][3].img, TRUE);
	}
	// 石（ポケット５）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(460, 200 + i * 20, gStone[i][4].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(430, 40 + i * 20, gStone[i][4].img, TRUE);
	}
	// 石（ポケット６）の初期配置
	for (int i = 0; i < 8; i++) {
		DrawGraph(340, 200 + i * 20, gStone[i][5].img, TRUE);
	}
	for (int i = 8; i < 16; i++) {
		DrawGraph(370, 40 + i * 20, gStone[i][5].img, TRUE);
	}


	// 石（ゴール）の初期配置
	//for (int y = 0; y < 1; y++) {
	for (int i = 0; i < 15; i++) {
		DrawGraph(1100 /*+ y * 30*/, 170 + i * 20, gGoal[0][i].img, TRUE);
	}
	// }


	//------------- ここまで-----------------


	// 1Pターン時の ポケット移動
	if (P1Turn == 1) {
		if (Pocket_cnt == 0) {
			/*	DrawGraph(255, 385, P1PocketImg, FALSE);*/
			DrawBox(295, 425, 400, 640, GetColor(0, 0, 255), FALSE);
			DrawBox(296, 426, 401, 641, GetColor(0, 0, 255), FALSE);
			DrawBox(297, 427, 402, 642, GetColor(0, 0, 255), FALSE);
		}
		else if (Pocket_cnt == 1) {
			DrawBox(425, 425, 530, 640, GetColor(0, 0, 255), FALSE);
			DrawBox(426, 426, 531, 641, GetColor(0, 0, 255), FALSE);
			DrawBox(427, 427, 532, 642, GetColor(0, 0, 255), FALSE);

		}
		else if (Pocket_cnt == 2) {
			DrawBox(555, 425, 655, 640, GetColor(0, 0, 255), FALSE);
			DrawBox(556, 426, 656, 641, GetColor(0, 0, 255), FALSE);
			DrawBox(557, 427, 657, 642, GetColor(0, 0, 255), FALSE);

		}
		else if (Pocket_cnt == 3) {
			DrawBox(685, 425, 785, 640, GetColor(0, 0, 255), FALSE);
			DrawBox(686, 426, 786, 641, GetColor(0, 0, 255), FALSE);
			DrawBox(687, 427, 787, 642, GetColor(0, 0, 255), FALSE);

		}
		else if (Pocket_cnt == 4) {
			DrawBox(810, 415, 910, 640, GetColor(0, 0, 255), FALSE);
			DrawBox(811, 416, 911, 641, GetColor(0, 0, 255), FALSE);
			DrawBox(812, 417, 912, 642, GetColor(0, 0, 255), FALSE);

		}
		else if (Pocket_cnt == 5) {
			DrawBox(940, 415, 1040, 640, GetColor(0, 0, 255), FALSE);
			DrawBox(941, 416, 1041, 641, GetColor(0, 0, 255), FALSE);
			DrawBox(942, 417, 1042, 642, GetColor(0, 0, 255), FALSE);
		}

	}


	// 2Pターン時のポケット移動
	if (P2Turn == 1) {
		if (Pocket_cnt == 0) {
			DrawBox(940, 125, 1040, 340, GetColor(255, 0, 0), FALSE);
			DrawBox(941, 126, 1041, 341, GetColor(255, 0, 0), FALSE);
			DrawBox(942, 127, 1042, 342, GetColor(255, 0, 0), FALSE);
		}
		else if (Pocket_cnt == 1) {
			DrawBox(810, 125, 910, 340, GetColor(255, 0, 0), FALSE);
			DrawBox(811, 126, 911, 341, GetColor(255, 0, 0), FALSE);
			DrawBox(812, 127, 912, 342, GetColor(255, 0, 0), FALSE);
		}
		else if (Pocket_cnt == 2) {
			DrawBox(685, 125, 785, 340, GetColor(255, 0, 0), FALSE);
			DrawBox(686, 126, 786, 341, GetColor(255, 0, 0), FALSE);
			DrawBox(687, 127, 787, 342, GetColor(255, 0, 0), FALSE);
		}
		else if (Pocket_cnt == 3) {
			DrawBox(555, 125, 655, 340, GetColor(255, 0, 0), FALSE);
			DrawBox(556, 126, 656, 341, GetColor(255, 0, 0), FALSE);
			DrawBox(557, 127, 657, 342, GetColor(255, 0, 0), FALSE);

		}
		else if (Pocket_cnt == 4) {
		
			DrawBox(415, 125, 525, 340, GetColor(255, 0, 0), FALSE);
			DrawBox(416, 126, 526, 341, GetColor(255, 0, 0), FALSE);
			DrawBox(417, 127, 527, 342, GetColor(255, 0, 0), FALSE);

		}
		else if (Pocket_cnt == 5) {
		
			DrawBox(295, 125, 395, 340, GetColor(255, 0, 0), FALSE);
			DrawBox(296, 126, 396, 341, GetColor(255, 0, 0), FALSE);
			DrawBox(297, 127, 397, 342, GetColor(255, 0, 0), FALSE);
		}

	}

	SetFontSize(24);
	// ゴールに入った石の数
	DrawBox(1110, 100, 1160, 150, GetColor(200, 200, 255), TRUE);
	DrawBox(1110, 100, 1160, 150, GetColor(0, 0, 255), FALSE);
	DrawFormatString(1135, 110, GetColor(0, 0, 0), "%d", P1BigPocket);
	DrawFormatString(1125, 70, GetColor(0, 0, 255), "1P");

	DrawBox(185, 615, 235, 670, GetColor(255, 200, 200), TRUE);
	DrawBox(185, 615, 235, 670, GetColor(255, 0, 0), FALSE);
	DrawFormatString(210, 630, GetColor(255, 0, 0), "%d", P2BigPocket);
	DrawFormatString(200, 570, GetColor(255, 0, 0), "2P");

	

	// ターン切り替え
	if (P2Turn == 1) {
		DrawFormatString(100, 30, GetColor(255, 0, 0), "2P TURN");
	}

	if (P1Turn == 1) {
		DrawFormatString(100, 30, GetColor(0, 0, 255), "1P TURN");
	}
	

	DrawFormatString(340, 625, GetColor(255, 255, 255), "%d", P1StoneSave[0]);
	DrawFormatString(340 + 125 * 1, 625, GetColor(255, 255, 255), "%d", P1StoneSave[1]);
	DrawFormatString(340 + 125 * 2, 625, GetColor(255, 255, 255), "%d", P1StoneSave[2]);
	DrawFormatString(340 + 125 * 3, 625, GetColor(255, 255, 255), "%d", P1StoneSave[3]);
	DrawFormatString(340 + 125 * 4, 625, GetColor(255, 255, 255), "%d", P1StoneSave[4]);
	DrawFormatString(340 + 125 * 5, 625, GetColor(255, 255, 255), "%d", P1StoneSave[5]);


	DrawFormatString(340, 125, GetColor(255, 255, 255), "%d", P2StoneSave[5]);
	DrawFormatString(340 + 125 * 1, 125, GetColor(255, 255, 255), "%d", P2StoneSave[4]);
	DrawFormatString(340 + 125 * 2, 125, GetColor(255, 255, 255), "%d", P2StoneSave[3]);
	DrawFormatString(340 + 125 * 3, 125, GetColor(255, 255, 255), "%d", P2StoneSave[2]);
	DrawFormatString(340 + 125 * 4, 125, GetColor(255, 255, 255), "%d", P2StoneSave[1]);
	DrawFormatString(340 + 125 * 5, 125, GetColor(255, 255, 255), "%d", P2StoneSave[0]);
}

void Mankara::MoveStone()
{
	if (P1Turn == 1 && MoveStoneFlg == FALSE && PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {

		// ポケット0が選ばれた時、
		if (P1Pocket[0] == 1) {
			if (StonePocket[0] > 0) {
				// ポケット０の中身の石の数の分だけ、石を移動させる
				for (int i = 0; i < StonePocket[0]; i++) {
					// 各ポケットの石の数に１ずつ追加する
					StonePocket[i + 1] += 1;
					//石の移動量の分だけ、各ポケットの石を1ずつ描画する
					gStone[P1StoneSave[i + 1]][i + 1].img = TRUE;
					// その後　移動元のポケットの石の描画数を0にする
					gStone[i][0].img = FALSE;
					// 各ポケットのカウントを1ずつ追加する
					P1StoneSave[i + 1] += 1;
					P1StoneSave[0] -= 1;
					// ゴールに入った時(2個以上あった時)
					if (P1StoneSave[0] > 1 && i + 1 == 5) {
						P1BigPocket += 1; // ゴールに1追加する
						i += 1;
					}
				}
			}
			// 移動元のポケットの中身の石の数を０にする
			StonePocket[0] = 0;
		}
		MoveStoneFlg = TRUE;
	}
	else if (P1Turn == 1 && MoveStoneFlg2 == FALSE && PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {

		// ポケット1が選ばれた時、	
		if (P1Pocket[1] == 1) {

			if (StonePocket[1] > 0) {
				// ポケット1の中身の石の数の分だけ、石を移動させる
				for (int i = 0; i < StonePocket[1]; i++) {
					// 各ポケットの石の数に１ずつ追加する
					StonePocket[i + 1] += 1;
					//石の移動量の分だけ、各ポケットの石を1ずつ描画する
					gStone[P1StoneSave[i + 1]][i + 1].img = TRUE;
					// その後　移動元のポケットの石の描画数を0にする
					gStone[i][1].img = FALSE;
					// 各ポケットのカウントを1ずつ追加する
					P1StoneSave[i + 1] += 1;
					P1StoneSave[1] -= 1;
					// ゴールに入った時(2個以上あった時)
					if (P1StoneSave[1] > 1 && i + 1 == 4) {
						P1BigPocket += 1; // ゴールに1追加する
						i += 1;
					}
				}
			}
			// 移動元のポケットの中身の石の数を０にする
			StonePocket[1] = 0;
		}
		MoveStoneFlg2 = TRUE;
	}
	else if (P1Turn == 1 && MoveStoneFlg3 == FALSE && PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {

		// ポケット3が選ばれた時、	
		if (P1Pocket[2] == 1) {
			if (StonePocket[2] > 0) {
				// ポケット０の中身の石の数の分だけ、石を移動させる
				for (int i = 0; i < StonePocket[2]; i++) {
					// 各ポケットの石の数に１ずつ追加する
					StonePocket[i + 1] += 1;
					//石の移動量の分だけ、各ポケットの石を1ずつ描画する
					gStone[P1StoneSave[i + 1]][i + 1].img = TRUE;
					// その後　移動元のポケットの石の描画数を0にする
					gStone[i][2].img = FALSE;
					// 各ポケットのカウントを1ずつ追加する
					P1StoneSave[i + 1] += 1;
					P1StoneSave[2] -= 1;
					// ゴールに入った時(2個以上あった時)
					if (P1StoneSave[2] > 1 && i + 1 == 4) {
						P1BigPocket += 1; // ゴールに1追加する
						i += 1;
					}
				}
			}
			// 移動元のポケットの中身の石の数を０にする
			StonePocket[2] = 0;
		}
		MoveStoneFlg3 = TRUE;
	}
	else if (P1Turn == 1 && MoveStoneFlg4 == FALSE && PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {

		// ポケット3が選ばれた時、	
		if (P1Pocket[3] == 1) {
			if (StonePocket[3] > 0) {
				// ポケット０の中身の石の数の分だけ、石を移動させる
				for (int i = 0; i < StonePocket[3]; i++) {
					// 各ポケットの石の数に１ずつ追加する
					StonePocket[i + 1] += 1;
					//石の移動量の分だけ、各ポケットの石を1ずつ描画する
					gStone[P1StoneSave[i + 1]][i + 1].img = TRUE;
					// その後　移動元のポケットの石の描画数を0にする
					gStone[i][3].img = FALSE;
					// 各ポケットのカウントを1ずつ追加する
					P1StoneSave[i + 1] += 1;
					P1StoneSave[3] -= 1;
					// ゴールに入った時(2個以上あった時)
					if (P1StoneSave[3] > 1 && i + 1 == 3) {
						P1BigPocket += 1; // ゴールに1追加する
						i += 1;
					}
				}
			}
			// 移動元のポケットの中身の石の数を０にする
			StonePocket[3] = 0;
		}
		MoveStoneFlg4 = TRUE;
	}
	else if (P1Turn == 1 && MoveStoneFlg5 == FALSE && PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		// ポケット4が選ばれた時、
		if (P1Pocket[4] == 1) {
			if (StonePocket[4] > 0) {
				// ポケット０の中身の石の数の分だけ、石を移動させる
				for (int i = 0; i < StonePocket[4]; i++) {
					// 各ポケットの石の数に１ずつ追加する
					StonePocket[i + 1] += 1;
					//石の移動量の分だけ、各ポケットの石を1ずつ描画する
					gStone[P1StoneSave[i + 1]][i + 1].img = TRUE;
					// その後　移動元のポケットの石の描画数を0にする
					gStone[i][4].img = FALSE;
					// 各ポケットのカウントを1ずつ追加する
					P1StoneSave[i + 1] += 1;
					P1StoneSave[4] -= 1;
					// ゴールに入った時(2個以上あった時)
					if (P1StoneSave[4] > 1 && i + 1 == 2) {
						P1BigPocket += 1; // ゴールに1追加する
						i += 1;
					}
				}
			}
		 // 移動元のポケットの中身の石の数を０にする
			StonePocket[4] = 0;
		}
		MoveStoneFlg5 = TRUE;
	}
	else if (P1Turn == 1 && MoveStoneFlg6 == FALSE && PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		// ポケット4が選ばれた時、
		if (P1Pocket[5] == 1) {
			if (StonePocket[5] > 0) {
				// ポケット０の中身の石の数の分だけ、石を移動させる
				for (int i = 0; i < StonePocket[5]; i++) {
					// 各ポケットの石の数に１ずつ追加する
					StonePocket[i + 1] += 1;
					//石の移動量の分だけ、各ポケットの石を1ずつ描画する
					gStone[P1StoneSave[i + 1]][i + 1].img = TRUE;
					// その後　移動元のポケットの石の描画数を0にする
					gStone[i][5].img = FALSE;
					// 各ポケットのカウントを1ずつ追加する
					P1StoneSave[i + 1] += 1;
					P1StoneSave[5] -= 1;
					// ゴールに入った時(2個以上あった時)
					if (P1StoneSave[5] > 1 && i + 1 == 1) {
						P1BigPocket += 1; // ゴールに1追加する
						i += 1;
					}
				}
			}
			// 移動元のポケットの中身の石の数を０にする
			StonePocket[5] = 0;
		}
		MoveStoneFlg6 = TRUE;
	}
	else if (P2Turn == 1 && MoveStoneFlg7 == FALSE && PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {

		// ポケット0が選ばれた時、
		if (P2Pocket[0] == 1) {
			if (StonePocket[7] > 0) {
				// ポケット０の中身の石の数の分だけ、石を移動させる
				for (int i = 0; i < StonePocket[7]; i++) {
					// 各ポケットの石の数に１ずつ追加する
					StonePocket[i + 1] += 1;
					//石の移動量の分だけ、各ポケットの石を1ずつ描画する
					gStone2[P2StoneSave[i + 1]][i + 1].img = TRUE;
					// その後　移動元のポケットの石の描画数を0にする
					gStone2[i][0].img = FALSE;
					// 各ポケットのカウントを1ずつ追加する
					P2StoneSave[i + 1] += 1;
					P2StoneSave[0] -= 1;
					// ゴールに入った時(2個以上あった時)
					if (P2StoneSave[0] > 1 && i + 1 == 5) {
						P2BigPocket += 1; // ゴールに1追加する
						i += 1;
					}
				}
			}
			// 移動元のポケットの中身の石の数を０にする
			StonePocket[7] = 0;
		}
		MoveStoneFlg7 = TRUE;
	}
	else if (P2Turn == 1 && MoveStoneFlg8 == FALSE && PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {

		// ポケット1が選ばれた時、	
		if (P2Pocket[1] == 1) {

			if (StonePocket[8] > 0) {
				// ポケット1の中身の石の数の分だけ、石を移動させる
				for (int i = 0; i < StonePocket[8]; i++) {
					// 各ポケットの石の数に１ずつ追加する
					StonePocket[i + 1] += 1;
					//石の移動量の分だけ、各ポケットの石を1ずつ描画する
					gStone2[P2StoneSave[i + 1]][i + 1].img = TRUE;
					// その後　移動元のポケットの石の描画数を0にする
					gStone2[i][1].img = FALSE;
					// 各ポケットのカウントを1ずつ追加する
					P2StoneSave[i + 1] += 1;
					P2StoneSave[1] -= 1;
					// ゴールに入った時(2個以上あった時)
					if (P2StoneSave[1] > 1 && i + 1 == 4) {
						P2BigPocket += 1; // ゴールに1追加する
						i += 1;
					}
				}
			}
			// 移動元のポケットの中身の石の数を０にする
			StonePocket[8] = 0;
		}
		MoveStoneFlg8 = TRUE;
	}
	else if (P2Turn == 1 && MoveStoneFlg9 == FALSE && PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {

		// ポケット3が選ばれた時、	
		if (P2Pocket[2] == 1) {
			if (StonePocket[9] > 0) {
				// ポケット０の中身の石の数の分だけ、石を移動させる
				for (int i = 0; i < StonePocket[9]; i++) {
					// 各ポケットの石の数に１ずつ追加する
					StonePocket[i + 1] += 1;
					//石の移動量の分だけ、各ポケットの石を1ずつ描画する
					gStone2[P2StoneSave[i + 1]][i + 1].img = TRUE;
					// その後　移動元のポケットの石の描画数を0にする
					gStone2[i][2].img = FALSE;
					// 各ポケットのカウントを1ずつ追加する
					P2StoneSave[i + 1] += 1;
					P2StoneSave[2] -= 1;
					// ゴールに入った時(2個以上あった時)
					if (P2StoneSave[2] > 1 && i + 1 == 4) {
						P2BigPocket += 1; // ゴールに1追加する
						i += 1;
					}
				}
			}
			// 移動元のポケットの中身の石の数を０にする
			StonePocket[9] = 0;
		}
		MoveStoneFlg9 = TRUE;

	}
	else if (P2Turn == 1 && MoveStoneFlg10 == FALSE && PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {

		// ポケット3が選ばれた時、	
		if (P2Pocket[3] == 1) {
			if (StonePocket[10] > 0) {
				// ポケット０の中身の石の数の分だけ、石を移動させる
				for (int i = 0; i < StonePocket[10]; i++) {
					// 各ポケットの石の数に１ずつ追加する
					StonePocket[i + 1] += 1;
					//石の移動量の分だけ、各ポケットの石を1ずつ描画する
					gStone2[P2StoneSave[i + 1]][i + 1].img = TRUE;
					// その後　移動元のポケットの石の描画数を0にする
					gStone2[i][3].img = FALSE;
					// 各ポケットのカウントを1ずつ追加する
					P2StoneSave[i + 1] += 1;
					P2StoneSave[3] -= 1;
					// ゴールに入った時(2個以上あった時)
					if (P2StoneSave[3] > 1 && i + 1 == 3) {
						P2BigPocket += 1; // ゴールに1追加する
						i += 1;
					}
				}
			}
			// 移動元のポケットの中身の石の数を０にする
			StonePocket[10] = 0;
		}
		MoveStoneFlg10 = TRUE;
	}
	else if (P2Turn == 1 && MoveStoneFlg11 == FALSE && PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		// ポケット4が選ばれた時、
		if (P2Pocket[4] == 1) {
			if (StonePocket[11] > 0) {
				// ポケット０の中身の石の数の分だけ、石を移動させる
				for (int i = 0; i < StonePocket[11]; i++) {
					// 各ポケットの石の数に１ずつ追加する
					StonePocket[i + 1] += 1;
					//石の移動量の分だけ、各ポケットの石を1ずつ描画する
					gStone2[P2StoneSave[i + 1]][i + 1].img = TRUE;
					// その後　移動元のポケットの石の描画数を0にする
					gStone2[i][4].img = FALSE;
					// 各ポケットのカウントを1ずつ追加する
					P2StoneSave[i + 1] += 1;
					P2StoneSave[4] -= 1;
					// ゴールに入った時(2個以上あった時)
					if (P2StoneSave[4] > 1 && i + 1 == 2) {
						P2BigPocket += 1; // ゴールに1追加する
						i += 1;
					}
				}
			}
		 // 移動元のポケットの中身の石の数を０にする
			StonePocket[11] = 0;
		}
		MoveStoneFlg11 = TRUE;
	}
	else if (P2Turn == 1 && MoveStoneFlg12 == FALSE && PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		// ポケット4が選ばれた時、
		if (P2Pocket[5] == 1) {
			if (StonePocket[12] > 0) {
				// ポケット０の中身の石の数の分だけ、石を移動させる
				for (int i = 0; i < StonePocket[12]; i++) {
					// 各ポケットの石の数に１ずつ追加する
					StonePocket[i + 1] += 1;
					//石の移動量の分だけ、各ポケットの石を1ずつ描画する
					gStone2[P2StoneSave[i + 1]][i + 1].img = TRUE;
					// その後　移動元のポケットの石の描画数を0にする
					gStone2[i][5].img = FALSE;
					// 各ポケットのカウントを1ずつ追加する
					P2StoneSave[i + 1] += 1;
					P2StoneSave[5] -= 1;
					// ゴールに入った時(2個以上あった時)
					if (P2StoneSave[5] > 1 && i + 1 == 1) {
						P2BigPocket += 1; // ゴールに1追加する
						i += 1;
					}
				}
			}
			// 移動元のポケットの中身の石の数を０にする
			StonePocket[12] = 0;
		}
		MoveStoneFlg12 = TRUE;
	}
}

void Mankara::WinLose()
{
	if (P1BigPocket >= 25) {
		DrawFormatString(500, 500, GetColor(255, 255, 255), "1P  WIN");
		DrawFormatString(500, 600, GetColor(255, 255, 255), "2P  LOSE");
	}
		
	if (P2BigPocket >= 25) {
		DrawFormatString(500, 500, GetColor(255, 255, 255), "2P  WIN");
		DrawFormatString(500, 600, GetColor(255, 255, 255), "1P  LOSE");

	}
}
