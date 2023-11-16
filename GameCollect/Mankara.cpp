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
	sideAddition = 0;

	PlayerPocket = 0;
	PartnerPocket = 0;

	for (int y = 0; y < 6; y++) {
		P1Pocket[y]+=1;
	}

	for (int y = 0; y < 6; y++) {
		P2Pocket[y]+=1;
	}

	// 石の画像処理
	for (int i = 0; i < 8; i++) {
		gStone.img[0][i] = StoneImg[1];//赤
		gStone.img[1][i] = StoneImg[5];//青
		gStone.img[2][i] = StoneImg[3];//緑
		gStone.img[3][i] = StoneImg[0];//黄
		gStone.img[4][i] = StoneImg[2];//紫
		gStone.img[5][i] = StoneImg[4];//白

	}

	for (int i = 0; i < 6; i++) {
		StonePocket[1][i] = InitialStone; // 2P（[1]）のポケット（[6]）の中にStone_cntの初期値（4）を格納
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


	
	 //1P用石の移動処理
	 if (P1Turn == 1) {
		 if (Pocket_cnt == 0) {
			 if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				 // Aボタンで決定した時に選択したポケット以外をFALSEにする処理
				 PlayerPocket = 0;
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
				 PlayerPocket = 1;
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
				 PlayerPocket = 2;
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
				 PlayerPocket = 3;
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
				 PlayerPocket = 4;
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
				 PlayerPocket = 5;
				 P1Pocket[0] = FALSE;
				 P1Pocket[1] = FALSE;
				 P1Pocket[2] = FALSE;
				 P1Pocket[3] = FALSE;
				 P1Pocket[4] = FALSE;
				 P1Pocket[5] = TRUE;
			 }
		 }
	 }
	/* else {
		 PlayerPocket = 0;
	 }*/

	 //2P用石の移動処理
	 if (P2Turn == 1) {
		 if (Pocket_cnt == 0) {
			 if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
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
				 P2Pocket[0] = FALSE;
				 P2Pocket[1] = FALSE;
				 P2Pocket[2] = FALSE;
				 P2Pocket[3] = FALSE;
				 P2Pocket[4] = FALSE;
				 P2Pocket[5] = TRUE;
			 }
		 }
	 }


	 if (P1Turn == 1) {
		 int i = 0;

		 if (P1Pocket[PlayerPocket] == TRUE) {
			 switch (PlayerPocket)
			 {
			 case 0:
				 for (int y = StonePocket[0][PlayerPocket]; y > 0; y--) {
					 StonePocket[0][i + y] += Stone_cnt;
						 DrawGraph(300 + y * 125, 430, gStone.img[y][0], TRUE);
				 }
				 break;
			 case 1:
				 for (int y = StonePocket[0][PlayerPocket]; y > 0; y--) {
					 StonePocket[0][i + y] += Stone_cnt;
					 DrawGraph(300 + y * 125, 430, gStone.img[y][1], TRUE);

				 }
				 break;
			 case 2:
				 for (int y = StonePocket[0][PlayerPocket]; y > 0; y--) {
					 StonePocket[0][i + y] += Stone_cnt;
					 DrawGraph(300 + y * 125, 430, gStone.img[y][2], TRUE);

				 }				 
				 break;
			 case 3:
				 for (int y = StonePocket[0][PlayerPocket]; y > 0; y--) {
					 StonePocket[0][i + y] += Stone_cnt;
					 DrawGraph(300 + y * 125, 430, gStone.img[y][3], TRUE);

				 }
				 break;
			 case 4:
				 for (int y = StonePocket[0][PlayerPocket]; y > 0; y--) {
					 StonePocket[0][i + y] += Stone_cnt;
					 DrawGraph(300 + y * 125, 430 , gStone.img[y][4], TRUE);

				 }
				 break;
			 case 5:
				 for (int y = StonePocket[0][PlayerPocket]; y > 0; y--) {
					 StonePocket[0][i + y] += Stone_cnt;
					 DrawGraph(300 + y * 125, 430, gStone.img[y][5], TRUE);

				 }
				 break;
			 default:
				 
				 break;
			 }
		 }
	 }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             

	 /*if (P1Turn == 1) {
		 if (P1Pocket[0] == TRUE) {
			 if (Stone_cnt > 0) {
				 StonePocket[1] += Stone_cnt;
				 StonePocket[2] += Stone_cnt;
				 StonePocket[3] += Stone_cnt;
				 StonePocket[4] += Stone_cnt;
					 Stone_cnt-=1;
			 }
			 P2Turn = 1;
			 P1Turn = 0;
		 }
		 else if (P1Pocket[1] == TRUE) {
			 movePocket = 1;
			 if (Stone_cnt > 0) {
				 StonePocket[1 + movePocket] += Stone_cnt;
				 StonePocket[2 + movePocket] += Stone_cnt;
				 StonePocket[3 + movePocket] += Stone_cnt;
				 StonePocket[4 + movePocket] += Stone_cnt;
				 Stone_cnt -= 1;
			 }
			 P2Turn = 1;
			 P1Turn = 0;
		 }
		 else if (P1Pocket[2] == TRUE) {
			 movePocket = 2;
			 if (Stone_cnt > 0) {
				 StonePocket[1 + movePocket] += Stone_cnt;
				 StonePocket[2 + movePocket] += Stone_cnt;
				 StonePocket[3 + movePocket] += Stone_cnt;
				 StonePocket[4 + movePocket] += Stone_cnt;
				 P1BigPocket++;
				 Stone_cnt -= 2;
			 }
			 P2Turn = 0;
			 P1Turn = 1;

		 }
		 else if (P1Pocket[3] == TRUE) {
			 movePocket = 3;
			 if (Stone_cnt > 0) {
				 StonePocket[1 + movePocket] += Stone_cnt;
				 StonePocket[2 + movePocket] += Stone_cnt;
				 P1BigPocket++;
				 StonePocket[3 + movePocket] += Stone_cnt;
				 Stone_cnt -= 3;
			 }
			 P2Turn = 1;
			 P1Turn = 0;
		 }
		 else if (P1Pocket[4] == TRUE) {
			 movePocket = 4;
			 if (Stone_cnt > 0) {
				 StonePocket[1 + movePocket] += Stone_cnt;
				 StonePocket[2 + movePocket] += Stone_cnt;
				 P1BigPocket++;
				 StonePocket[3 + movePocket] += Stone_cnt;
				 Stone_cnt -= 4;
			 }
			 P2Turn = 1;
			 P1Turn = 0;
		 }
		 else if (P1Pocket[5] == TRUE) {
			 movePocket = 5;
			 if (Stone_cnt > 0) {
				 StonePocket[1 + movePocket] += Stone_cnt;
				 StonePocket[2 + movePocket] += Stone_cnt;
				 P1BigPocket++;
				 StonePocket[3 + movePocket] += Stone_cnt;
				 Stone_cnt -= 5;
			 }
			 P2Turn = 1;
			 P1Turn = 0;
		 }
	 }*/



	 //// ２P用石の移動
	 //if (P2Turn == 1) {

		// if (P2Pocket[0] == TRUE) {
		//	 
		//	 if (Stone_cnt > 0) {
		//		 StonePocket[7 + movePocket] += Stone_cnt;
		//		 StonePocket[8 + movePocket] += Stone_cnt;
		//		 StonePocket[9 + movePocket] += Stone_cnt;
		//		 StonePocket[10 + movePocket] += Stone_cnt;
		//		 Stone_cnt -= 1;
		//	 }
		//	 P2Turn = 0;
		//	 P1Turn = 1;
		// }
		// else if (P2Pocket[1] == TRUE) {
		//	 movePocket = 1;
		//	 if (Stone_cnt > 0) {
		//		 StonePocket[7 + movePocket] += Stone_cnt;
		//		 StonePocket[8 + movePocket] += Stone_cnt;
		//		 StonePocket[9 + movePocket] += Stone_cnt;
		//		 StonePocket[10 + movePocket] += Stone_cnt;
		//		 Stone_cnt -= 1;
		//	 }
		//	 P2Turn = 0;
		//	 P1Turn = 1;
		// }
		// else if (P2Pocket[2] == TRUE) {
		//	 movePocket = 2;
		//	 if (Stone_cnt > 0) {
		//		 StonePocket[7 + movePocket] += Stone_cnt;
		//		 StonePocket[8 + movePocket] += Stone_cnt;
		//		 StonePocket[9 + movePocket] += Stone_cnt;
		//		 P2BigPocket++;
		//		 Stone_cnt -= 2;
		//	 }
		//	 P2Turn = 0;
		//	 P1Turn = 1;
		// }
		// else if (P2Pocket[3] == TRUE) {
		//	 movePocket = 3;
		//	 if (Stone_cnt > 0) {
		//		 StonePocket[7 + movePocket] += Stone_cnt;
		//		 StonePocket[8 + movePocket] += Stone_cnt;
		//		 P2BigPocket++;
		//		 StonePocket[0] += Stone_cnt;
		//		 Stone_cnt -= 3;
		//	 }
		//	 P2Turn = 1;
		//	 P1Turn = 0;
		// }
		// else if (P2Pocket[4] == TRUE) {
		//	 movePocket = 4;
		//	 if (Stone_cnt > 0) {
		//		 StonePocket[7 + movePocket] += Stone_cnt;
		//		 P2BigPocket++;
		//		 StonePocket[0] += Stone_cnt;
		//		 StonePocket[1] += Stone_cnt;
		//		 Stone_cnt -= 4;
		//	 }
		//	 P2Turn = 0;
		//	 P1Turn = 1;
		// }
		// else if (P2Pocket[5] == TRUE) {
		//	 movePocket = 5;
		//	 if (Stone_cnt > 0) {
		//		 P2BigPocket++;
		//		 StonePocket[0] += Stone_cnt;
		//		 StonePocket[1] += Stone_cnt;
		//		 StonePocket[2] += Stone_cnt;
		//		 Stone_cnt -= 5;
		//	 }
		//	 P2Turn = 0;
		//	 P1Turn = 1;
		// }

	 //}

	return this;
}

void Mankara::Draw()const
{
	DrawGraph(0, 0, Background, TRUE);
	DrawGraph(30,30,Board,TRUE);

	// 石（赤）の初期配置
	for (int i = 0; i < 6; i++) {
		DrawGraph(300 + i * 125, 430, gStone.img[0][i], TRUE);

	}
	DrawGraph(300, 160, gStone.img[0][6], TRUE);
	DrawGraph(300 + 125, 160, gStone.img[0][7], TRUE);

	// 石（青）の初期配置
	for (int i = 0; i < 6; i++) {
		DrawGraph(300 + i * 125, 460, gStone.img[1][i], TRUE);
	}
	DrawGraph(300, 190, gStone.img[1][6], TRUE);
	DrawGraph(300 + 125, 190, gStone.img[1][7], TRUE);

	// 石（緑）の初期配置
	for (int i = 0; i < 6; i++) {
		DrawGraph(300 + i * 125, 490, gStone.img[2][i], TRUE);
	}
	DrawGraph(300+125*2, 160, gStone.img[2][6], TRUE);
	DrawGraph(300 + 125*3, 160, gStone.img[2][7], TRUE);

	// 石（黄）の初期配置
	for (int i = 0; i < 6; i++) {
		DrawGraph(300 + i * 125, 520, gStone.img[3][i], TRUE);
	}
	DrawGraph(300+125*2, 190, gStone.img[3][6], TRUE);
	DrawGraph(300 + 125*3, 190, gStone.img[3][7], TRUE);

	// 石（紫）の初期配置
	for (int i = 0; i < 6; i++) {
		DrawGraph(300 + i * 125, 100, gStone.img[4][i], TRUE);
	}
	DrawGraph(300 + 125 * 4, 190, gStone.img[4][6], TRUE);
	DrawGraph(300 + 125 * 5, 190, gStone.img[4][7], TRUE);

	// 石（白）の初期配置

	for (int i = 0; i < 6; i++) {
		DrawGraph(300 + i * 125, 130, gStone.img[5][i], TRUE);

	}
	DrawGraph(300 + 125 * 4, 160, gStone.img[5][6], TRUE);
	DrawGraph(300 + 125 * 5, 160, gStone.img[5][7], TRUE);

	

    // 1Pターン時のポケット移動
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
	
	// ターン切り替え
	if (P2Turn == 1 ) {
		DrawFormatString(200,200,GetColor(255,255,255),"2P TURN");
	}

	if (P1Turn == 1) {
		DrawFormatString(200, 200, GetColor(255, 255, 255), "1P TURN");
	}
	
	/*for (int y = StonePocket[PlayerPocket]; y > 0; y--) {
		StonePocket[PlayerPocket+y] += Stone_cnt;
		DrawGraph(300 + y * 125, 430, gStone.img[y][0], TRUE);

	}*/

	
}
