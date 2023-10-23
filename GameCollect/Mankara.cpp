#include "Mankara.h"
#include"DxLib.h"
#include"PadInput.h"
Mankara::Mankara()
{
	 RedStone = 1;
	 BlueStone = 1;
	 GreenStone - 1;
}

 AbstractScene* Mankara:: Update()
{
	
	return this;
}

void Mankara::Draw()const
{
	// 赤ストーンの移動
	if (CheckHitKey(KEY_INPUT_Q)) {
		DrawCircle(510, 490, 10, GetColor(255, 0, 0), RedStone);
		if (CheckHitKey(KEY_INPUT_W)) {
			DrawCircle(500+100, 500, 10, GetColor(255, 0, 0), RedStone);
		}
	}
	else {
		DrawCircle(500, 500, 10, GetColor(255, 0, 0), RedStone);

	}	

	 // 青ストーンの移動
	if (CheckHitKey(KEY_INPUT_Q)) {
		DrawCircle(515, 495, 10, GetColor(0, 0, 255), BlueStone);
		if (CheckHitKey(KEY_INPUT_W)) {
			DrawCircle(515+100, 515, 10, GetColor(0, 0, 255), BlueStone);
		}
	}
	else {
		DrawCircle(515, 515, 10, GetColor( 0, 0, 255), BlueStone);

	}

	// 緑ストーンの移動
	if (CheckHitKey(KEY_INPUT_Q)) {
		DrawCircle(505, 485, 10, GetColor(0, 255, 0), GreenStone);
		if (CheckHitKey(KEY_INPUT_W)) {
			DrawCircle(483+100, 483, 10, GetColor(0, 255, 0), GreenStone);
		}
	}
	else {
		DrawCircle(483, 483, 10, GetColor(0, 255, 0), GreenStone);

	}	
	
	
	
		


}
