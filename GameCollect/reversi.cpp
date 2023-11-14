#include "Reversi.h"
#include<DxLib.h>
#include "PadInput.h"

#define WALL 0;
#define WHITE 1;
#define BLACK 2;

#define SCREEN_HEIGHT 720	//画面サイズ (縦)
#define SCREEN_WIDTH 1280	//画面サイズ (横)

//盤面
#define SIZ 8
#define BOARD_IMG_SIZE 640


Reversi::Reversi()
{
	Bac = LoadGraph("images/Reversi/banmen_4.png");
	Bla = LoadGraph("images/Reversi/osero(black).png");
	Whi= LoadGraph("images/Reversi/osero(white).png");
	XOnce = TRUE;
	XOnce = TRUE;
	/*CursorPoint = { 0, 0 };*/

	K_Flg = FALSE;

	//フラグ初期化
	Fla.Xr = 0;
	Fla.Xl = 0;
	Fla.Yu = 0;
	Fla.Yd = 0;
	Fla.button = 0;

	Tur = 0;

	//配列の初期値
	for (int y = 0; y < 8; y = y + 1)
	{
		for (int x = 0; x < 8; x = x + 1)
		{
			Sto.Typ[x][y] = 0;
			Sto.X[x][y] = 0;
			Sto.Y[x][y] = 0;
		}
	}

	//左上黒
	Sto.Typ[3][3] = 1;
	Sto.X[3][3] = 3 * 188;
	Sto.Y[3][3] = 3 * 100 - 5;

	//右下黒
	Sto.Typ[4][4] = 1;
	Sto.X[4][4] = 4 * 165;
	Sto.Y[4][4] = 4 * 100 - 6;

	//左下白
	Sto.Typ[3][4] = 2;
	Sto.X[3][4] = 3 * 190;
	Sto.Y[3][4] = 4 * 100 - 5;

	//右上白
	Sto.Typ[4][3] = 2;
	Sto.X[4][3] = 4 * 165;
	Sto.Y[4][3] = 3 * 100 - 6;

	Cur.X = 310;
	Cur.Y = 20;
}

Reversi::~Reversi()
{

}


AbstractScene* Reversi::Update()
{
	Cursor();
	turn();

	
	return this;
}



void Reversi::Draw() const
{
	DrawFormatString(0, 100, GetColor(255, 255, 255), " %d:button", Fla.button);
	for (int y = 0; y < 8; y = y + 1)
	{
		for (int x = 0; x < 8; x = x + 1)
		{
			DrawGraph(x * 85 + 310, y * 85 + 20, Bac, TRUE);
		}
	}

	for (int y = 0; y < 8; y = y + 1)
	{
		for (int x = 0; x < 8; x = x + 1)
		{
			switch (Sto.Typ[x][y])
			{
			case 0:
				break;
			case 1:
				DrawGraph(Sto.X[x][y], Sto.Y[x][y], Bla, TRUE);
				break;
			case 2:
				DrawGraph(Sto.X[x][y], Sto.Y[x][y], Whi, TRUE);
				break;
			}
		}
	}

	DrawFormatString(0, 120, GetColor(255, 255, 255), "Cur.X,Cur.Y=(%d,%d)", Cur.X, Cur.Y);
	DrawFormatString(0, 140, GetColor(255, 255, 255), "Tur,%d", Tur);

	DrawBox(Cur.X, Cur.Y, Cur.X + 85, Cur.Y + 85, 0xffffff, FALSE);

	if (Tur % 2 == 0)
	{
		DrawFormatString(0, 160, GetColor(255, 255, 255), "%dTurn Black", Tur);
	}
	else
	{
		DrawFormatString(0, 160, GetColor(255, 255, 255), "%dTurn White", Tur);

	}

}

void Reversi::Cursor()
{
	
	//カーソルを上移動させる
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP) || (PAD_INPUT::GetLStick().ThumbY > 10000 && YOnce == TRUE)) {
		Cur.Y -= 85;
		//連続入力しないようにする
		YOnce = FALSE;

	}
	//カーソルを右移動させる
	else if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT) || (PAD_INPUT::GetLStick().ThumbX > 10000 && YOnce == TRUE)) {
		Cur.X += 85;
		//連続入力しないようにする
		YOnce = FALSE;

	}
	//カーソルを下移動させる
	else if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN) || (PAD_INPUT::GetLStick().ThumbY < -10000 && YOnce == TRUE)) {
		Cur.Y += 85;
		//連続入力しないようにする
		YOnce = FALSE;

	}
	//カーソルを左移動させる
	else if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT) || (PAD_INPUT::GetLStick().ThumbX < -10000 && YOnce == TRUE)) {
		Cur.X -= 85;

		//連続入力しないようにする
		YOnce = FALSE;

	}

	//カーソルが盤面の外に行かないようにする
	if (Cur.Y < 20) {
		Cur.Y = 20;
	}
	if (Cur.Y > 615) {
		Cur.Y = 615;
	}
	if (Cur.X < 310) {
		Cur.X = 310;
	}
	if (Cur.X > 905) {
		Cur.X = 905;
	}

}

void Reversi::turn()
{

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		Fla.button = 1;
	}

	for (int y = 0; y < 8; y = y + 1)
	{
		for (int x = 0; x < 8; x = x + 1)
		{
			Fla.button = 0;
			if (Cur.X == 85 * x  + 310 && Cur.Y == 85 * y + 20 &&
				Fla.button == 1 && Sto.Typ[x][y] == 0)
			{
				Tur = Tur + 1;
				Sto.X[x][y] = Cur.X;
				Sto.Y[x][y] = Cur.Y;
				if (Tur % 2 == 0)
				{
					Sto.Typ[x][y] = 2;
				}
				else
				{
					Sto.Typ[x][y] = 1;
				}

			}
		}
	}

	
	
}

