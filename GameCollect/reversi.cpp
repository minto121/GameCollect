#include "Reversi.h"
#include<DxLib.h>
#include "PadInput.h"

#define WALL 0
#define WHITE 1
#define BLACK 2

Reversi::Reversi()
{
	R_Img = LoadGraph("images/Reversi/banmen.png");
	B_Storn_Img = LoadGraph("images/Reversi/osero(black).png");
	W_Storn_Img = LoadGraph("images/Reversi/osero(white).png");
	XOnce = TRUE;
	XOnce = TRUE;
	/*CursorPoint = { 0, 0 };*/

	K_Flg = FALSE;

	board();

}

Reversi::~Reversi()
{
}

void Reversi::board()
{

	for (int x = 0; x < 10;x++) {
		for (int y = 0; y < 10; y++) {
			Boa.typ[x][y] = 0;
			Boa.x[x][y] = 0;
			Boa.y[x][y] = 0;
		}
	}

	Boa.typ[3][3] = 1;
	Boa.x[3][3] = 3 * 100;
	Boa.y[3][3] = 3 * 100;

	Boa.typ[4][4] = 1;
	Boa.x[4][4] = 4 * 100;
	Boa.y[4][4] = 4 * 100;

	Boa.typ[3][4] = 2;
	Boa.x[3][4] = 4 * 100;
	Boa.y[3][4] = 4 * 100;

	Boa.typ[4][3] = 2;
	Boa.x[4][3] = 4 * 100;
	Boa.y[4][3] = 3 * 100;
}



AbstractScene* Reversi::Update()
{

	disp();
	board();
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
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) || CheckHitKey(KEY_INPUT_0)) {
		K_Flg = TRUE;

		if (WHITE)
		{
			DrawGraph(0, 0, W_Storn_Img, TRUE);
		}
		else if (BLACK)
		{
			DrawGraph(0, 0, B_Storn_Img, TRUE);
		}
	}
}

void Reversi::Draw() const
{
	DrawFormatString(0, 100, GetColor(255, 255, 255), " %d:button", K_Flg);
	//駒の描画
	if (K_Flg == TRUE)
	{
		DrawGraph(0, 0, W_Storn_Img, TRUE);
	}

	//盤面の描画
	DrawGraph(340, 50, R_Img, TRUE);

}

