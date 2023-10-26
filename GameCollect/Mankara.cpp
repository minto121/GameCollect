#include "Mankara.h"
#include"DxLib.h"
#include"PadInput.h"
Mankara::Mankara()
{
	/* RedStone = 1;
	 BlueStone = 1;
	 GreenStone = 1;
	 YellowStone = 1;*/

	for (int i = 0; i < 8; i++) {
		redStone[i];
	}

	for (int i = 0; i < 8; i++) {
		blueStone[i];
	}

	for (int i = 0; i < 8; i++) {
		greenStone[i];
	}

	for (int i = 0; i < 8; i++) {
		yellowStone[i];
	}
	
	for (int i = 0; i < 8; i++) {
		purpleStone[i];
	}
	
	for (int i = 0; i < 8; i++) {
		whiteStone[i];
	}



	for (int y = 0; y < 6; y++) {
		P1Pocket[y];
	}

	for (int y = 0; y < 6; y++) {
		P2Pocket[y];
	}

	 Pocket1 = 0;
	 Pocket2 = 0;
	 Pocket3 = 0;
	 Pocket4 = 0;
	 Pocket5 = 0;
	 Pocket6 = 0; 
	 
	 Pocket7 = 0;
	 Pocket8 = 0;
	 Pocket9 = 0;
	 Pocket10 = 0;
	 Pocket11 = 0;
	 Pocket12 = 0;

	
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

	return this;
}

void Mankara::Draw()const
{
	// ターン切り替え
	if (P2Turn == 1 ) {
		DrawFormatString(200,200,GetColor(255,255,255),"2P TURN");
	}

	if (P1Turn == 1) {
		DrawFormatString(200, 200, GetColor(255, 255, 255), "1P TURN");
	}

	DrawCircle(400, 500, 50, GetColor(255, 200, 255),P1Pocket[0]);
	DrawCircle(500, 500, 50, GetColor(255, 200, 255),P1Pocket[1]);
	DrawCircle(600, 500, 50, GetColor(255, 200, 255),P1Pocket[2]);
	DrawCircle(700, 500, 50, GetColor(255, 200, 255),P1Pocket[3]);
	DrawCircle(800, 500, 50, GetColor(255, 200, 255),P1Pocket[4]);
	DrawCircle(900, 500, 50, GetColor(255, 200, 255),P1Pocket[5]);
	
	DrawCircle(400, 300, 50, GetColor(255, 200, 255),P2Pocket[0]);
	DrawCircle(500, 300, 50, GetColor(255, 200, 255),P2Pocket[1]);
	DrawCircle(600, 300, 50, GetColor(255, 200, 255),P2Pocket[2]);
	DrawCircle(700, 300, 50, GetColor(255, 200, 255),P2Pocket[3]);
	DrawCircle(800, 300, 50, GetColor(255, 200, 255),P2Pocket[4]);
	DrawCircle(900, 300, 50, GetColor(255, 200, 255),P2Pocket[5]);


	// 赤ストーン初期配置
	DrawCircle(500 + 100, 500, 10, GetColor(255, 0, 0), redStone[0]);
	DrawCircle(500 + 200, 500, 10, GetColor(255, 0, 0), redStone[1]);
	DrawCircle(500 + 300, 500, 10, GetColor(255, 0, 0), redStone[2]);
	DrawCircle(500 + 400, 500, 10, GetColor(255, 0, 0), redStone[3]);

	DrawCircle(500 - 100, 500, 10, GetColor(255, 0, 0), redStone[4]);
	DrawCircle(500 - 100, 500-200, 10, GetColor(255, 0, 0), redStone[5]);
	DrawCircle(500 , 500 - 200, 10, GetColor(255, 0, 0), redStone[6]);
	
	if (P1Turn == 1) {


		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {
				DrawCircle(510, 490, 10, GetColor(255, 0, 0), FALSE, RedStone);
			}else {
				DrawCircle(510, 490, 10, GetColor(255, 0, 0), RedStone);
			}
		}
		else {
			DrawCircle(500, 500, 10, GetColor(255, 0, 0), RedStone);
		}
		
	}else if (P1Turn == 0) {
	
		DrawCircle(500, 500, 10, GetColor(255, 0, 0), RedStone);
	}


	 // 青ストーン初期配置
	
	DrawCircle(500 + 100, 515, 10, GetColor(0, 0, 255), blueStone[0]);
	DrawCircle(500 + 200, 515, 10, GetColor(0, 0, 255), blueStone[1]);
	DrawCircle(500 + 300, 515, 10, GetColor(0, 0, 255), blueStone[2]);
	DrawCircle(500 + 400, 515, 10, GetColor(0, 0, 255), blueStone[3]);

	DrawCircle(500 - 100, 515 - 200, 10, GetColor(0, 0, 255), blueStone[4]);
	DrawCircle(500 + 200, 515 - 200, 10, GetColor(0, 0, 255), blueStone[5]);
	DrawCircle(500 + 300, 515 - 200, 10, GetColor(0, 0, 255), blueStone[6]);
	DrawCircle(500 + 400, 515 - 200, 10, GetColor(0, 0, 255), blueStone[7]);

	if (P1Turn == 1) {

		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {
				DrawCircle(515, 495, 10, GetColor(0, 0, 255), FALSE, BlueStone);
			}else {
				DrawCircle(515, 495, 10, GetColor(0, 0, 255), BlueStone);
			}
		}else {
			DrawCircle(500, 515, 10, GetColor(0, 0, 255), BlueStone);
		}

	}else if (P1Turn == 0) {
		DrawCircle(500, 515, 10, GetColor(0, 0, 255), BlueStone);
		
	}
	

	// 緑ストーン初期配置

	DrawCircle(500 + 100, 525, 10, GetColor(0, 255, 0), greenStone[0]);
	DrawCircle(500 + 200, 525, 10, GetColor(0, 255, 0), greenStone[1]);
	DrawCircle(500 + 300, 525, 10, GetColor(0, 255, 0), greenStone[2]);
	DrawCircle(500 + 400, 525, 10, GetColor(0, 255, 0), greenStone[3]);	

	DrawCircle(500 - 100, 525, 10, GetColor(0, 255, 0), greenStone[4]);
	DrawCircle(500 + 200, 525 - 200, 10, GetColor(0, 255, 0), greenStone[5]);
	DrawCircle(500 + 300, 525 - 200, 10, GetColor(0, 255, 0), greenStone[6]);
	DrawCircle(500 + 400, 525 - 200, 10, GetColor(0, 255, 0), greenStone[7]);

	if (P1Turn == 1) {

		if (PAD_INPUT::OnPressed(XINPUT_BUTTON_A)) {

			if (PAD_INPUT::OnPressed(XINPUT_BUTTON_B)) {
				DrawCircle(505, 485, 10, GetColor(0, 255, 0), FALSE, GreenStone);
			}
			else {
				DrawCircle(505, 485, 10, GetColor(0, 255, 0), GreenStone);
			}
		}else {
			DrawCircle(500, 525, 10, GetColor(0, 255, 0), GreenStone);
		}
		
	}else if (P1Turn == 0) {

		DrawCircle(500, 525, 10, GetColor(0, 255, 0), GreenStone);
	}


	// 黄ストーン 初期配置
	
	
	DrawCircle(500 + 100, 535, 10, GetColor(255, 255, 0), yellowStone[0]);
	DrawCircle(500 + 200, 535, 10, GetColor(255, 255, 0), yellowStone[1]);
	DrawCircle(500 + 300, 535, 10, GetColor(255, 255, 0), yellowStone[2]);
	DrawCircle(500 + 400, 535, 10, GetColor(255, 255, 0), yellowStone[3]);
	
	DrawCircle(500 - 100, 535, 10, GetColor(255, 255, 0), yellowStone[4]);
	DrawCircle(500 + 200, 535 - 200, 10, GetColor(255, 255, 0), yellowStone[5]);
	DrawCircle(500 + 300, 535 - 200, 10, GetColor(255, 255, 0), yellowStone[6]);
	DrawCircle(500 + 400, 535 - 200, 10, GetColor(255, 255, 0), yellowStone[7]);

	if (P1Turn == 1) {

		if (PAD_INPUT::OnPressed(XINPUT_BUTTON_A)) {
			if (PAD_INPUT::OnPressed(XINPUT_BUTTON_B)) {
				DrawCircle(495, 480, 10, GetColor(255, 255, 0), FALSE, YellowStone);
			}else {
				DrawCircle(495, 480, 10, GetColor(255, 255, 0), YellowStone);
			}		
		}else {
			DrawCircle(500, 535, 10, GetColor(255, 255, 0), YellowStone);
		}
	}else if (P1Turn == 0) {

		DrawCircle(500, 535, 10, GetColor(255, 255, 0), YellowStone);
	}


	// 紫ストーン
	DrawCircle(500 + 100, 545-200, 10, GetColor(255, 0, 255), purpleStone[0]);
	DrawCircle(500 + 200, 545-200, 10, GetColor(255, 0, 255), purpleStone[1]);
	DrawCircle(500 + 300, 545-200, 10, GetColor(255, 0, 255), purpleStone[2]);
	DrawCircle(500 + 400, 545-200, 10, GetColor(255, 0, 255), purpleStone[3]);

	DrawCircle(500 - 100, 545, 10, GetColor(255, 0, 255), purpleStone[4]);
	DrawCircle(500 + 100, 545 - 200, 10, GetColor(255, 0, 255), purpleStone[5]);
	DrawCircle(500 + 200, 545 - 200, 10, GetColor(255, 0, 255), purpleStone[6]);
	DrawCircle(500 + 300, 545 - 200, 10, GetColor(255, 0, 255), purpleStone[7]);


	// 白ストーン
	DrawCircle(500 , 545 - 200, 10, GetColor(255, 255, 255), whiteStone[0]);
	DrawCircle(500 , 525 - 200, 10, GetColor(255, 255, 255), whiteStone[1]);
	DrawCircle(500 + 100, 535 - 200, 10, GetColor(255, 255, 255), whiteStone[2]);
	DrawCircle(500 + 100, 525 - 200, 10, GetColor(255, 255, 255), whiteStone[3]);

	DrawCircle(500, 535-200, 10, GetColor(255, 255, 255), whiteStone[4]);
	DrawCircle(500 - 100, 525 - 200, 10, GetColor(255, 255, 255), whiteStone[5]);
	DrawCircle(500 - 100, 545 - 200, 10, GetColor(255, 255, 255), whiteStone[6]);
	DrawCircle(500 + 100, 505 - 200, 10, GetColor(255, 255, 255), whiteStone[7]);


	if (P1Turn == 1) {
		// ポケットの移動
		if (CheckHitKey(KEY_INPUT_E)) {
			DrawCircle(400 + 100, 500, 60, GetColor(255, 255, 0), FALSE);
		}
		else {
			DrawCircle(400, 500, 60, GetColor(255, 255, 0), FALSE);

		}
	}


	// ストーンの移動
	if (P1Turn == 1) {
		if (CheckHitKey(KEY_INPUT_Q)) {
			if (CheckHitKey(KEY_INPUT_W)) {
				DrawCircle(500 + 100, 480, 10, GetColor(255, 0, 0), RedStone);
				DrawCircle(500 + 200, 480, 10, GetColor(0, 0, 255), BlueStone);
				DrawCircle(500 + 300, 480, 10, GetColor(0, 255, 0), GreenStone);
				DrawCircle(500 + 400, 480, 10, GetColor(255, 255, 0), YellowStone);
			}
		}
	}
	
}
