#include "Reversi.h"
#include<DxLib.h>
#include "PadInput.h"

Reversi::Reversi()
{
	/*R_Img = LoadGraph("images/Reversi/banmen.png");*/
	B_Rock_Img = LoadGraph("images/Reversi/osero(black).png");
	W_Rock_Img = LoadGraph("images/Reversi/osero(white).png");
	XOnce = TRUE;
	XOnce = TRUE;
	/*CursorPoint = { 0, 0 };*/

	K_Flg = FALSE;

	

}

Reversi::~Reversi()
{
}

void Reversi::board()
{

}



AbstractScene* Reversi::Update()
{

	disp();
	////カーソルを上移動させる
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP) || (PAD_INPUT::GetLStick().ThumbY > 10000 && YOnce == TRUE)) {

	//	//連続入力しないようにする
	//	YOnce = FALSE;

	//	//カーソルがはみ出ないように調整する
	//	if (--CursorPoint.y < 0) {
	//		if (CursorPoint.x == 10) {
	//			CursorPoint.y = 3;
	//		}
	//		else {
	//			CursorPoint.y = 4;
	//		}
	//		if (CursorPoint.x == 12) {
	//			CursorPoint.x = 11;
	//		}
	//	}
	//}

	////カーソルを下移動させる
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN) || (PAD_INPUT::GetLStick().ThumbY < -10000 && YOnce == TRUE)) {

	//	//連続入力しないようにする
	//	YOnce = FALSE;

	//	

	//	//カーソルがはみ出ないように調整する
	//	if (++CursorPoint.y > 3 && CursorPoint.x == 10 || CursorPoint.y > 4) {
	//		CursorPoint.y = 0;
	//	}
	//	if (CursorPoint.y > 3 && CursorPoint.x == 12) {
	//		CursorPoint.x = 11;
	//	}

	//}

	////カーソルを右移動させる
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT) || (PAD_INPUT::GetLStick().ThumbX > 10000 && XOnce == TRUE)) {

	//	//連続入力しないようにする
	//	XOnce = FALSE;

	//

	//	//カーソルがはみ出ないように調整する
	//	if (++CursorPoint.x == 10 && CursorPoint.y > 3)
	//	{
	//		CursorPoint.x = 11;
	//	}
	//	if (CursorPoint.x > 11 && CursorPoint.y == 4) {
	//		CursorPoint.x = 0;
	//	}
	//	if (CursorPoint.x > 12) {
	//		CursorPoint.x = 0;
	//	}
	//}

	////カーソルを左移動させる
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT) || (PAD_INPUT::GetLStick().ThumbX < -10000 && XOnce == TRUE)) {

	//	//連続入力しないようにする
	//	XOnce = FALSE;

	//	//カーソルがはみ出ないように調整する
	//	if (--CursorPoint.x < 0) {
	//		if (CursorPoint.y > 3) {
	//			CursorPoint.x = 11;
	//		}
	//		else {
	//			CursorPoint.x = 12;
	//		}
	//	}
	//	if (CursorPoint.x == 10 && CursorPoint.y == 4)
	//	{
	//		CursorPoint.x = 9;
	//	}
	//}

	////Aボタンが押されたら
	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
	//}
	return this;
}

void Reversi::disp()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		K_Flg = TRUE;
		/*switch(order) 
		{
			case Order::First;
			DrawGraph(0, 0, B_Rock_Img, TRUE);
			break;

		}*/
	}
}

void Reversi::Draw() const
{
	DrawFormatString(0, 100, GetColor(255, 255, 255), " %d:button", K_Flg);
	//駒の描画
	if (K_Flg == TRUE)
	{
		DrawGraph(0, 0, W_Rock_Img, TRUE);
	}

	//盤面の描画
	DrawGraph(340, 50, R_Img, TRUE);


}

