#include "gomokuScene.h"
#include"DxLib.h"
#include <stdio.h>

gomokuScene::gomokuScene()
{
	TitleImg = LoadGraph("../images/Gomoku/gomoku.png");
	wTopImg = LoadGraph("../images/Gomoku/BK.png");
	bTopImg = LoadGraph("../images/Gomoku/WK.png");
	cX = 0;
	cY = 0;
	for (int y = 0; y < 13; y++)
		for (int x = 0; x < 13; x++) {
			Banmen[x][y] = 0;
		}
	Phase = 0;
	Battle = 0;
}

gomokuScene::~gomokuScene()
{}

AbstractScene* gomokuScene::Update()
{
	if (Battle == 0) { // 試合中なら実行する

		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;

		// カーソルを動かす処理
		if (g_KeyFlg & PAD_INPUT_RIGHT && cX < 12) {
			cX += 1;
		}
		if (g_KeyFlg & PAD_INPUT_LEFT && cX > 0) {
			cX -= 1;
		}
		if (g_KeyFlg & PAD_INPUT_DOWN && cY < 12) {
			cY += 1;
		}
		if (g_KeyFlg & PAD_INPUT_UP && cY > 0) {
			cY -= 1;
		}

		// まだ石が置かれていない盤面に石を置き、手番を交代する
		if (g_KeyFlg & PAD_INPUT_1 && Banmen[cX][cY] == 0) {
			if (Phase == 0) {
				Banmen[cX][cY] = 1;
			}
			else {
				Banmen[cX][cY] = 2;
			}
			if (Phase == 0) {
				Phase = 1;
			}
			else {
				Phase = 0;
			}
		}

		// 黒(Banmen[x][y] = 1)と白(Banmen[x][y] = 2)の勝利判定
		for (int y = 0; y < 13; y++)
			for (int x = 0; x < 13; x++) {
				// 黒(Banmen[x][y] = 1)の勝利判定
				if (Banmen[x][y] == 1 && Banmen[x + 1][y] == 1 && Banmen[x + 2][y] == 1 && Banmen[x + 3][y] == 1 && Banmen[x + 4][y] == 1 ||
					Banmen[x][y] == 1 && Banmen[x][y + 1] == 1 && Banmen[x][y + 2] == 1 && Banmen[x][y + 3] == 1 && Banmen[x][y + 4] == 1 ||
					Banmen[x][y] == 1 && Banmen[x + 1][y + 1] == 1 && Banmen[x + 2][y + 2] == 1 && Banmen[x + 3][y + 3] == 1 && Banmen[x + 4][y + 4] == 1 ||
					Banmen[x][y] == 1 && Banmen[x - 1][y - 1] == 1 && Banmen[x - 2][y - 2] == 1 && Banmen[x - 3][y - 3] == 1 && Banmen[x - 4][y - 4] == 1 ||
					Banmen[x][y] == 1 && Banmen[x + 1][y - 1] == 1 && Banmen[x + 2][y - 2] == 1 && Banmen[x + 3][y - 3] == 1 && Banmen[x + 4][y - 4] == 1 ||
					Banmen[x][y] == 1 && Banmen[x - 1][y + 1] == 1 && Banmen[x - 2][y + 2] == 1 && Banmen[x - 3][y + 3] == 1 && Banmen[x - 4][y + 4] == 1) {
					Battle = 1;
				}
				// 白(Banmen[x][y] = 2)の勝利判定
				else if (Banmen[x][y] == 2 && Banmen[x + 1][y] == 2 && Banmen[x + 2][y] == 2 && Banmen[x + 3][y] == 2 && Banmen[x + 4][y] == 2 ||
					Banmen[x][y] == 2 && Banmen[x][y + 1] == 2 && Banmen[x][y + 2] == 2 && Banmen[x][y + 3] == 2 && Banmen[x][y + 4] == 2 ||
					Banmen[x][y] == 2 && Banmen[x + 1][y + 1] == 2 && Banmen[x + 2][y + 2] == 2 && Banmen[x + 3][y + 3] == 2 && Banmen[x + 4][y + 4] == 2 ||
					Banmen[x][y] == 2 && Banmen[x - 1][y - 1] == 2 && Banmen[x - 2][y - 2] == 2 && Banmen[x - 3][y - 3] == 2 && Banmen[x - 4][y - 4] == 2 ||
					Banmen[x][y] == 2 && Banmen[x + 1][y - 1] == 2 && Banmen[x + 2][y - 2] == 2 && Banmen[x + 3][y - 3] == 2 && Banmen[x + 4][y - 4] == 2 ||
					Banmen[x][y] == 2 && Banmen[x - 1][y + 1] == 2 && Banmen[x - 2][y + 2] == 2 && Banmen[x - 3][y + 3] == 2 && Banmen[x - 4][y + 4] == 2) {
					Battle = 2;
				}
			}
		return this;
	}
}

void gomokuScene::Draw() const
{
	DrawFormatString(10, 10,0xffffff, "%d %d", cX, cY);
	DrawGraph(180, 0, TitleImg, TRUE);
	for (int y = 0; y < 13; y++) {
		for (int x = 0; x < 13; x++) {
			if (Banmen[x][y] == 1) {
				DrawGraph(270 + (56 * x) + x * 1, -25 + (56 * y) + y * 1, bTopImg, TRUE);
			}
			else if (Banmen[x][y] == 2) {
				DrawGraph(270 + (56 * x) + x * 1, -25 + (56 * y) + y * 1, wTopImg, TRUE);
			}
		}
	}
	if (Phase == 0 && Battle == 0) {
		SetFontSize(60);
		DrawFormatString(50, 300, 0xfffffff, "黒の手番");
	}
	if (Phase == 1 && Battle == 0) {
		SetFontSize(60);
		DrawFormatString(50, 300, 0xfffffff, "白の手番");
	}
	if (Battle == 0) {
		DrawBox(285 + (56 * cX), -15 + (56 * cY), 345 + (56 * cX), 45 + (56 * cY), 0xffff00, FALSE);
	}
	if (Battle == 1) {
		SetFontSize(80);
		DrawFormatString(600, 300, 0xFF00FF, ("黒の勝ち"));
	}
	else if (Battle == 2) {
		SetFontSize(80);
		DrawFormatString(600, 300, 0xFF00FF, ("白の勝ち"));
	}
	
}
// if(x % 2 == 0 && y % 2 == 0)