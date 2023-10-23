#include "Mankara.h"
#include"DxLib.h"
#include"PadInput.h"
Mankara::Mankara()
{
	 RedStone = 1;
	 BlueStone = 1;
	 GreenStone = 1;
	 YellowStone = 1;

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
	
	return this;
}

void Mankara::Draw()const
{

	DrawCircle(400, 500, 50, GetColor(255, 0, 0),Pocket1);
	DrawCircle(500, 500, 50, GetColor(255, 0, 0),Pocket2);
	DrawCircle(600, 500, 50, GetColor(255, 0, 0),Pocket3);
	DrawCircle(700, 500, 50, GetColor(255, 0, 0),Pocket4);
	DrawCircle(800, 500, 50, GetColor(255, 0, 0),Pocket5);
	DrawCircle(900, 500, 50, GetColor(255, 0, 0),Pocket6);
	
	DrawCircle(400, 300, 50, GetColor(255, 0, 0),Pocket7);
	DrawCircle(500, 300, 50, GetColor(255, 0, 0),Pocket8);
	DrawCircle(600, 300, 50, GetColor(255, 0, 0),Pocket9);
	DrawCircle(700, 300, 50, GetColor(255, 0, 0),Pocket10);
	DrawCircle(800, 300, 50, GetColor(255, 0, 0),Pocket11);
	DrawCircle(900, 300, 50, GetColor(255, 0, 0),Pocket12);


	// 赤ストーン
	if (CheckHitKey(KEY_INPUT_Q)) {
		if (CheckHitKey(KEY_INPUT_W)) {
			DrawCircle(510, 490, 10, GetColor(255, 0, 0), FALSE,RedStone);

		}else
		DrawCircle(510, 490, 10, GetColor(255, 0, 0), RedStone);
		
	}
	else {
		DrawCircle(500, 500, 10, GetColor(255, 0, 0), RedStone);

	}	

	 // 青ストーン
	if (CheckHitKey(KEY_INPUT_Q)) {
		if (CheckHitKey(KEY_INPUT_W)) {
			DrawCircle(515, 495, 10, GetColor(0, 0, 255),FALSE, BlueStone);
		}
		else
		DrawCircle(515, 495, 10, GetColor(0, 0, 255), BlueStone);
	}
	else {
		DrawCircle(500, 515, 10, GetColor( 0, 0, 255), BlueStone);

	}

	// 緑ストーン
	if (CheckHitKey(KEY_INPUT_Q)) {
		if (CheckHitKey(KEY_INPUT_W)) {
			DrawCircle(505, 485, 10, GetColor(0, 255, 0), FALSE, GreenStone);
		}
		else
		DrawCircle(505, 485, 10, GetColor(0, 255, 0), GreenStone);
	}
	else {
		DrawCircle(500, 525, 10, GetColor(0, 255, 0), GreenStone);

	}	
	
	// 黄ストーン
	if (CheckHitKey(KEY_INPUT_Q)) {
		if (CheckHitKey(KEY_INPUT_W)) {
			DrawCircle(495, 480, 10, GetColor(255, 255, 0), FALSE,YellowStone);

		}else
		DrawCircle(495, 480, 10, GetColor(255, 255, 0), YellowStone);
	}
	else {
		DrawCircle(500, 535, 10, GetColor(255, 255, 0), YellowStone);

	}

	// ストーンの移動

	if (CheckHitKey(KEY_INPUT_Q)) {
		if (CheckHitKey(KEY_INPUT_W)) {
			DrawCircle(500 + 100, 500, 10, GetColor(255, 0, 0), RedStone);
			DrawCircle(500 + 200, 500, 10, GetColor(0, 0, 255), BlueStone);
			DrawCircle(500 + 300, 500, 10, GetColor(0, 255, 0), GreenStone);
			DrawCircle(500 + 400, 500, 10, GetColor(255, 255, 0), YellowStone);
		}
	}
		


}
