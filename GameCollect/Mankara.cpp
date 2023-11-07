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

	for (int y = 0; y < 6; y++) {
		P1Pocket[y]+=1;
	}

	for (int y = 0; y < 6; y++) {
		P2Pocket[y]+=1;
	}

}

 AbstractScene* Mankara:: Update()
{

	 /****************************
	 * プレイヤー行動制限
	 *****************************/ 
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

	 /****************************
	* プレイヤーポケット選択
	*****************************/
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

	 /****************************
	* プレイヤー 石の移動処理
	*****************************/
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

	DrawGraph(300, 430, StoneImg[0], TRUE);
	DrawGraph(300, 450, StoneImg[1], TRUE);
	DrawGraph(300, 470, StoneImg[2], TRUE);
	DrawGraph(300, 490, StoneImg[3], TRUE);
	DrawGraph(300, 510, StoneImg[4], TRUE);
	DrawGraph(300, 530, StoneImg[5], TRUE);

    // 1Pターン時のポケット移動
	if (P1Turn == 1) {
			if (Pocket_cnt == 1) {
				DrawBox(385, 385, 485, 600, GetColor(255, 0, 0), FALSE);
				
			}
			else if (Pocket_cnt == 2) {
				DrawBox(385 + 100, 385, 485 + 100, 600, GetColor(255, 0, 0), FALSE);

			}else if (Pocket_cnt == 3) {
				DrawBox(385 + 200, 385, 485 + 200, 600, GetColor(255, 0, 0), FALSE);

			}else if (Pocket_cnt == 4) {
				DrawBox(385 + 300, 385, 485 + 300, 600, GetColor(255, 0, 0), FALSE);

			}else if (Pocket_cnt == 5) {
				DrawBox(385 + 400, 385, 485 + 400, 600, GetColor(255, 0, 0), FALSE);

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
			DrawFormatString(100, 100, GetColor(255, 255, 255),"1P TRUE");
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
