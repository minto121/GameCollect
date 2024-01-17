#include "Mankara.h"
#include"DxLib.h"
#include"PadInput.h"
#include"GameSelect.h"
Mankara::Mankara()
{
	Board = LoadGraph("images/mancala/MancalaBoard.png");
	Background = LoadGraph("images/Mancala/BackGround02.png");

	// 0：未選択　１：選択した　２：相手のターン
	PocketEnter = 0; 

	MyTurn = TRUE;
	InputFlg = 0;
	// このフラグがTRUEなら、リザルト表示
	ResultFlg1 = FALSE;
	ResultFlg2 = FALSE;
	// TRUEなら、リザルト描画
	ResultDraw1 = FALSE;
	ResultDraw2 = FALSE;


	P1BigPocket = 0;
	P2BigPocket = 0;
	Pocket_cnt = 0;

	P1Pocket[0] = 1;
	P2Pocket[0] = 1;
	// 初期石
	InitialStone = 4;
	FullStone = 48;


	for (int y = 0; y < 6; y++) {
		P1Pocket[y] = 0;
	}

	for (int y = 0; y < 6; y++) {
		P2Pocket[y] = 0;
	}

	for (int pocket = 0; pocket < 6;) {
		P1StoneSave[pocket] = 4;
		P2StoneSave[pocket] = 4;
		pocket++;
	}
}

AbstractScene* Mankara::Update()
{

	if (ResultFlg1 == FALSE&&ResultFlg2 == FALSE) {
		// 自分のターンの操作
		if (MyTurn == TRUE) {
			// ポケットを選択したとき、ポケットの中の石が移動する
			if (PocketEnter == 0) {
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
		}

		if (MyTurn == FALSE) {
			// ポケットを選択したとき、ポケットの中の石が移動する
			if (PocketEnter == 0) {
				// ポケットの選択
				// 右に移動
				if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT)) {
					Pocket_cnt--;
					if (Pocket_cnt < 0) {
						Pocket_cnt = 5;

					}
				} // 左に移動
				else if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) {
					Pocket_cnt++;
					if (Pocket_cnt > 5) {
						Pocket_cnt = 0;
					}
				}
			}
		}
	}
	

	//1P用石の移動処理
	if (MyTurn == TRUE) {
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


	if (MyTurn == FALSE) {
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

	

	MoveStone();

	if (P1StoneSave[0] == 0 && P1StoneSave[1] == 0 && P1StoneSave[2] == 0 && P1StoneSave[3] == 0
		&& P1StoneSave[4] == 0 && P1StoneSave[5] == 0) {

		ResultFlg1 = TRUE;
	}
	if (P2StoneSave[0] == 0 && P2StoneSave[1] == 0 && P2StoneSave[2] == 0 && P2StoneSave[3] == 0
		&& P2StoneSave[4] == 0 && P2StoneSave[5] == 0) {

		ResultFlg2 = TRUE;
	}

	return this;
}

void Mankara::Draw()const
{
	DrawGraph(0, 0, Background, TRUE);
	DrawGraph(30, 30, Board, TRUE);

	// 1Pターン時の ポケット移動
	if (MyTurn == TRUE) {
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
	if (MyTurn == FALSE) {
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
	if (MyTurn == FALSE) {
		DrawFormatString(100, 30, GetColor(255, 0, 0), "2P TURN");
	}

	if (MyTurn == TRUE) {
		DrawFormatString(100, 30, GetColor(0, 0, 255), "1P TURN");
	}
	
	SetFontSize(50);

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

	

	SetFontSize(24);
	if (ResultDraw1 == TRUE) {
		if (P1BigPocket < P2BigPocket) {
			DrawBox(480, 250, 700, 400, GetColor(255, 255, 255), TRUE);
			DrawFormatString(500, 300, GetColor(255, 0, 0), "2P  WIN");
			DrawFormatString(500, 350, GetColor(0, 0, 0), "ESC：ゲーム終了");
		}
		else if (P1BigPocket > P1BigPocket) {
			DrawBox(480, 250, 700, 400, GetColor(255, 255, 255), TRUE);
			DrawFormatString(500, 300, GetColor(0, 0, 255), "1P  WIN");
			DrawFormatString(500, 350, GetColor(0, 0, 0), "ESC：ゲーム終了");
		}
	}

    if (ResultDraw2 == TRUE) {
		if (P1BigPocket < P2BigPocket) {
			DrawBox(480, 250, 700, 400, GetColor(255, 255, 255), TRUE);
			DrawFormatString(500, 300, GetColor(255, 0, 0), "2P  WIN");
			DrawFormatString(500, 350, GetColor(0, 0, 0), "ESC：ゲーム終了");
		}
		else if (P1BigPocket > P1BigPocket) {
			DrawBox(480, 250, 700, 400, GetColor(255, 255, 255), TRUE);
			DrawFormatString(500, 300, GetColor(0, 0, 255), "1P  WIN");
			DrawFormatString(500, 350, GetColor(0, 0, 0), "ESC：ゲーム終了");
		}
	}
}

void Mankara::MoveStone()
{
	if (ResultFlg1 == FALSE&& ResultFlg2 == FALSE) {
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
			InputFlg = TRUE;
		}

		if (MyTurn == TRUE && PAD_INPUT::OnRelease(XINPUT_BUTTON_A) && InputFlg == TRUE) {
			PocketEnter = 1;
			InputFlg = FALSE;
		}

		if (MyTurn == FALSE && PAD_INPUT::OnRelease(XINPUT_BUTTON_A) && InputFlg == TRUE) {
			PocketEnter = 1;
			InputFlg = FALSE;
		}
	}

	int tmp;
	int tmp2;

      /* 自分のターン中の処理 */
	if (MyTurn == TRUE && PocketEnter == 1&& P1Pocket[0] == TRUE) {
		tmp = P1StoneSave[0];
		// 1番目のポケットの中の数になるまで、iを足し続ける
		for (int i = 0; i < tmp;) {
			i++;

			P1StoneSave[i] += 1;
		}
		// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
		if (tmp >= 6) {
			P1BigPocket += 1;
			for (int i = 0; i < tmp; i++) {
				P2StoneSave[i - 6] += 1;
			}
		}
		// 移動が終わったので、石の数を０にする。
		P1StoneSave[0] = 0;
		PocketEnter = 2;
	}
	else if (MyTurn == TRUE && PocketEnter == 1 && P1Pocket[1] == TRUE) {
		tmp = P1StoneSave[1];
		// 2番目のポケットの中の数になるまで、iを足し続ける
		for (int i = 0; i < tmp; ) {
			i++;
			P1StoneSave[i+1] += 1;
		}

		// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
		if (tmp >= 5) {
			P1BigPocket += 1;
			for (int i = 0; i < tmp; i++) {
				P2StoneSave[i - 5] += 1;
			}
		}
		// 移動が終わったので、石の数を０にする。
		P1StoneSave[1] = 0;
		PocketEnter = 2;
	}
	else if (MyTurn == TRUE && PocketEnter == 1 && P1Pocket[2] == TRUE) {
		tmp = P1StoneSave[2];
		// 3番目のポケットの中の数になるまで、iを足し続ける
		for (int i = 0; i < tmp;) {
			i++;
			P1StoneSave[i+2] += 1;
		}
		// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
		if (tmp >= 4) {
			P1BigPocket += 1;
			for (int i = 0; i < tmp; i++) {
				P2StoneSave[i - 4] += 1;
			}
		}
		// 移動が終わったので、石の数を０にする。
		P1StoneSave[2] = 0;
		PocketEnter = 2;

	}
	else if (MyTurn == TRUE && PocketEnter == 1 && P1Pocket[3] == TRUE) {
		tmp = P1StoneSave[3];
		// 4番目のポケットの中の数になるまで、iを足し続ける
		for (int i = 0; i < tmp; ) {
			i++;
			P1StoneSave[i + 3] += 1;
		}
		// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
		if (tmp >= 3) {
			P1BigPocket += 1;
			for (int i = 0; i <tmp; i++) {
				P2StoneSave[i - 3] += 1;
			}
		}
		// 移動が終わったので、石の数を０にする。
		P1StoneSave[3] = 0;
		PocketEnter = 2;

	}
	else if (MyTurn == TRUE && PocketEnter == 1 && P1Pocket[4] == TRUE) {
		int tmp = P1StoneSave[4];
		// 5番目のポケットの中の数になるまで、iを足し続ける
		for (int i = 0; i < tmp; ) {
			i++;
			P1StoneSave[i+4] += 1;
		}
		// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
		if (tmp >= 2) {
			P1BigPocket += 1;
			for (int i = 0; i < tmp; i++) {
				P2StoneSave[i - 2] += 1;
			}
		}
		// 移動が終わったので、石の数を０にする。
		P1StoneSave[4] = 0;
		PocketEnter = 2;

	}
	else if (MyTurn == TRUE && PocketEnter == 1 && P1Pocket[5] == TRUE) {
		tmp = P1StoneSave[5];
		// 6番目のポケットの中の数になるまで、iを足し続ける
		for (int i = 0; i < tmp; ) {
			i++;
			P1StoneSave[i+5] += 1;
		}
		// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
		if (tmp >= 1) {
			P1BigPocket += 1;

			for (int i = 0; i < tmp; i++) {
				P2StoneSave[i - 1] += 1;
			}
		}
		// 移動が終わったので、石の数を０にする。
		P1StoneSave[5] = 0;
		PocketEnter = 2;
	}



        /* 相手のターン中の処理 */
	if (MyTurn == FALSE && PocketEnter == 1&& P2Pocket[0] == TRUE) {
		tmp2 = P2StoneSave[0];
		// 1番目のポケットの中の数になるまで、iを足し続ける
		for (int i = 0; i < tmp2; ) {
			i++;
			P2StoneSave[i] += 1;
		}
		// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
		if (tmp2 >= 6) {
			P2BigPocket += 1;
			for (int i = 0; i < tmp2; i++) {
				P1StoneSave[i - 6] += 1;
			}
		}
		// 移動が終わったので、石の数を０にする。
		P2StoneSave[0] = 0;
		PocketEnter = 2;
	}
	else if (MyTurn == FALSE && PocketEnter == 1 && P2Pocket[1] == TRUE) {
		tmp2 = P2StoneSave[1];
		// 2番目のポケットの中の数になるまで、iを足し続ける
		for (int i = 0; i < tmp2; ) {
			i++;
			P2StoneSave[i + 1] += 1;
		}
		// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
		if (tmp2 >= 5) {
			P2BigPocket += 1;
			for (int i = 5; i < tmp2 ; i++) {
				P1StoneSave[i - 5] += 1;
			}

		}
		// 移動が終わったので、石の数を０にする。
		P2StoneSave[1] = 0;
		PocketEnter = 2;
	}
	else if (MyTurn == FALSE && PocketEnter == 1 && P2Pocket[2] == TRUE) {
		tmp2 = P2StoneSave[2];
		// 3番目のポケットの中の数になるまで、iを足し続ける
		for (int i = 0; i < tmp2; ) {
			i++;
			P2StoneSave[i + 2] += 1;
		}
		// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
		if (tmp2 >= 4) {
			P2BigPocket += 1;
			for (int i = 4; i < tmp2 ; i++) {
				P1StoneSave[i - 4] += 1;
			}
		}
		// 移動が終わったので、石の数を０にする。
		P2StoneSave[2] = 0;
		PocketEnter = 2;

	}
	else if (MyTurn == FALSE && PocketEnter == 1 && P2Pocket[3] == TRUE) {
		int tmp2 = P2StoneSave[3];
		// 4番目のポケットの中の数になるまで、iを足し続ける
		for (int i = 0; i < tmp2; ) {
			i++;
			P2StoneSave[i + 3] += 1;
		}
		// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
		if (tmp2 >= 3) {
			P2BigPocket += 1;
			for (int i = 3; i < tmp2 ; i++) {
				P1StoneSave[i - 3] += 1;
			}

		}
		// 移動が終わったので、石の数を０にする。
		P2StoneSave[3] = 0;
		PocketEnter = 2;

	}
	else if (MyTurn == FALSE && PocketEnter == 1 && P2Pocket[4] == TRUE) {
		tmp2 = P2StoneSave[4];
		// 5番目のポケットの中の数になるまで、iを足し続ける
		for (int i = 0; i < tmp2; ) {
			i++;
			P2StoneSave[i + 4] += 1;
		}
		// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
		if (tmp2 >= 2) {
			P2BigPocket += 1;
			for (int i = 2; i < tmp2; i++) {
				P1StoneSave[i - 2] += 1;
			}
		}
		// 移動が終わったので、石の数を０にする。
		P2StoneSave[4] = 0;
		PocketEnter = 2;

	}
	else if (MyTurn == FALSE && PocketEnter == 1 && P2Pocket[5] == TRUE) {
		tmp2 = P2StoneSave[5];
		// 6番目のポケットの中の数になるまで、iを足し続ける
		for (int i = 0; i < tmp2; ) {
			i++;
			P2StoneSave[i + 5] += 1;
		}
		// 石の数がポケットの数より多い時は、bigpocketに１プラスする。
		if (tmp2 >= 1) {
			P2BigPocket += 1;
			for (int i = 1; i < tmp2; i++) {
				P1StoneSave[i - 1] += 1;
			}
		}
		// 移動が終わったので、石の数を０にする。
		P2StoneSave[5] = 0;
		PocketEnter = 2;
	}


	// PocketEnterが２になら、ターンを切り替える
	if ( PocketEnter == 2) {
		// 自分のターンなら、MyTurnをFALSEにする
		if (MyTurn == TRUE) {
			MyTurn = FALSE;
			PocketEnter = 0;
		}
		// 相手のターンなら、MyturnをTRUEにする
		else if(MyTurn == FALSE) {
			MyTurn = TRUE;
			PocketEnter = 0;
		}
	}


	// 勝敗結果の表示
	if (ResultFlg1== TRUE) {
		for (int i = 0; i < P2StoneSave[i]; i++) {
			P2BigPocket += P2StoneSave[i];
			P2StoneSave[i] = 0;
		}
		ResultDraw1 = TRUE;
	}
	else if (ResultFlg2 == TRUE) {
		for (int i = 0; i < P1StoneSave[i]; i++) {
			P1BigPocket += P1StoneSave[i];
			P1StoneSave[i] = 0;
		}
		ResultDraw2 = TRUE;
	}
}

