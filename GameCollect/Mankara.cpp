#include "Mankara.h"
#include"DxLib.h"
#include"PadInput.h"
Mankara::Mankara()
{
	StoneImg[6] = LoadDivGraph("images/Mancala/MancalaStone.png", 6, 6, 1, 32, 32, StoneImg);
	Board = LoadGraph("images/mancala/MancalaBoard.png");
	Background = LoadGraph("images/Mancala/BackGround02.png");
	P1BigPocket= 0;
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

	// 石の画像処理
	for (int i = 0; i < 16; i++) {
		for (int y = 0; y < 6; y++) {
			gStone[y][i].img = StoneImg[y];
			gStone2[y][i].img = StoneImg[y];
		}
	}

	
	//// 石の画像処理
	//for (int i = 0; i < 48; i++) {
	//	for (int y = 0; y < 6; y++) {
	//		BigPocket[y][i] = StoneImg[y];
	//	}
	//}
	//for (int i = 0; i < 7; i++) {
	//	StonePocket[0][i] = InitialStone; // 1P（[1]）のポケット（[6]）の中にStone_cntの初期値（4）を格納
	//	StonePocket[1][i] = InitialStone; // 2P（[1]）のポケット（[6]）の中にStone_cntの初期値（4）を格納
	//}

	/*for (int Pocket = 0; Pocket < 7;) {
		for (int i = 0; i < 4; i++) {
			P1StoneSave[Pocket][i] = gStone[Pocket][i].img;
			P2StoneSave[Pocket][i] = gStone[Pocket][i].img;
		}
		Pocket++;
	}*/

	for (int i = 0; i < 6; i++) {
		for (int y = 4; y < 16; y++) {
			gStone[y][i].img = FALSE;
			gStone2[y][i].img = FALSE;
		}
	}
}

 AbstractScene* Mankara:: Update()
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
	DrawGraph(30,30,Board,TRUE);

	// -----------ここから石の初期配置--------------

	// 石（ポケット１）の初期配置
	for (int i = 0; i < 16; i++) {
		DrawGraph(300, 400 + i * 15, gStone[i][0].img, TRUE);
		if (i >= 10) {
			DrawGraph(325, 400 + i * 15, gStone[i][0].img, TRUE);
		}
	}
	// 石（ポケット２）の初期配置
	for (int i = 0; i < 16; i++) {
		DrawGraph(425, 400 + i * 15, gStone[i][1].img, TRUE);
		if (i >= 10) {
			DrawGraph(450, 400 + i * 15, gStone[i][1].img, TRUE);
		}
	}
	// 石（ポケット３）の初期配置
	for (int i = 0; i < 16; i++) {
		DrawGraph(550, 400 + i * 15, gStone[i][2].img, TRUE);
		if (i >= 10) {
			DrawGraph(575, 400 + i * 15, gStone[i][2].img, TRUE);
		}
	}
	// 石（ポケット４）の初期配置
	for (int i = 0; i < 16; i++) {
		DrawGraph(675, 400 + i * 15, gStone[i][3].img, TRUE);	
		if (i >= 10) {
			DrawGraph(700, 400 + i * 15, gStone[i][3].img, TRUE);
		}
	}
	// 石（ポケット５）の初期配置
	for (int i = 0; i < 16; i++) {
		DrawGraph(800, 400 + i * 15, gStone[i][4].img, TRUE);
		if (i >= 10) {
			DrawGraph(825, 400 + i * 15, gStone[i][4].img, TRUE);
		}
	}
	// 石（ポケット６）の初期配置
	for (int i = 0; i < 16; i++) {
		DrawGraph(925, 400 + i * 15, gStone[i][5].img, TRUE);
		if (i >= 10) {
			DrawGraph(950, 400 + i * 15, gStone[i][5].img, TRUE);
		}

	}

	// 2P石の初期配置
	
	// 石（ポケット１）の初期配置
	for (int i = 0; i < 16; i++) {
		DrawGraph(925, 50 + i * 15, gStone2[i][0].img, TRUE);
		if (i >= 10) {
			DrawGraph(950, 50 + i * 15, gStone2[i][0].img, TRUE);
		}
	}
	// 石（ポケット２）の初期配置
	for (int i = 0; i < 16; i++) {
		DrawGraph(800, 50 + i * 15, gStone2[i][1].img, TRUE);
		if (i >= 10) {
			DrawGraph(825, 50 + i * 15, gStone2[i][1].img, TRUE);
		}
	}
	// 石（ポケット３）の初期配置
	for (int i = 0; i < 16; i++) {
		DrawGraph(675, 50 + i * 15, gStone2[i][2].img, TRUE);
		if (i >= 10) {
			DrawGraph(700, 50 + i * 15, gStone2[i][2].img, TRUE);
		}
	}
	// 石（ポケット４）の初期配置
	
	for (int i = 0; i < 16; i++) {
		DrawGraph(550, 50 + i * 15, gStone2[i][3].img, TRUE);
		if (i >= 10) {
			DrawGraph(575, 50 + i * 15, gStone2[i][3].img, TRUE);
		}
	}
	// 石（ポケット５）の初期配置
	for (int i = 0; i < 16; i++) {
		DrawGraph(425, 50 + i * 15, gStone2[i][4].img, TRUE);
		if (i >= 10) {
			DrawGraph(450, 50 + i * 15, gStone2[i][4].img, TRUE);
		}
	}
	// 石（ポケット６）の初期配置
	for (int i = 0; i < 16; i++) {
		DrawGraph(300, 50 + i * 15, gStone2[i][5].img, TRUE);
		if (i >= 10) {
			DrawGraph(325, 50 + i * 15, gStone2[i][5].img, TRUE);
		}
	}

	//// 石（ゴール）の初期配置
	//for (int i = 0; i < 48; i++) {
	//	DrawGraph(150, 50 + i * 10, P2BigPocket[i][0], TRUE);
	//	if (i >= 24) {
	//		DrawGraph(175, 50 + i * 10,P2BigPocket[i][0], TRUE);
	//	}
	//}

	//------------- ここまで-----------------


    // 1Pターン時の ポケット移動
	if (P1Turn == 1) {
	    if(Pocket_cnt == 0) {
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

		}else if (Pocket_cnt == 3) {
			DrawBox(645, 385, 745, 600, GetColor(0, 0, 255), FALSE);
			DrawBox(646, 386, 746, 601, GetColor(0, 0, 255), FALSE);
			DrawBox(647, 387, 747, 602, GetColor(0, 0, 255), FALSE);

		}else if (Pocket_cnt == 4) {
			DrawBox(770, 385, 870, 600, GetColor(0, 0, 255), FALSE);
			DrawBox(771, 386, 871, 601, GetColor(0, 0, 255), FALSE);
			DrawBox(772, 387, 872, 602, GetColor(0, 0, 255), FALSE);

		}else if (Pocket_cnt == 5) {
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
	if (P2Turn == 1 ) {
		DrawFormatString(200,200,GetColor(255,255,255),"2P TURN");
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


	if (moveStone == 0) {

		for (int i = moveStone; i < InitialStone + 1; i++) {
			gStone[InitialStone + 1][moveStone + i].img = TRUE;
		}
		InitialStone++;
		for (int y = 16; y > 16; y--) {
			gStone[y][moveStone].img = FALSE;
	    }
		P2Turn = TRUE;
	}else if (moveStone == 1) {

		for (int i = moveStone; i < InitialStone + 1; i++) {
			gStone[InitialStone + 1][moveStone + i].img = TRUE;
		}
		InitialStone++;
		for (int y = 16; y > 16; y--) {
			gStone[y][moveStone].img = FALSE;
	    }
		P2Turn = TRUE;

	}else if (moveStone == 2) {

		for (int i = moveStone; i < InitialStone + 1; i++) {
			gStone[InitialStone + 1][moveStone + i].img = TRUE;
		}
		InitialStone++;
		for (int y = 16; y > 16; y--) {
			gStone[y][moveStone].img = FALSE;
	    }
		P2Turn = TRUE;

	}
	else if (moveStone == 3) {

		for (int i = moveStone; i < InitialStone + 1; i++) {
			gStone[InitialStone + 1][moveStone + i].img = TRUE;
		}
		InitialStone++;
		for (int y = 16; y > 16; y--) {
			gStone[y][moveStone].img = FALSE;
	    }
		P2Turn = TRUE;

	}
	else if (moveStone == 4) {

		for (int i = moveStone; i < InitialStone + 1; i++) {
			gStone[InitialStone + 1][moveStone + i].img = TRUE;
		}
		InitialStone++;
		for (int y = 16; y > 16; y--) {
			gStone[y][moveStone].img = FALSE;
	    }
		P2Turn = TRUE;

	}
	else if (moveStone == 5) {

		for (int i = moveStone; i < InitialStone + 1; i++) {
			gStone[InitialStone + 1][moveStone + i].img = TRUE;
		}
		InitialStone++;
		for (int y = 16; y > 16; y--) {
			gStone[y][moveStone].img = FALSE;
	    }
		P2Turn = TRUE;

	}



	if (moveStone2 == 0) {

		for (int i = moveStone; i < InitialStone + 1; i++) {
			gStone2[InitialStone + 1][moveStone + i].img = TRUE;
		}
		InitialStone++;
		for (int y = 16; y > 16; y--) {
			gStone2[y][moveStone].img = FALSE;
		}
		P1Turn = TRUE;

	}
	else if (moveStone2 == 1) {

		for (int i = moveStone; i < InitialStone + 1; i++) {
			gStone2[InitialStone + 1][moveStone + i].img = TRUE;
		}
		InitialStone++;
		for (int y = 16; y > 16; y--) {
			gStone2[y][moveStone].img = FALSE;
		}
		P1Turn = TRUE;

	}
	else if (moveStone2 == 2) {

		for (int i = moveStone; i < InitialStone + 1; i++) {
			gStone2[InitialStone + 1][moveStone + i].img = TRUE;
		}
		InitialStone++;
		for (int y = 16; y > 16; y--) {
			gStone2[y][moveStone].img = FALSE;
		}
		P1Turn = TRUE;

	}
	else if (moveStone2 == 3) {

		for (int i = moveStone; i < InitialStone + 1; i++) {
			gStone2[InitialStone + 1][moveStone + i].img = TRUE;
		}
		InitialStone++;
		for (int y = 16; y > 16; y--) {
			gStone2[y][moveStone].img = FALSE;
		}
		P1Turn = TRUE;

	}
	else if (moveStone2 == 4) {

		for (int i = moveStone; i < InitialStone + 1; i++) {
			gStone2[InitialStone + 1][moveStone + i].img = TRUE;
		}
		InitialStone++;
		for (int y = 16; y > 16; y--) {
			gStone2[y][moveStone].img = FALSE;
		}
		P1Turn = TRUE;

	}
	else if (moveStone2 == 5) {

		for (int i = moveStone; i < InitialStone + 1; i++) {
			gStone2[InitialStone + 1][moveStone + i].img = TRUE;
		}
		InitialStone++;
		for (int y = 16; y > 16; y--) {
			gStone2[y][moveStone].img = FALSE;
		}
		P1Turn = TRUE;

	}

}
 