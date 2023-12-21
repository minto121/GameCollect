#include "Mankara.h"
#include"DxLib.h"
#include"PadInput.h"
#include"GameSelect.h"
Mankara::Mankara()
{
	//StoneImg[6] = LoadDivGraph("images/Mancala/MancalaStone.png", 6, 6, 1, 32, 32, StoneImg);
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

	PocketEnter = 0;
	PocketEnter2 = 0;


	


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

	//// 石の画像処理(ポケット)
	//for (int i = 0; i < 6; i++) {
	//	for (int y = 0; y < 6; y++) {
	//		gStone[y][i].img = StoneImg[y], P1Pocket[i];//ポケット１
	//		gStone2[y][i].img = StoneImg[y],P2Pocket[i] ;//ポケット１
	//	}
	//}

	//// 石の画像処理(ゴール)
	//for (int i = 0; i < 30; i++) {
	//	for (int y = 0; y < 6; y++) {
	//		gGoal[y][i].img = StoneImg[y];//ポケット１
	//		
	//	}
	//}


	//for (int i = 0; i < 12; i++) {
	//	StonePocket[i] = InitialStone; // 1P（[1]）のポケット（[6]）の中にStone_cntの初期値（4）を格納
	//}

	for (int pocket = 0; pocket < 6;) {
		P1StoneSave[pocket] = 4;
		P2StoneSave[pocket] = 4;
		pocket++;
	}

	/*for (int i = 4; i < 16; i++) {
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
		
	}*/

}

AbstractScene* Mankara::Update()
{
	// 相手のターンはプレイヤーは動かない
	if (P2Turn == 1) {
		P1Turn = 0;
	}

	

	// プレイヤーのターンは相手は動かない
	if (P1Turn == 1) {
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
			
				// Aボタンで決定した時に選択したポケット以外をFALSEにする処理
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = TRUE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = FALSE;
		}
		else if (Pocket_cnt == 1) {
	
					PlayerPocket = Pocket_cnt;
					P1Pocket[0] = FALSE;
					P1Pocket[1] = TRUE;
					P1Pocket[2] = FALSE;
					P1Pocket[3] = FALSE;
					P1Pocket[4] = FALSE;
					P1Pocket[5] = FALSE;
			
		}
		else if (Pocket_cnt == 2) {
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = TRUE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = FALSE;
			
		}
		else if (Pocket_cnt == 3) {
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = TRUE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = FALSE;
			
		}
		else if (Pocket_cnt == 4) {
			
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = TRUE;
				P1Pocket[5] = FALSE;
			
		}
		else if (Pocket_cnt == 5) {
				PlayerPocket = Pocket_cnt;
				P1Pocket[0] = FALSE;
				P1Pocket[1] = FALSE;
				P1Pocket[2] = FALSE;
				P1Pocket[3] = FALSE;
				P1Pocket[4] = FALSE;
				P1Pocket[5] = TRUE;
		}
	}


	if (P2Turn == 1) {
		if (Pocket_cnt == 0) {
				// Aボタンで決定した時に選択したポケット以外をFALSEにする処理
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = TRUE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = FALSE;
		}
		else if (Pocket_cnt == 1) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = TRUE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = FALSE;
		}
		else if (Pocket_cnt == 2) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = TRUE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = FALSE;
		}
		else if (Pocket_cnt == 3) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = TRUE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = FALSE;			
		}
		else if (Pocket_cnt == 4) {
			
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = TRUE;
				P2Pocket[5] = FALSE;		
		}
		else if (Pocket_cnt == 5) {
				PartnerPocket = Pocket_cnt;
				P2Pocket[0] = FALSE;
				P2Pocket[1] = FALSE;
				P2Pocket[2] = FALSE;
				P2Pocket[3] = FALSE;
				P2Pocket[4] = FALSE;
				P2Pocket[5] = TRUE;
		}
	}

	if (P1StoneSave[0] == 0&&P1StoneSave[1] == 0&&P1StoneSave[2] == 0&&P1StoneSave[3] == 0&&P1StoneSave[4] == 0&&P1StoneSave[5] == 0) {
		P1Turn = 0;
		P2Turn = 0;

	}
	if (P2StoneSave[0] == 0&&P2StoneSave[1] == 0&&P2StoneSave[2] == 0&&P2StoneSave[3] == 0&&P2StoneSave[4] == 0&&P2StoneSave[5] == 0) {
		P1Turn = 0;
		P2Turn = 0;
	}

	MoveStone();

	return this;
}

void Mankara::Draw()const
{
	DrawGraph(0, 0, Background, TRUE);
	DrawGraph(30, 30, Board, TRUE);

	//// -----------ここから石の初期配置--------------

	//// 石（ポケット１）の初期配置
	//for (int i = 0; i < 8; i++) {
	//	DrawGraph(340, 440 + i * 20, gStone[i][0].img, TRUE);
	//}
	//for (int i = 8; i < 16; i++) {
	//	DrawGraph(370, 280 + i * 20, gStone[i][0].img, TRUE);
	//}
	//// 石（ポケット２）の初期配置
	//for (int i = 0; i < 8; i++) {
	//	DrawGraph(460, 440 + i * 20, gStone[i][1].img, TRUE);
	//}
	//for (int i = 8; i < 16; i++) {
	//	DrawGraph(490, 280 + i * 20, gStone[i][1].img, TRUE);
	//}
	//// 石（ポケット３）の初期配置
	//for (int i = 0; i < 8; i++) {
	//	DrawGraph(590, 440 + i * 20, gStone[i][2].img, TRUE);
	//}
	//for (int i = 8; i < 16; i++) {
	//	DrawGraph(620, 280 + i * 20, gStone[i][2].img, TRUE);
	//}
	//// 石（ポケット４）の初期配置
	//for (int i = 0; i < 8; i++) {
	//	DrawGraph(715, 440 + i * 20, gStone[i][3].img, TRUE);
	//}
	//for (int i = 8; i < 16; i++) {
	//	DrawGraph(745, 280 + i * 20, gStone[i][3].img, TRUE);
	//}
	//// 石（ポケット５）の初期配置
	//for (int i = 0; i < 8; i++) {
	//	DrawGraph(840, 440 + i * 20, gStone[i][4].img, TRUE);
	//}
	//for (int i = 8; i < 16; i++) {
	//	DrawGraph(870, 280 + i * 20, gStone[i][4].img, TRUE);
	//}
	//// 石（ポケット６）の初期配置
	//for (int i = 0; i < 8; i++) {
	//	DrawGraph(965, 440 + i * 20, gStone[i][5].img, TRUE);
	//}
	//for (int i = 8; i < 16; i++) {
	//	DrawGraph(995, 280 + i * 20, gStone[i][5].img, TRUE);
	//}

	////// 2P石の初期配置
	//// -----------ここから石の初期配置--------------

	//// 石（ポケット１）の初期配置
	//for (int i = 0; i < 8; i++) {
	//	DrawGraph(965, 200 + i * 20, gStone[i][0].img, TRUE);
	//}
	//for (int i = 8; i < 16; i++) {
	//	DrawGraph(995, 40 + i * 20, gStone[i][0].img, TRUE);
	//}
	//// 石（ポケット２）の初期配置
	//for (int i = 0; i < 8; i++) {
	//	DrawGraph(840, 200 + i * 20, gStone[i][1].img, TRUE);
	//}
	//for (int i = 8; i < 16; i++) {
	//	DrawGraph(870, 40 + i * 20, gStone[i][1].img, TRUE);
	//}
	//// 石（ポケット３）の初期配置
	//for (int i = 0; i < 8; i++) {
	//	DrawGraph(715, 200 + i * 20, gStone[i][2].img, TRUE);
	//}
	//for (int i = 8; i < 16; i++) {
	//	DrawGraph(745, 40 + i * 20, gStone[i][2].img, TRUE);
	//}
	//// 石（ポケット４）の初期配置
	//for (int i = 0; i < 8; i++) {
	//	DrawGraph(590, 200 + i * 20, gStone[i][3].img, TRUE);
	//}
	//for (int i = 8; i < 16; i++) {
	//	DrawGraph(620, 40 + i * 20, gStone[i][3].img, TRUE);
	//}
	//// 石（ポケット５）の初期配置
	//for (int i = 0; i < 8; i++) {
	//	DrawGraph(460, 200 + i * 20, gStone[i][4].img, TRUE);
	//}
	//for (int i = 8; i < 16; i++) {
	//	DrawGraph(430, 40 + i * 20, gStone[i][4].img, TRUE);
	//}
	//// 石（ポケット６）の初期配置
	//for (int i = 0; i < 8; i++) {
	//	DrawGraph(340, 200 + i * 20, gStone[i][5].img, TRUE);
	//}
	//for (int i = 8; i < 16; i++) {
	//	DrawGraph(370, 40 + i * 20, gStone[i][5].img, TRUE);
	//}


	//// 石（ゴール）の初期配置
	////for (int y = 0; y < 1; y++) {
	//for (int i = 0; i < 15; i++) {
	//	DrawGraph(1100 /*+ y * 30*/, 170 + i * 20, gGoal[0][i].img, TRUE);
	//}
	//// }


	//------------- ここまで-----------------


	// 1Pターン時の ポケット移動
	if (P1Turn == 1) {
		if (Pocket_cnt == 0) {
			/*	DrawGraph(255, 385, P1PocketImg, FALSE);*/
			DrawBox(255, 385, 360, 600, GetColor(0, 0, 255), FALSE);
			DrawBox(256, 386, 361, 601, GetColor(0, 0, 255), FALSE);
			DrawBox(257, 387, 362, 602, GetColor(0, 0, 255), FALSE);
		}
		else if (Pocket_cnt == 1) {
			DrawBox(385, 385, 490, 600, GetColor(0, 0, 255), FALSE);
			DrawBox(386, 386, 491, 601, GetColor(0, 0, 255), FALSE);
			DrawBox(387, 387, 492, 602, GetColor(0, 0, 255), FALSE);

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
			DrawBox(770, 85, 870, 300, GetColor(255, 0, 0), FALSE);
			DrawBox(771, 86, 871, 301, GetColor(255, 0, 0), FALSE);
			DrawBox(772, 87, 872, 302, GetColor(255, 0, 0), FALSE);
		}
		else if (Pocket_cnt == 2) {
			DrawBox(645, 85, 745, 300, GetColor(255, 0, 0), FALSE);
			DrawBox(646, 86, 746, 301, GetColor(255, 0, 0), FALSE);
			DrawBox(647, 87, 747, 302, GetColor(255, 0, 0), FALSE);
		}
		else if (Pocket_cnt == 3) {
			DrawBox(515, 85, 615, 300, GetColor(255, 0, 0), FALSE);
			DrawBox(516, 86, 616, 301, GetColor(255, 0, 0), FALSE);
			DrawBox(517, 87, 617, 302, GetColor(255, 0, 0), FALSE);

		}
		else if (Pocket_cnt == 4) {
		
			DrawBox(375, 85, 485, 300, GetColor(255, 0, 0), FALSE);
			DrawBox(376, 86, 486, 301, GetColor(255, 0, 0), FALSE);
			DrawBox(377, 87, 487, 302, GetColor(255, 0, 0), FALSE);

		}
		else if (Pocket_cnt == 5) {
		
			DrawBox(255, 85, 355, 300, GetColor(255, 0, 0), FALSE);
			DrawBox(256, 86, 356, 301, GetColor(255, 0, 0), FALSE);
			DrawBox(257, 87, 357, 302, GetColor(255, 0, 0), FALSE);
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
	

	DrawFormatString(260, 585, GetColor(255, 255, 255), "%d", P1StoneSave[0]);
	DrawFormatString(260 + 125 * 1, 585, GetColor(255, 255, 255), "%d", P1StoneSave[1]);
	DrawFormatString(260 + 125 * 2, 585, GetColor(255, 255, 255), "%d", P1StoneSave[2]);
	DrawFormatString(260 + 125 * 3, 585, GetColor(255, 255, 255), "%d", P1StoneSave[3]);
	DrawFormatString(260 + 125 * 4, 585, GetColor(255, 255, 255), "%d", P1StoneSave[4]);
	DrawFormatString(260 + 125 * 5, 585, GetColor(255, 255, 255), "%d", P1StoneSave[5]);


	DrawFormatString(300, 85, GetColor(255, 255, 255), "%d", P2StoneSave[5]);
	DrawFormatString(300 + 125 * 1, 85, GetColor(255, 255, 255), "%d", P2StoneSave[4]);
	DrawFormatString(300 + 125 * 2, 85, GetColor(255, 255, 255), "%d", P2StoneSave[3]);
	DrawFormatString(300 + 125 * 3, 85, GetColor(255, 255, 255), "%d", P2StoneSave[2]);
	DrawFormatString(300 + 125 * 4, 85, GetColor(255, 255, 255), "%d", P2StoneSave[1]);
	DrawFormatString(300 + 125 * 5, 85, GetColor(255, 255, 255), "%d", P2StoneSave[0]);


	// 勝敗条件（マンカラカラハ）
	if (P1StoneSave[0] ==0&&P1StoneSave[1] ==0&&P1StoneSave[2] ==0&&P1StoneSave[3] ==0&&P1StoneSave[4] ==0&&P1StoneSave[5] ==0) {
		DrawBox(480, 250, 700, 400, GetColor(255, 255, 255), TRUE);
		
		DrawFormatString(500, 300, GetColor(0, 0, 255), "1P  WIN");
		DrawFormatString(500, 350, GetColor(0, 0, 0), "ESC：ゲーム終了");
	}

	if (P2StoneSave[0] ==0 && P2StoneSave[1] == 0 && P2StoneSave[2] == 0 && P2StoneSave[3] == 0 && P2StoneSave[4] == 0 && P2StoneSave[5] == 0) {
		DrawBox(480, 250, 700, 400, GetColor(255, 255, 255), TRUE);
		DrawFormatString(500, 300, GetColor(255, 0, 0), "2P  WIN");
		DrawFormatString(500, 350, GetColor(0, 0, 0), "ESC：ゲーム終了");
	}
}

void Mankara::MoveStone()
{

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_X)) {
		P1Turn = 1;
	}

	if (P1Turn &&PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		PocketEnter = TRUE;
	}
	if (P2Turn == 1&&PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		PocketEnter2 = TRUE;
	}



	if (P1Turn == 1 &&PocketEnter ==TRUE&& P1Pocket[0] == TRUE) {

			// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
			if (P1StoneSave[0] >= 6) {
				P1BigPocket += 1;
			}
			if (P1StoneSave[0] >= 6) {
				for (int i = 0; i < P1StoneSave[0] - 6; i++) {
					P2StoneSave[i] += 1;
				}
			}
			// 1番目のポケットの中の数になるまで、iを足し続ける
			for (int i = 0; i < P1StoneSave[0]; i++) {
				
				P1StoneSave[i] += 1;
			}
			// 移動が終わったので、石の数を０にする。
			P1StoneSave[0] = 0;
		PocketEnter = FALSE;
		P1Turn = 0;
		P2Turn = 1;
		
	}
	else if (P1Turn == 1 && PocketEnter == TRUE&& P1Pocket[1] == 1) {
			// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
			if (P1StoneSave[1] >= 5) {
				P1BigPocket += 1;
			}
			if (P1StoneSave[1] >= 5) {
				for (int i = 0; i < P1StoneSave[1] - 5; i++) {
					P2StoneSave[i] += 1;
				}
			}
			// 1番目のポケットの中の数になるまで、iを足し続ける
			for (int i = 1; i < P1StoneSave[1] + 1; i++) {
				
				P1StoneSave[i] += 1;
			}
			// 移動が終わったので、石の数を０にする。
			P1StoneSave[1] = 0;

		PocketEnter = FALSE;
		P1Turn = 0;
		P2Turn = 1;

	}
	else if (P1Turn == 1 &&PocketEnter == TRUE&& P1Pocket[2] == 1) {

		
			// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
			if (P1StoneSave[2] >= 4) {
				P1BigPocket += 1;
			}
			if (P1StoneSave[2] >= 4) {
				for (int i = 0; i < P1StoneSave[2] - 4; i++) {
					P2StoneSave[i] += 1;
				}
			}
			// 1番目のポケットの中の数になるまで、iを足し続ける
			for (int i = 2; i < P1StoneSave[2] + 2; i++) {
				
				P1StoneSave[i] += 1;
			}
			// 移動が終わったので、石の数を０にする。
			P1StoneSave[2] = 0;
		PocketEnter = FALSE;
		P1Turn = 0;
		P2Turn = 1;
	}
	else if (P1Turn == 1  && PocketEnter == TRUE&& P1Pocket[3] == 1) {
			// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
			if (P1StoneSave[3] >= 3) {
				P1BigPocket += 1;
			}
			if (P1StoneSave[3] >= 3) {
				for (int i = 0; i < P1StoneSave[3] - 3; i++) {
					P2StoneSave[i] += 1;
				}
			}
			// 1番目のポケットの中の数になるまで、iを足し続ける
			for (int i = 3; i < P1StoneSave[3] + 3; i++) {
				
				P1StoneSave[i] += 1;
			}
			// 移動が終わったので、石の数を０にする。
			P1StoneSave[3] = 0;
		PocketEnter = FALSE;
		P1Turn = 0;
		P2Turn = 1;
	}
	else if (P1Turn == 1  && PocketEnter == TRUE&& P1Pocket[4] == 1) {
		
			// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
			if (P1StoneSave[4] >= 2) {
				P1BigPocket += 1;
			}
			if (P1StoneSave[4] >= 2) {
				for (int i = 0; i < P1StoneSave[4] - 2; i++) {
					P2StoneSave[i] += 1;
				}
			}
			// 1番目のポケットの中の数になるまで、iを足し続ける
			for (int i = 4; i < P1StoneSave[4] + 4; i++) {
				
				P1StoneSave[i] += 1;
			}
			// 移動が終わったので、石の数を０にする。
			P1StoneSave[4] = 0;

		PocketEnter = FALSE;
		P1Turn = 0;
		P2Turn = 1;
	}
	else if (P1Turn == 1 && PocketEnter == TRUE&& P1Pocket[5] == 1) {
			// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
			if (P1StoneSave[5] >= 6) {
				P1BigPocket += 1;
			}
			if (P1StoneSave[5] >= 1) {
				for (int i = 0; i < P1StoneSave[5] - 1; i++) {
					P2StoneSave[i] += 1;
				}
			}
			// 1番目のポケットの中の数になるまで、iを足し続ける
			for (int i = 5; i < P1StoneSave[5] + 5; i++) {
				
				P1StoneSave[i] += 1;
			}
			// 移動が終わったので、石の数を０にする。
			P1StoneSave[5] = 0;

		PocketEnter = FALSE;
		P1Turn = 0;
		P2Turn = 1;
	}




	else if (P2Turn == 1 &&  PocketEnter2 == TRUE&& P2Pocket[0] == TRUE) {
			// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
			if (P2StoneSave[0] >= 6) {
				P2BigPocket += 1;
			}
			if (P2StoneSave[0] >= 6) {
				for (int i = 0; i < P2StoneSave[0] - 6; i++) {
					P1StoneSave[i] += 1;
				}
			}
			// 1番目のポケットの中の数になるまで、iを足し続ける
			for (int i = 0; i < P2StoneSave[0]; i++) {
				
				P2StoneSave[i] += 1;
				
			}
			
			// 移動が終わったので、石の数を０にする。
				P2StoneSave[0] = 0;
		PocketEnter2 = FALSE;
			P1Turn = 1;
			P2Turn = 0;
	}
	else if (P2Turn == 1  && PocketEnter2 == TRUE&& P2Pocket[1] == TRUE) {
			// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
			if (P2StoneSave[1] >= 5) {
				P2BigPocket += 1;
			}
			if (P2StoneSave[1] >= 5) {
				for (int i = 0; i < P2StoneSave[1] - 5; i++) {
					P1StoneSave[i] += 1;
				}
			}
			// 1番目のポケットの中の数になるまで、iを足し続ける
			for (int i = 1; i < P2StoneSave[1] + 1; i++) {	
				
				P2StoneSave[i] += 1;
				
			}
			// 移動が終わったので、石の数を０にする。
				P2StoneSave[1] = 0;
		PocketEnter2 = FALSE;
			P1Turn = 1;
			P2Turn = 0;
	}
	else if (P2Turn == 1  && PocketEnter2 == TRUE&& P2Pocket[2] == TRUE) {
			// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
			if (P2StoneSave[2] >= 4) {
				P2BigPocket += 1;
			}
			if (P2StoneSave[2] >= 4) {
				for (int i = 0; i < P2StoneSave[2] - 4; i++) {
					P1StoneSave[i] += 1;
				}
			}
			// 1番目のポケットの中の数になるまで、iを足し続ける
			for (int i = 2; i < P2StoneSave[2] + 2; i++) {

				P2StoneSave[i] += 1;

			}
			// 移動が終わったので、石の数を０にする。
				P2StoneSave[2] = 0;
			PocketEnter2 = FALSE;
			P1Turn = 1;
			P2Turn = 0;
	}
	else if (P2Turn == 1 && PocketEnter2== TRUE&& P2Pocket[3] == TRUE) {
			// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
			if (P2StoneSave[3] >= 3) {
				P2BigPocket += 1;
			}

			if (P2StoneSave[3] >= 3) {
				for (int i = 0; i < P2StoneSave[3] - 3; i++) {
					P1StoneSave[i] += 1;
				}
			}
			// 1番目のポケットの中の数になるまで、iを足し続ける
			for (int i = 3; i < P2StoneSave[3] + 3; i++) {

					P2StoneSave[i] += 1;

			}
			// 移動が終わったので、石の数を０にする。
			P2StoneSave[3] = 0;
		PocketEnter2 = FALSE; 
			P1Turn = 1;
			P2Turn = 0;
	}
	else if (P2Turn == 1 && PocketEnter2 == TRUE&& P2Pocket[4] == TRUE) {
			// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
			if (P2StoneSave[4] >= 2) {
				P2BigPocket += 1;
			}
			if (P2StoneSave[4] >= 2) {
				for (int y = 0; y < P2StoneSave[1] - 2; y++) {
					P1StoneSave[y] += 1;
				}
			}
			// 1番目のポケットの中の数になるまで、iを足し続ける
			for (int i = 4; i < P2StoneSave[4] + 4; i++) {	
				
				P2StoneSave[i] += 1;
				
			}
			// 移動が終わったので、石の数を０にする。
				P2StoneSave[4] = 0;
		
		PocketEnter2 = FALSE;
			P1Turn = 1;
			P2Turn = 0;
	}
	else if (P2Turn == 1  && PocketEnter2 == TRUE&& P2Pocket[5] == TRUE) {
	
			// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
			if (P2StoneSave[5] >= 1) {
				P2BigPocket += 1;
			}
			if (P2StoneSave[5] >= 1) {
				for (int y = 0; y < P2StoneSave[5] - 1; y++) {
					P1StoneSave[y] += 1;
				}
			}
			// 1番目のポケットの中の数になるまで、iを足し続ける
			for (int i = 5; i < P2StoneSave[5] + 5; i++) {
				
				P2StoneSave[i] += 1;
			
			}
			// 移動が終わったので、石の数を０にする。		
			P2StoneSave[5] = 0;		

		PocketEnter2 = FALSE;
			P1Turn = 1;
			P2Turn = 0;
	}


}

