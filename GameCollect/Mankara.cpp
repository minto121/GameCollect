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


	for (int y = 0; y < 6; y++) {
		P1Pocket[y] += 1;
	}

	for (int y = 0; y < 6; y++) {
		P2Pocket[y] += 1;
	}

	// 石の画像処理
	for (int i = 0; i < 8; i++) {
		for (int y = 0; y < 6; y++) {
			gStone[y][i].img = StoneImg[y];//ポケット１
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
	for (int i = 0; i < 4; i++) {
		if (PlayerPocket == 0) {
			// ポケットの中身の石の数の分だけX軸を移動させる
			for (int y = 0; y < JustGoal; ) {
				DrawGraph(300 + y * 125, 450 + y * 20, gStone[y][0].img, TRUE);
				y++;
			}
		}
		else {
			DrawGraph(300, 450 + i * 20, gStone[i][0].img, TRUE);
		}

	}
	// 石（ポケット２）の初期配置
	for (int i = 0; i < 4; i++) {
		if (PlayerPocket == 1) {
			// ポケットの中身の石の数の分だけX軸を移動させる
			for (int y = 0; y < JustGoal; ) {
				DrawGraph(425 + y * 125, 450 + y * 20, gStone[y][1].img, TRUE);
				y++;
			}
		}
		else {
			DrawGraph(300 + 125, 450 + i * 20, gStone[i][1].img, TRUE);
		}
	}
	// 石（ポケット３）の初期配置
	for (int i = 0; i < 4; i++) {
		if (PlayerPocket == 2) {
			// ポケットの中身の石の数の分だけX軸を移動させる
			for (int y = 0; y < JustGoal; ) {
				DrawGraph(550 + y * 125, 450 + y * 20, gStone[y][2].img, TRUE);
				y++;
			}
		}
		else {
			DrawGraph(550, 450 + i * 20, gStone[i][2].img, TRUE);
		}
	}
	// 石（ポケット４）の初期配置
	for (int i = 0; i < 4; i++) {
		if (PlayerPocket == 3) {
			for (int y = 0; y < JustGoal; ) {
				// ポケットの中身の石の数の分だけX軸を移動させる
				DrawGraph(675 + y * 125, 450 + y * 20, gStone[y][3].img, TRUE);
				y++;
			}
		}
		else {
			DrawGraph(675, 450 + i * 20, gStone[i][3].img, TRUE);
		}
	}
	// 石（ポケット５）の初期配置
	for (int i = 0; i < 4; i++) {

		if (PlayerPocket == 4) {
			// ポケットの中身の石の数の分だけX軸を移動させる
			for (int y = 0; y < JustGoal; ) {
				DrawGraph(800 + y * 125, 450 + y * 20, gStone[y][4].img, TRUE);
				y++;
			}
		}
		else {
			DrawGraph(800, 450 + i * 20, gStone[i][4].img, TRUE);
		}
	}
	// 石（ポケット６）の初期配置
	for (int i = 0; i < 4; i++) {
		if (PlayerPocket == 5) {
			for (int y = 0; y < JustGoal; ) {
				// ポケットの中身の石の数の分だけX軸を移動させる
				DrawGraph(925 + y * 125, 450 + y * 20, gStone[y][5].img, TRUE);
				y++;
			}
		}
		else {
			DrawGraph(925, 450 + i * 20, gStone[i][5].img, TRUE);
		}

	}

	//// 2P石の初期配置
	// -----------ここから石の初期配置--------------

	// 石（ポケット１）の初期配置
	for (int i = 0; i < 4; i++) {
		if (PartnerPocket == 0) {
			// ポケットの中身の石の数の分だけX軸を移動させる
			for (int y = 0; y < JustGoal; ) {
				DrawGraph(300 + 5 * 125 - y * 125, 100 + y * 20, gStone[y][0].img, TRUE);
				y++;
			}
		}
		else {
			DrawGraph(300 + 5 * 125, 100 + i * 20, gStone[i][0].img, TRUE);
		}

	}
	// 石（ポケット２）の初期配置
	for (int i = 0; i < 4; i++) {
		if (PartnerPocket == 1) {
			// ポケットの中身の石の数の分だけX軸を移動させる
			for (int y = 0; y < JustGoal; ) {
				DrawGraph(300 + 4 * 125 - y * 125, 100 + y * 20, gStone[y][1].img, TRUE);
				y++;
			}
		}
		else {
			DrawGraph(300 + 4 * 125, 100 + i * 20, gStone[i][1].img, TRUE);
		}
	}
	// 石（ポケット３）の初期配置
	for (int i = 0; i < 4; i++) {
		if (PartnerPocket == 2) {
			// ポケットの中身の石の数の分だけX軸を移動させる
			for (int y = 0; y < JustGoal; ) {
				DrawGraph(300 + 3 * 125 - y * 125, 100 + y * 20, gStone[y][2].img, TRUE);
				y++;
			}
		}
		else {
			DrawGraph(300 + 3 * 125, 100 + i * 20, gStone[i][2].img, TRUE);
		}
	}
	// 石（ポケット４）の初期配置
	for (int i = 0; i < 4; i++) {
		if (PartnerPocket == 3) {
			for (int y = 0; y < JustGoal; ) {
				// ポケットの中身の石の数の分だけX軸を移動させる
				DrawGraph(300 + 2 * 125 - y * 125, 100 + y * 20, gStone[y][3].img, TRUE);
				y++;
			}
		}
		else {
			DrawGraph(300 + 2 * 125, 100 + i * 20, gStone[i][3].img, TRUE);
		}
	}
	// 石（ポケット５）の初期配置
	for (int i = 0; i < 4; i++) {

		if (PartnerPocket == 4) {
			// ポケットの中身の石の数の分だけX軸を移動させる
			for (int y = 0; y < JustGoal; ) {
				DrawGraph(300 + 1 * 125 - y * 125, 100 + y * 20, gStone[y][4].img, TRUE);
				y++;
			}
		}
		else {
			DrawGraph(300 + 1 * 125, 100 + i * 20, gStone[i][4].img, TRUE);
		}
	}
	// 石（ポケット６）の初期配置
	for (int i = 0; i < 4; i++) {
		if (PlayerPocket == 5) {
			for (int y = 0; y < JustGoal; ) {
				// ポケットの中身の石の数の分だけX軸を移動させる
				DrawGraph(300 - y * 125, 100 + y * 20, gStone[y][5].img, TRUE);
				y++;
			}
		}
		else {
			DrawGraph(300, 100 + i * 20, gStone[i][5].img, TRUE);
		}

	}
	//DrawGraph(300 + 125 * 4, 190, gStone[0][6].img, TRUE);
	//DrawGraph(300 + 125 * 5, 190, gStone[0][7].img, TRUE);

	//DrawGraph(300 + 125 * 2, 190, gStone[1][6].img, TRUE);
	//DrawGraph(300 + 125 * 3, 190, gStone[1][7].img, TRUE);

	//DrawGraph(300 + 125 * 2, 160, gStone[2][6].img, TRUE);
	//DrawGraph(300 + 125 * 3, 160, gStone[2][7].img, TRUE);

	//DrawGraph(300, 190, gStone[3][6].img, TRUE);
	//DrawGraph(300 + 125, 190, gStone[3][7].img, TRUE);

	//DrawGraph(300, 160, gStone[4][6].img, TRUE);
	//DrawGraph(300 + 125, 160, gStone[4][7].img, TRUE);

	//DrawGraph(300 + 125 * 4, 160, gStone[5][6].img, TRUE);
	//DrawGraph(300 + 125 * 5, 160, gStone[5][7].img, TRUE);

	//------------- ここまで-----------------


	// ポケットを選択
	if (moveStone == 0) {
		// 選択したポケットに格納されている石を移動させる
		for (int i = 0; i < P1StoneSave[0][i+=InitialStone]; i++) {
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
		for (int i = 0; i < P1StoneSave[0][ i +=InitialStone]; i++) {
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

	//　画像移動時の数的処理
	if (P1Turn == TRUE) {

		// ポケットを選択
		if (moveStone == 0) {

			// 選択したポケットに格納されている石を移動させる
			for (int i = 0; i < P1StoneSave[0][i + 1]; i++) {
				P1StoneSave[moveStone + i][i];
				JustGoal = InitialStone;
				// 移動する石が1Pポケットの数を超えるなら、2Pポケットに余剰分を格納する
				if (InitialStone > 6) {
					for (int z = 6; z < InitialStone; z++) {
						P2StoneSave[z][InitialStone + 1];
					}
					// 石が移動したポケットには＋１ずつ追加
					for (int y = 1; y < InitialStone; y++) {
						P1StoneSave[y][InitialStone + 1];

					}
				}
			}

			// 選択したポケットの中身を０にする
			P1StoneSave[0][InitialStone - InitialStone] ;
			// 大きいポケットに石が入る
			if (JustGoal >= 6) {
				P1BigPocket += 1;
				JustGoal = 0;
			}
			P1Turn = FALSE;
			P2Turn = TRUE;
		}
		else if (moveStone == 1) {
			// 選択したポケットに格納されている石を移動させる
			for (int i = 0; i < P1StoneSave[1][i + 2]; i++) {
				P1StoneSave[moveStone + i][i];
				JustGoal = InitialStone;
				// 移動する石が1Pポケットの数を超えるなら、2Pポケットに余剰分を格納する
				if (InitialStone > 5) {
					for (int z = 5; z < InitialStone; z++) {
						P2StoneSave[z][InitialStone + 1];
					}
					// 石が移動したポケットには＋１ずつ追加
					for (int y = 2; y < InitialStone; y++) {
						P1StoneSave[y][InitialStone + 1];

					}
				}
			}

			// 選択したポケットの中身を０にする
			P1StoneSave[1][InitialStone - InitialStone];
			// 大きいポケットに石が入る
			if (JustGoal >= 5) {
				P1BigPocket += 1;
				JustGoal = 0;
			}
			P1Turn = FALSE;
			P2Turn = TRUE;
		}
		else if (moveStone == 2) {
			// 選択したポケットに格納されている石を移動させる
				for (int i = 0; i < P1StoneSave[2][i + 3]; i++) {
					P1StoneSave[moveStone + i][i];
					JustGoal = InitialStone;
					// 移動する石が1Pポケットの数を超えるなら、2Pポケットに余剰分を格納する
					if (InitialStone > 4) {
						for (int z = 4; z < InitialStone; z++) {
							P2StoneSave[z][InitialStone + 1];
						}
						// 石が移動したポケットには＋１ずつ追加
						for (int y = 3; y < InitialStone; y++) {
							P1StoneSave[y][InitialStone + 1];

						}
					}
				}

				// 選択したポケットの中身を０にする
				P1StoneSave[2][InitialStone - InitialStone] ;
				// 大きいポケットに石が入る
				if (JustGoal >= 4) {
					P1BigPocket += 1;
					JustGoal = 0;
				}
				P1Turn = FALSE;
				P2Turn = TRUE;
		}
		else if (moveStone == 3) {
				// 選択したポケットに格納されている石を移動させる
				for (int i = 0; i < P1StoneSave[3][i + 4]; i++) {
					P1StoneSave[moveStone + i][i];
					JustGoal = InitialStone;
					// 移動する石が1Pポケットの数を超えるなら、2Pポケットに余剰分を格納する
					if (InitialStone > 3) {
						for (int z = 3; z < InitialStone; z++) {
							P2StoneSave[z][InitialStone + 1];
						}
						// 石が移動したポケットには＋１ずつ追加
						for (int y = 4; y < InitialStone; y++) {
							P1StoneSave[y][InitialStone + 1];

						}
					}
				}

				// 選択したポケットの中身を０にする
				P1StoneSave[3][InitialStone - InitialStone] ;
				// 大きいポケットに石が入る
				if (JustGoal >= 3) {
					P1BigPocket += 1;
					JustGoal = 0;
				}
				P1Turn = FALSE;
				P2Turn = TRUE;
		}
		else if (moveStone == 4) {
				// 選択したポケットに格納されている石を移動させる
				for (int i = 0; i < P1StoneSave[4][i + InitialStone]; i++) {
					P1StoneSave[moveStone + i][i];
					JustGoal = InitialStone;
					// 移動する石が1Pポケットの数を超えるなら、2Pポケットに余剰分を格納する
					if (InitialStone > 2) {
						for (int z = 2; z < InitialStone; z++) {
							P2StoneSave[z][InitialStone + 1];
						}
						// 石が移動したポケットには＋１ずつ追加
						for (int y = 4; y < InitialStone; y++) {
							P1StoneSave[y][InitialStone + 1];

						}
					}
				}
				// 選択したポケットの中身を０にする
				P1StoneSave[4][InitialStone - InitialStone];
				// 大きいポケットに石が入る
				if (JustGoal >= 2) {
					P1BigPocket += 1;
					JustGoal = 0;
				}
				P1Turn = FALSE;
				P2Turn = TRUE;
		}
		else if (moveStone == 5) {
				// 選択したポケットに格納されている石を移動させる
				for (int i = 0; i < P1StoneSave[5][i + 5]; i++) {
					P1StoneSave[moveStone + i][i];
					JustGoal = InitialStone;
					// 移動する石が1Pポケットの数を超えるなら、2Pポケットに余剰分を格納する
					if (InitialStone > 1) {
						for (int z = 1; z < InitialStone; z++) {
							P2StoneSave[z][InitialStone + 1];
						}
						// 石が移動したポケットには＋１ずつ追加
						for (int y = 5; y < InitialStone; y++) {
							P1StoneSave[y][InitialStone + 1];

						}
					}
				}

				// 選択したポケットの中身を０にする
				P1StoneSave[5][InitialStone - InitialStone];
				// 大きいポケットに石が入る
				if (JustGoal >= 1) {
					P1BigPocket += 1;
					JustGoal = 0;
				}
				P1Turn = FALSE;
				P2Turn = TRUE;
		}
	}	
	
	
	//　画像移動時の数的処理
	if (P2Turn == TRUE) {

		// ポケットを選択
		if (moveStone == 0) {

			// 選択したポケットに格納されている石を移動させる
			for (int i = 0; i < P2StoneSave[0][i + 1]; i++) {
				P2StoneSave[moveStone + i][i];
				JustGoal = InitialStone;
				// 移動する石が2Pポケットの数を超えるなら、1Pポケットに余剰分を格納する
				if (InitialStone > 6) {
					for (int z = 6; z < InitialStone; z++) {
						P1StoneSave[z][InitialStone + 1];
					}
					// 石が移動したポケットには＋１ずつ追加
					for (int y = 1; y < InitialStone; y++) {
						P2StoneSave[y][InitialStone + 1];

					}
				}
			}

			// 選択したポケットの中身を０にする
			P2StoneSave[0][InitialStone - InitialStone] ;
			// 大きいポケットに石が入る
			if (JustGoal >= 6) {
				P2BigPocket += 1;
				JustGoal = 0;
			}
			P1Turn = TRUE;
			P2Turn = FALSE;
		}
		else if (moveStone == 1) {
			// 選択したポケットに格納されている石を移動させる
			for (int i = 0; i < P2StoneSave[1][i + 2]; i++) {
				P2StoneSave[moveStone + i][i];
				JustGoal = InitialStone;
				// 移動する石が2Pポケットの数を超えるなら、1Pポケットに余剰分を格納する
				if (InitialStone > 5) {
					for (int z = 5; z < InitialStone; z++) {
						P1StoneSave[z][InitialStone + 1];
					}
					// 石が移動したポケットには＋１ずつ追加
					for (int y = 2; y < InitialStone; y++) {
						P2StoneSave[y][InitialStone + 1];

					}
				}
			}

			// 選択したポケットの中身を０にする
			P2StoneSave[1][InitialStone - InitialStone];
			// 大きいポケットに石が入る
			if (JustGoal >= 5) {
				P2BigPocket += 1;
				JustGoal = 0;
			}
			P1Turn = TRUE;
			P2Turn = FALSE;
		}
		else if (moveStone == 2) {
				// 選択したポケットに格納されている石を移動させる
				for (int i = 0; i < P2StoneSave[2][i + 3]; i++) {
					P2StoneSave[moveStone + i][i];
					JustGoal = InitialStone;
					// 移動する石が2Pポケットの数を超えるなら、1Pポケットに余剰分を格納する
					if (InitialStone > 4) {
						for (int z = 4; z < InitialStone; z++) {
							P1StoneSave[z][InitialStone + 1];
						}
						// 石が移動したポケットには＋１ずつ追加
						for (int y = 3; y < InitialStone; y++) {
							P2StoneSave[y][InitialStone + 1];

						}
					}
				}

				// 選択したポケットの中身を０にする
				P2StoneSave[2][InitialStone - InitialStone] ;
				// 大きいポケットに石が入る
				if (JustGoal >= 4) {
					P2BigPocket += 1;
					JustGoal = 0;
				}
		}
		else if (moveStone == 3) {
				// 選択したポケットに格納されている石を移動させる
				for (int i = 0; i < P2StoneSave[3][i + 4]; i++) {
					P2StoneSave[moveStone + i][i];
					JustGoal = InitialStone;
					// 移動する石が2Pポケットの数を超えるなら、1Pポケットに余剰分を格納する
					if (InitialStone > 3) {
						for (int z = 3; z < InitialStone; z++) {
							P1StoneSave[z][InitialStone + 1];
						}
						// 石が移動したポケットには＋１ずつ追加
						for (int y = 4; y < InitialStone; y++) {
							P2StoneSave[y][InitialStone + 1];

						}
					}
				}

				// 選択したポケットの中身を０にする
				P2StoneSave[3][InitialStone - InitialStone] ;
				// 大きいポケットに石が入る
				if (JustGoal >= 3) {
					P2BigPocket += 1;
					JustGoal = 0;
				}
				P1Turn = TRUE;
				P2Turn = FALSE;
		}
		else if (moveStone == 4) {
		     	// 選択したポケットに格納されている石を移動させる
				for (int i = 0; i < P2StoneSave[4][i + InitialStone]; i++) {
					P2StoneSave[moveStone + i][i];
					JustGoal = InitialStone;
					// 移動する石が2Pポケットの数を超えるなら、1Pポケットに余剰分を格納する
					if (InitialStone > 2) {
						for (int z = 2; z < InitialStone; z++) {
							P1StoneSave[z][InitialStone + 1];
						}
						// 石が移動したポケットには＋１ずつ追加
						for (int y = 4; y < InitialStone; y++) {
							P2StoneSave[y][InitialStone + 1];

						}
					}
				}
				// 選択したポケットの中身を０にする
				P2StoneSave[4][InitialStone - InitialStone];
				// 大きいポケットに石が入る
				if (JustGoal >= 2) {
					P2BigPocket += 1;
					JustGoal = 0;
				}
				P1Turn = TRUE;
				P2Turn = FALSE;
		}
		else if (moveStone == 5) {
				// 選択したポケットに格納されている石を移動させる
				for (int i = 0; i < P2StoneSave[5][i + 5]; i++) {
					P2StoneSave[moveStone + i][i];
					JustGoal = InitialStone;
					// 移動する石が2Pポケットの数を超えるなら、1Pポケットに余剰分を格納する
					if (InitialStone > 1) {
						for (int z = 1; z < InitialStone; z++) {
							P1StoneSave[z][InitialStone + 1];
						}
						// 石が移動したポケットには＋１ずつ追加
						for (int y = 5; y < InitialStone; y++) {
							P2StoneSave[y][InitialStone + 1];

						}
					}
				}

				// 選択したポケットの中身を０にする
				P2StoneSave[5][InitialStone - InitialStone];
				// 大きいポケットに石が入る
				if (JustGoal >= 1) {
					P2BigPocket += 1;
					JustGoal = 0;
				}
				P1Turn = TRUE;
				P2Turn = FALSE;
		}
	}
}
 