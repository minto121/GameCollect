#include "Reversi.h"
#include<DxLib.h>
#include "PadInput.h"

#define WALL 0;
#define WHITE 1;
#define BLACK 2;

#define SCREEN_HEIGHT 720	//画面サイズ (縦)
#define SCREEN_WIDTH 1280	//画面サイズ (横)

//盤面
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
	Sto.X[3][3] = 555;
	Sto.Y[3][3] = 280;

	//右下黒
	Sto.Typ[4][4] = 1;
	Sto.X[4][4] = 640;
	Sto.Y[4][4] = 364;

	//左下白
	Sto.Typ[3][4] = 2;
	Sto.X[3][4] = 555;
	Sto.Y[3][4] = 365;

	//右上白
	Sto.Typ[4][3] = 2;
	Sto.X[4][3] = 640;
	Sto.Y[4][3] = 279;

	Cur.X = 310;
	Cur.Y = 20;



}

Reversi::~Reversi()
{

}


AbstractScene* Reversi::Update()
{

	Fla.button = 0;
	Cursor();
	turn();

	e.x.m = Cur.X / 85;
	e.y.m = Cur.Y / 85;

	e.x.r = e.x.m + 1;
	e.x.l = e.x.m - 1;
	e.y.u = e.y.m - 1;
	e.y.d = e.y.m + 1;

	if (Fla.button == 1)
	{
		int x, y;

		//黒
		int same;
		//白
		int diff;

		if (Tur % 2 == 0)
		{
			same = 2;
			diff = 1;
		}
		else
		{
			same = 1;
			diff = 2;
		}

		int cou = 0;

		//右に石が置かれているかの確認
		for (x = e.x.r; x < 8; x = x + 1)
		{
			if (Sto.Typ[x][e.y.m] == 0)break;
			else if (Sto.Typ[x][e.y.m] == same)
			{
				for ( x = e.x.r; x < e.x.r + cou; x = x + 1)
				{
					Sto.Typ[x][e.y.m] = same;
				}break;
			}
			else if (Sto.Typ[x][e.y.m] == diff)cou = cou + 1;
			else break;
		}
		cou = 0;

		//左に石が置かれているかの確認
		for (x = e.x.l; x > 0; x = x - 1)
		{
			if (Sto.Typ[x][e.y.m] == 0)break;
			else if (Sto.Typ[x][e.y.m] == same)
			{
				for ( x = e.x.l; x > e.x.l - cou; x = x - 1)
				{
					Sto.Typ[x][e.y.m] = same;
				}break;
			}
			else if (Sto.Typ[x][e.y.m] == diff)cou = cou + 1;
			else break;
		}
		cou = 0;

		//下に石が置かれているかの確認
		for (y = e.y.d; y < 8; y = y + 1)
		{
			if (Sto.Typ[e.x.m][y] == 0)break;
			else if (Sto.Typ[e.x.m][y] == same)
			{
				for (x = e.y.d; y < e.y.d + cou; y = y + 1)
				{
					Sto.Typ[e.x.m][y] = same;
				}break;
			}
			else if (Sto.Typ[e.x.m][y] == diff)cou = cou + 1;
			else break;
		}
		cou = 0;

		//上に石が置かれているかの確認
		for (y = e.y.u; y > 0; y = y - 1)
		{
			if (Sto.Typ[e.x.m][y] == 0)break;
			else if (Sto.Typ[e.x.m][y] == same)
			{
				for ( x = e.y.u; y > e.y.u - cou; y = y - 1)
				{
					Sto.Typ[e.x.m][y] = same;
				}break;
			}
			else if (Sto.Typ[e.x.m][y] == diff)cou = cou + 1;
			else break;
		}
		cou = 0;

		//右上に石が置かれているかの確認

		for (x = e.x.r, y = e.y.u;
			x < 8,y > 0;
			x = x + 1,y = y - 1)
		{
			if (Sto.Typ[x][y] == 0)break;
			else if (Sto.Typ[x][y] == same)
			{
				for (x = e.x.r, y = e.y.d;
					x < e.x.r + cou,y > e.y.u - cou;
					x = x + 1, y = y - 1)
				{
					Sto.Typ[x][y] = same;
				}break;
			}
			else if (Sto.Typ[x][y] == diff)cou = cou + 1;
			else break;
		}
		cou = 0;


		//右下に石が置かれているかの確認
		for (x = e.x.r, y = e.y.d;
			x < 8, y < 8;
			x = x + 1, y = y + 1)
		{
			if (Sto.Typ[x][y] == 0)break;
			else if (Sto.Typ[x][y] == same)
			{
				for (x = e.x.r, y = e.y.d;
					x < e.x.r + cou, y < e.y.d + cou;
					x = x + 1, y = y + 1)
				{
					Sto.Typ[x][y] = same;
				}break;
			}
			else if (Sto.Typ[x][y] == diff)cou = cou + 1;
			else break;
		}
		cou = 0;

		//左上に石が置かれているかの確認

		for (x = e.x.l, y = e.y.u;
			x > 0, y > 0;
			x = x - 1, y = y - 1)
		{
			if (Sto.Typ[x][y] == 0)break;
			else if (Sto.Typ[x][y] == same)
			{
				for (x = e.x.l, y = e.y.d;
					x < e.x.r - cou, y > e.y.u - cou;
					x = x + 1, y = y - 1)
				{
					Sto.Typ[x][y] = same;
				}break;
			}
			else if (Sto.Typ[x][y] == diff)cou = cou + 1;
			else break;
		}
		cou = 0;


		//左下に石が置かれているかの確認
		for (x = e.x.l, y = e.y.d;
			x > 0, y < 8;
			x = x - 1, y = y + 1)
		{
			if (Sto.Typ[x][y] == 0)break;
			else if (Sto.Typ[x][y] == same)
			{
				for (x = e.x.l, y = e.y.d;
					x > e.x.r - cou, y < e.y.d + cou;
					x = x - 1, y = y + 1)
				{
					Sto.Typ[x][y] = same;
				}break;
			}
			else if (Sto.Typ[x][y] == diff)cou = cou + 1;
			else break;
		}
		cou = 0;
	}

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
			if (Cur.X == 85 * x  + 310 && Cur.Y == 85 * y + 20 &&
				Fla.button == 1 && Sto.Typ[x][y] == 0)
			{
				Tur = Tur + 1;
				Sto.X[x][y] = Cur.X - 10;
				Sto.Y[x][y] = Cur.Y + 5;
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

