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
	
	Stone[i][j];
	P1Pocket[0] = 1;
	P2Pocket[0] = 1;
	RINE = 1;
	Pocket1[i][j];

	Stone_cnt = 4;

	for (int y = 0; y < 6; y++) {
		P1Pocket[y]+=1;
	}

	for (int y = 0; y < 6; y++) {
		P2Pocket[y]+=1;
	}

	for (int i = 0; i < 8; i++) {
		gStone.redimg[i] = StoneImg[1];
	}

	for (int i = 0; i < 8; i++) {
		gStone.blueimg[i] = StoneImg[5];
		
	}

	for (int i = 0; i < 8; i++) {
		gStone.greenimg[i] = StoneImg[3];
	}

	for (int i = 0; i < 8; i++) {
		gStone.yellowimg[i] = StoneImg[0];
	}

	for (int i = 0; i < 8; i++) {
		gStone.purpleimg[i] = StoneImg[2];
	}

	for (int i = 0; i < 8; i++) {
		gStone.whiteimg[i] = StoneImg[4];
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

	 
	return this;
}

void Mankara::Draw()const
{
	DrawGraph(0, 0, Background, TRUE);
	DrawGraph(30,30,Board,TRUE);
	for (int i = 0; i < 6; i++) {
		DrawGraph(300 + i * 125, 430, gStone.redimg[i], TRUE);

	}
	DrawGraph(300, 160, gStone.redimg[6], TRUE);
	DrawGraph(300 + 125, 160, gStone.redimg[7], TRUE);


	for (int i = 0; i < 6; i++) {
		DrawGraph(300 + i * 125, 460, gStone.blueimg[i], TRUE);
	}
	DrawGraph(300, 190, gStone.blueimg[6], TRUE);
	DrawGraph(300 + 125, 190, gStone.blueimg[7], TRUE);


	for (int i = 0; i < 6; i++) {
		DrawGraph(300 + i * 125, 490, gStone.greenimg[i], TRUE);
	}
	DrawGraph(300+125*2, 160, gStone.greenimg[6], TRUE);
	DrawGraph(300 + 125*3, 160, gStone.greenimg[7], TRUE);


	for (int i = 0; i < 6; i++) {
		DrawGraph(300 + i * 125, 520, gStone.yellowimg[i], TRUE);
	}
	DrawGraph(300+125*2, 190, gStone.yellowimg[6], TRUE);
	DrawGraph(300 + 125*3, 190, gStone.yellowimg[7], TRUE);


	for (int i = 0; i < 6; i++) {
		DrawGraph(300 + i * 125, 100, gStone.purpleimg[i], TRUE);
	}
	DrawGraph(300 + 125 * 4, 190, gStone.purpleimg[6], TRUE);
	DrawGraph(300 + 125 * 5, 190, gStone.purpleimg[7], TRUE);


	for (int i = 0; i < 6; i++) {
		DrawGraph(300 + i * 125, 130, gStone.whiteimg[i], TRUE);

	}
	DrawGraph(300 + 125 * 4, 160, gStone.whiteimg[6], TRUE);
	DrawGraph(300 + 125 * 5, 160, gStone.whiteimg[7], TRUE);

	

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
	

	for (int i = 0; i < 6; i++) {
		DrawFormatString(700 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", P1Pocket[i]);
		DrawFormatString(900 + 50 * i, 100 + 50 * i, GetColor(255, 255, 255), "%d", P2Pocket[i]);
	}
	
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
			DrawFormatString(100, 100, GetColor(255, 0, 0), "1P TRUE");

		}
		else if (P1Pocket[2] == TRUE) {
			DrawFormatString(100, 100, GetColor(0, 255, 0), "1P TRUE");

		}
		else if (P1Pocket[3] == TRUE) {
			DrawFormatString(100, 100, GetColor(0, 0, 255), "1P TRUE");

		}
		else if (P1Pocket[4] == TRUE) {
			DrawFormatString(100, 100, GetColor(255, 255, 0), "1P TRUE");

		}
		else if (P1Pocket[5] == TRUE) {
			DrawFormatString(100, 100, GetColor(255, 0, 255), "1P TRUE");

		}
		else if (P1Pocket[6] == TRUE) {
			DrawFormatString(100, 100, GetColor(0, 255, 255), "1P TRUE");

		}

	} 
	
	// ２P用石の移動

	if (P2Turn == 1) {

		if (P2Pocket[0] == TRUE) {
			DrawFormatString(100, 100, GetColor(255, 255, 255), "2P TRUE");

		}
		else if (P2Pocket[1] == TRUE) {
			DrawFormatString(100, 100, GetColor(255, 0, 0), "2P TRUE");

		}
		else if (P2Pocket[2] == TRUE) {
			DrawFormatString(100, 100, GetColor(0, 255, 0), "2P TRUE");

		}
		else if (P2Pocket[3] == TRUE) {
			DrawFormatString(100, 100, GetColor(0, 0, 255), "2P TRUE");

		}
		else if (P2Pocket[4] == TRUE) {
			DrawFormatString(100, 100, GetColor(255, 255, 0), "2P TRUE");

		}
		else if (P2Pocket[5] == TRUE) {
			DrawFormatString(100, 100, GetColor(255, 0, 255), "2P TRUE");

		}
		else if (P2Pocket[6] == TRUE) {
			DrawFormatString(100, 100, GetColor(0, 255, 255), "2P TRUE");

		}
	}
	
}
