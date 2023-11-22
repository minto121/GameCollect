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
	InitialStone = 4;
	Stone_cnt = 1;
	movePocket = 0;

	JustGoal = 0;

	for (int y = 0; y < 6; y++) {
		P1Pocket[y]+=1;
	}

	for (int y = 0; y < 6; y++) {
		P2Pocket[y]+=1;
	}

	// 石の画像処理
	for (int i = 0; i < 8; i++) {
		gStone[0][i].img = StoneImg[1];//赤
		gStone[1][i].img = StoneImg[5];//青
		gStone[2][i].img = StoneImg[3];//緑
		gStone[3][i].img = StoneImg[0];//黄
		gStone[4][i].img = StoneImg[2];//紫
		gStone[5][i].img = StoneImg[4];//白

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

	// -----------ここから直す箇所--------------

	// 石（赤）の初期配置
	for (int i = 0; i < 6; i++) {
		if (PlayerPocket >= 0) {

		}
		else {
			DrawGraph(300 + i * 125, 450, gStone[0][i].img, TRUE);
		}

	}
	DrawGraph(300, 160, gStone[0][6].img, TRUE);
	DrawGraph(300 + 125, 160, gStone[0][7].img, TRUE);

	// 石（青）の初期配置
	for (int i = 0; i < 6; i++) {
		if (PlayerPocket >= 0) {

		}
		else {
			DrawGraph(300 + i * 125, 470, gStone[1][i].img, TRUE);
		}
	}
	DrawGraph(300, 190, gStone[1][6].img, TRUE);
	DrawGraph(300 + 125, 190, gStone[1][7].img, TRUE);

	// 石（緑）の初期配置
	for (int i = 0; i < 6; i++) {
		if (PlayerPocket >= 0) {

		}
		else {
			DrawGraph(300 + i * 125, 490, gStone[2][i].img, TRUE);
		}
	}
	DrawGraph(300+125*2, 160, gStone[2][6].img, TRUE);
	DrawGraph(300 + 125*3, 160, gStone[2][7].img, TRUE);

	// 石（黄）の初期配置
	for (int i = 0; i < 6; i++) {
		if (PlayerPocket >= 0) {

		}
		else {
			DrawGraph(300 + i * 125, 510, gStone[3][i].img, TRUE);
		}
	}
	DrawGraph(300 + 125*2, 190, gStone[3][6].img, TRUE);
	DrawGraph(300 + 125*3, 190, gStone[3][7].img, TRUE);

	// 石（紫）の初期配置
	for (int i = 0; i < 6; i++) {
		DrawGraph(300 + i * 125, 100, gStone[4][i].img, TRUE);
	}
	DrawGraph(300 + 125 * 4, 190, gStone[4][6].img, TRUE);
	DrawGraph(300 + 125 * 5, 190, gStone[4][7].img, TRUE);

	// 石（白）の初期配置

	for (int i = 0; i < 6; i++) {
		DrawGraph(300 + i * 125, 130, gStone[5][i].img, TRUE);

	}
	DrawGraph(300 + 125 * 4, 160, gStone[5][6].img, TRUE);
	DrawGraph(300 + 125 * 5, 160, gStone[5][7].img, TRUE);

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
			if (Pocket_cnt == 1) {
				DrawBox(385, 385, 485, 600, GetColor(255, 0, 0), FALSE);
			}
			else if (Pocket_cnt == 2) {
				DrawBox(515, 385, 615, 600, GetColor(255, 0, 0), FALSE);

			}else if (Pocket_cnt == 3) {
				DrawBox(645, 385, 745, 600, GetColor(255, 0, 0), FALSE);

			}else if (Pocket_cnt == 4) {
				DrawBox(770, 385, 870, 600, GetColor(255, 0, 0), FALSE);

			}else if (Pocket_cnt == 5) {
				DrawBox(900, 385, 1000, 600, GetColor(255, 0, 0), FALSE);

			}
			else {
				DrawBox(255, 385, 355, 600, GetColor(255, 0, 0), FALSE);
			}
	}


	// 2Pターン時のポケット移動
	if (P2Turn == 1) {
		if (Pocket_cnt == 1) {
			DrawBox(255, 85, 355, 300, GetColor(255, 0, 0), FALSE);
		}
		else if (Pocket_cnt == 2) {
			DrawBox(385, 85, 485, 300, GetColor(255, 0, 0), FALSE);

		}
		else if (Pocket_cnt == 3) {
			DrawBox(515, 85, 615, 300, GetColor(255, 0, 0), FALSE);

		}
		else if (Pocket_cnt == 4) {
			DrawBox(645, 85, 745, 300, GetColor(255, 0, 0), FALSE);

		}
		else if (Pocket_cnt == 5) {
			DrawBox(770, 85, 870, 300, GetColor(255, 0, 0), FALSE);

		}
		else {
			DrawBox(900, 85, 1000, 300, GetColor(255, 0, 0), FALSE);
		}
	}
	
	//ポケットの中に値が入っているか
	for (int i = 0; i < 6; i++) {
		DrawFormatString(300 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", P1Pocket[i]);
		DrawFormatString(500 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", P2Pocket[i]);
	}

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

	if (PlayerPocket >=0) {
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {

			StoneFlg = TRUE;

			if (StoneFlg == TRUE) {
				moveStone = PlayerPocket;
				JustGoal = InitialStone;
			}
		}
	}
	if (PartnerPocket >=0) {
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {

			StoneFlg = TRUE;

			if (StoneFlg == TRUE) {
				moveStone2 = PartnerPocket;
				JustGoal = InitialStone;
			}
		}
	}

	if (P1Turn == TRUE) {

		// ポケットを選択
		if (moveStone == 0) {

			// 選択したポケットに格納されている石を移動させる
			for (int i = 0; i < P1StoneSave[0][i + InitialStone]; i++) {
				P1StoneSave[moveStone + i][i];
				// 移動する石が1Pポケットの数を超えるなら、2Pポケットに余剰分を格納する
				if (InitialStone > 6) {
					for (int z = 6; z < InitialStone; z++) {
						P2StoneSave[z][InitialStone + 1];
					}
					// 石が移動したポケットには＋１ずつ追加
					for (int y = 0; y < InitialStone; y++) {
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
		}
		else if (moveStone == 1) {
			// 選択したポケットに格納されている石を移動させる
			for (int i = 0; i < P1StoneSave[0][i + InitialStone]; i++) {
				P1StoneSave[moveStone + i][i];
				// 移動する石が1Pポケットの数を超えるなら、2Pポケットに余剰分を格納する
				if (InitialStone > 5) {
					for (int z = 5; z < InitialStone; z++) {
						P2StoneSave[z][InitialStone + 1];
					}
					// 石が移動したポケットには＋１ずつ追加
					for (int y = 0; y < InitialStone; y++) {
						P1StoneSave[y][InitialStone + 1];

					}
				}
			}

			// 選択したポケットの中身を０にする
			P1StoneSave[0][InitialStone - InitialStone] ;
			// 大きいポケットに石が入る
			if (JustGoal >= 5) {
				P1BigPocket+=1;
				JustGoal = 0;
			}
			else if (moveStone == 2) {
				// 選択したポケットに格納されている石を移動させる
				for (int i = 0; i < P1StoneSave[0][i + InitialStone]; i++) {
					P1StoneSave[moveStone + i][i];
					// 移動する石が1Pポケットの数を超えるなら、2Pポケットに余剰分を格納する
					if (InitialStone > 4) {
						for (int z = 4; z < InitialStone; z++) {
							P2StoneSave[z][InitialStone + 1];
						}
						// 石が移動したポケットには＋１ずつ追加
						for (int y = 0; y < InitialStone; y++) {
							P1StoneSave[y][InitialStone + 1];

						}
					}
				}

				// 選択したポケットの中身を０にする
				P1StoneSave[0][InitialStone - InitialStone] ;
				// 大きいポケットに石が入る
				if (JustGoal >= 4) {
					P1BigPocket += 1;
					JustGoal = 0;
				}
			}
			else if (moveStone == 3) {
				// 選択したポケットに格納されている石を移動させる
				for (int i = 0; i < P1StoneSave[0][i + InitialStone]; i++) {
					P1StoneSave[moveStone + i][i];
					// 移動する石が1Pポケットの数を超えるなら、2Pポケットに余剰分を格納する
					if (InitialStone > 3) {
						for (int z = 3; z < InitialStone; z++) {
							P2StoneSave[z][InitialStone + 1];
						}
						// 石が移動したポケットには＋１ずつ追加
						for (int y = 0; y < InitialStone; y++) {
							P1StoneSave[y][InitialStone + 1];

						}
					}
				}

				// 選択したポケットの中身を０にする
				P1StoneSave[0][InitialStone - InitialStone] ;
				// 大きいポケットに石が入る
				if (JustGoal >= 3) {
					P1BigPocket += 1;
					JustGoal = 0;
				}
			}
			else if (moveStone == 4) {
				// 選択したポケットに格納されている石を移動させる
				for (int i = 0; i < P1StoneSave[0][i + InitialStone]; i++) {
					P1StoneSave[moveStone + i][i];
					// 移動する石が1Pポケットの数を超えるなら、2Pポケットに余剰分を格納する
					if (InitialStone > 2) {
						for (int z = 2; z < InitialStone; z++) {
							P2StoneSave[z][InitialStone + 1];
						}
						// 石が移動したポケットには＋１ずつ追加
						for (int y = 0; y < InitialStone; y++) {
							P1StoneSave[y][InitialStone + 1];

						}
					}
				}
				// 選択したポケットの中身を０にする
				P1StoneSave[0][InitialStone - InitialStone];
				// 大きいポケットに石が入る
				if (JustGoal >= 2) {
					P1BigPocket += 1;
					JustGoal = 0;
				}
			}
			else if (moveStone == 5) {
				// 選択したポケットに格納されている石を移動させる
				for (int i = 0; i < P1StoneSave[0][i + InitialStone]; i++) {
					P1StoneSave[moveStone + i][i];
					// 移動する石が1Pポケットの数を超えるなら、2Pポケットに余剰分を格納する
					if (InitialStone > 1) {
						for (int z = 1; z < InitialStone; z++) {
							P2StoneSave[z][InitialStone + 1];
						}
						// 石が移動したポケットには＋１ずつ追加
						for (int y = 0; y < InitialStone; y++) {
							P1StoneSave[y][InitialStone + 1];

						}
					}
				}

				// 選択したポケットの中身を０にする
				P1StoneSave[0][InitialStone - InitialStone];
				// 大きいポケットに石が入る
				if (JustGoal >= 1) {
					P1BigPocket += 1;
					JustGoal = 0;
				}
			}
		}
	}
}
 