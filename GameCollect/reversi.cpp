#include "Reversi.h"
#include<DxLib.h>
#include "PadInput.h"

#define WALL 0
#define WHITE 1
#define BLACK 2

//”Õ–Ê
#define SIZ 10
#define BOARD_IMG_SIZE 640;
#define CELL_SIZE = BOARD_IMG_SIZE /SIZ;

int board[SIZ][SIZ];

Reversi::Reversi()
{
	Bac = LoadGraph("images/Reversi/banmen.png");
	Bla = LoadGraph("images/Reversi/osero(black).png");
	Whi= LoadGraph("images/Reversi/osero(white).png");
	XOnce = TRUE;
	XOnce = TRUE;
	/*CursorPoint = { 0, 0 };*/

	K_Flg = FALSE;

	
}

Reversi::~Reversi()
{
}


AbstractScene* Reversi::Update()
{
	turn();

	return this;
}



void Reversi::Draw() const
{
	DrawFormatString(0, 100, GetColor(255, 255, 255), " %d:button", K_Flg);
	
	//‹î‚Ì•`‰æ
	if (K_Flg == TRUE)
	{
		DrawGraph(0, 0, W_Storn_Img, TRUE);
	}

	//”Õ–Ê‚Ì•`‰æ
	DrawGraph(340, 50, R_Img, TRUE);


}


void Reversi::init_board(int board[SIZ][SIZ])
{
	int i, j;

	for (i = 0; i < SIZ; i++) {
		for (j = 0; j < SIZ; j++) {
			board[i][j] = -1;
		}
	}
	for (i = 1; i <= 8; i++) {
		for (j = 1; j <= 8; j++) {
			board[i][j] = 0;
		}
	}
	board[4][5] = board[5][4] = 1;
	board[4][4] = board[5][5] = 2;
}

//void Reversi::Board()
//{
//
//	int i;
//	int j;
//
//	//for (int x = 0; x < 10;x++) {
//	//	for (int y = 0; y < 10; y++) {
//	//		Boa.typ[x][y] = 0;
//	//		Boa.x[x][y] = 0;
//	//		Boa.y[x][y] = 0;
//	//	}
//	//}
//
//	//Boa.typ[3][3] = 1;
//	//Boa.x[3][3] = 3 * 100;
//	//Boa.y[3][3] = 3 * 100;
//
//	//Boa.typ[4][4] = 1;
//	//Boa.x[4][4] = 4 * 100;
//	//Boa.y[4][4] = 4 * 100;
//
//	//Boa.typ[3][4] = 2;
//	//Boa.x[3][4] = 4 * 100;
//	//Boa.y[3][4] = 4 * 100;
//
//	//Boa.typ[4][3] = 2;
//	//Boa.x[4][3] = 4 * 100;
//	//Boa.y[4][3] = 3 * 100;
//
//	static int initdata[10][10]{
// { -1 , -1, -1, -1, -1, -1, -1, -1, -1, -1},
// { -1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -1},
// { -1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -1},
// { -1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -1},
// { -1 , 0 , 0 , 0 , 1 , 2 , 0 , 0 , 0 , -1},
// { -1 , 0 , 0 , 0 , 2 , 1 , 0 , 0 , 0 , -1},
// { -1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -1},
// { -1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -1},
// { -1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -1},
// { -1 , -1, -1, -1, -1, -1, -1, -1, -1, -1}
//	};
//
//	for (i = 0; i < SIZ; i++) {
//		for (j = 0; j < SIZ; j++) {
//			board[i][j] = initdata[i][j];
//		}
//	}
//	board[3][3] = board[4][4] = 1;
//	board[3][4] = board[4][3] = 2;
//
//}



void Reversi::turn()
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

