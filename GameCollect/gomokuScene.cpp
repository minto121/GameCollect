#include "gomokuScene.h"
#include"DxLib.h"
#include <stdio.h>

gomokuScene::gomokuScene()
{
	TitleImg = LoadGraph("../images/Gomoku/gomoku.png");
	wTopImg = LoadGraph("../images/Gomoku/BK.png");
	bTopImg = LoadGraph("../images/Gomoku/WK.png");
	gomoku_BackImg = LoadGraph("../images/Gomoku/BackGround02.png");
	cX = 0;
	cY = 0;
	enemyX = 0;
	enemyY = 0;
	bCount = 0;
	wCount = 0;
	gomoku_AImove_Point = 0;
	gomoku_AI_MoveX = 0;
	gomoku_AI_MoveY = 0;
	gomoku_AI_think = 0;
	g_OldKey = 0;
	g_NowKey = 0;
	g_KeyFlg = 0;
	for (int y = 0; y < 13; y++)
		for (int x = 0; x < 13; x++) {
			/*if (x == 6 && y == 6 || x == 7 && y == 7) {
				Banmen[x][y] = 1;
			}
			else if (x == 6 && y == 7 || x == 7 && y == 6) {
				Banmen[x][y] = 2;
			}
			else {*/
				gomoku_Banmen[x][y] = 0;
			}
	gomoku_Phase = 0;
	gomoku_Battle = 0;
}

gomokuScene::~gomokuScene()
{}

AbstractScene* gomokuScene::Update()
{
	if (gomoku_Battle == 0) { // 試合中なら実行する

		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;

		// 初手は盤面の真ん中にしか置くことができない
		if (Key_Count <= 1) {
			cX = 5;
			cY = 5;
		}

		// カーソルを動かす処理
		if (gomoku_Phase == 0) {
			if (g_KeyFlg & PAD_INPUT_RIGHT && cX < 13) {
				if (Key_Count > 1) {
					cX += 1;
				}
				if (g_KeyFlg & PAD_INPUT_RIGHT && cX == 13) {
					cX = 0;
				}
			}
			if (g_KeyFlg & PAD_INPUT_LEFT && cX > -1) {
				if (Key_Count > 1) {
					cX -= 1;
				}
				if (g_KeyFlg & PAD_INPUT_LEFT && cX == -1) {
					cX = 12;
				}
			}
			if (g_KeyFlg & PAD_INPUT_DOWN && cY < 13) {
				if (Key_Count > 1) {
					cY += 1;
				}
				if (g_KeyFlg & PAD_INPUT_DOWN && cY == 13) {
					cY = 0;
				}
			}
			if (g_KeyFlg & PAD_INPUT_UP && cY > -1) {
				if (Key_Count > 1) {
					cY -= 1;
				}
				if (g_KeyFlg & PAD_INPUT_UP && cY == -1) {
					cY = 12;
				}
			}
		}
		gomoku_AI_MoveX = 0;
		gomoku_AI_MoveY = 0;
		gomoku_AI_think = 0;
		gomoku_AImove_Point = 0;

		// まだ石が置かれていない盤面に石を置き、手番を交代する
		if (g_KeyFlg & PAD_INPUT_1 && gomoku_Phase == 0) {
			Key_Count++;
		}
		if (g_KeyFlg& PAD_INPUT_1&& gomoku_Banmen[cX][cY] == 0 && Key_Count >= 2) {
			if (gomoku_Phase == 0) {
				bCount += 1;
				gomoku_Banmen[cX][cY] = 1;
				enemyX = cX + 1;
				enemyY = cY + 1;
				gomoku_Phase = 1;
			}
			/*else {
				gomoku_Banmen[cX][cY] = 2;
			}*/
			/*if (gomoku_Phase == 0) {
				gomoku_Phase = 1;
			}*/
			/*else {
				gomoku_Phase = 0;
			}*/

			// x < 8 y < 8
		}
		for (int y = 0; y < 13; y++) {
			for (int x = 0; x < 13; x++) {
				// 黒(Banmen[x][y] = 1)の勝利判定
				if (x < 8 && gomoku_Banmen[x][y] == 1 && gomoku_Banmen[x + 1][y] == 1 && gomoku_Banmen[x + 2][y] == 1 && gomoku_Banmen[x + 3][y] == 1 && gomoku_Banmen[x + 4][y] == 1 ||
					x > 3 && gomoku_Banmen[x][y] == 1 && gomoku_Banmen[x - 1][y] == 1 && gomoku_Banmen[x - 2][y] == 1 && gomoku_Banmen[x - 3][y] == 1 && gomoku_Banmen[x - 4][y] == 1 ||
					y < 8 && gomoku_Banmen[x][y] == 1 && gomoku_Banmen[x][y + 1] == 1 && gomoku_Banmen[x][y + 2] == 1 && gomoku_Banmen[x][y + 3] == 1 && gomoku_Banmen[x][y + 4] == 1 ||
					y > 3 && gomoku_Banmen[x][y] == 1 && gomoku_Banmen[x][y - 1] == 1 && gomoku_Banmen[x][y - 2] == 1 && gomoku_Banmen[x][y - 3] == 1 && gomoku_Banmen[x][y - 4] == 1 ||
					x < 8 && y < 8 && gomoku_Banmen[x][y] == 1 && gomoku_Banmen[x + 1][y + 1] == 1 && gomoku_Banmen[x + 2][y + 2] == 1 && gomoku_Banmen[x + 3][y + 3] == 1 && gomoku_Banmen[x + 4][y + 4] == 1 ||
					x > 3 && y > 3 && gomoku_Banmen[x][y] == 1 && gomoku_Banmen[x - 1][y - 1] == 1 && gomoku_Banmen[x - 2][y - 2] == 1 && gomoku_Banmen[x - 3][y - 3] == 1 && gomoku_Banmen[x - 4][y - 4] == 1 ||
					x < 8 && y > 3 && gomoku_Banmen[x][y] == 1 && gomoku_Banmen[x + 1][y - 1] == 1 && gomoku_Banmen[x + 2][y - 2] == 1 && gomoku_Banmen[x + 3][y - 3] == 1 && gomoku_Banmen[x + 4][y - 4] == 1 ||
					x < 8 && y > 3 && gomoku_Banmen[x][y] == 1 && gomoku_Banmen[x - 1][y + 1] == 1 && gomoku_Banmen[x - 2][y + 2] == 1 && gomoku_Banmen[x - 3][y + 3] == 1 && gomoku_Banmen[x - 4][y + 4] == 1) {
					gomoku_Battle = 1;
				}
			}
		}
		// ここからAI
		/*if (gomoku_Battle == 0 && gomoku_Phase == 1)
		if (enemyX < 12 && enemyY < 12 && gomoku_Banmen[enemyX][enemyY] == 0) {
			gomoku_Banmen[enemyX][enemyY] = 2;
			gomoku_Phase = 0;
		}
		else {
			for (int y = 0; y < 13; y++)
				for (int x = 0; x < 13; x++)
					if (gomoku_Banmen[x][y] == 0 && gomoku_Phase == 1) {
						wCount += 1;
						gomoku_Banmen[x][y] = 2;
						gomoku_Phase = 0;
					}
		}
		 */
		if (gomoku_Battle == 0 && gomoku_Phase == 1 && gomoku_AI_think == 0) {
			for (int y = 0; y < 13; y++) {
				for (int x = 0; x < 13; x++) {
					if (Key_Count == 2 && gomoku_Banmen[x][y] == 1) {
						gomoku_AImove_Point = 100;
						gomoku_AI_MoveX = x + 1;
						gomoku_AI_MoveY = y + 1;
					}
					// 盤面に黒がつ四つ並んでいて、端のどちらかに石が置かれていない場合白を置くプログラミング
					if (y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y + 1] == 1 && gomoku_Banmen[x][y + 2] == 1 && gomoku_Banmen[x][y + 3] == 1 && gomoku_Banmen[x][y + 4] == 1 ||
						y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y - 1] == 1 && gomoku_Banmen[x][y - 2] == 1 && gomoku_Banmen[x][y - 3] == 1 && gomoku_Banmen[x][y - 4] == 1 ||
						x < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y] == 1 && gomoku_Banmen[x + 2][y] == 1 && gomoku_Banmen[x + 3][y] == 1 && gomoku_Banmen[x + 4][y] == 1 ||
						x > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y] == 1 && gomoku_Banmen[x - 2][y] == 1 && gomoku_Banmen[x - 3][y] == 1 && gomoku_Banmen[x - 4][y] == 1 ||
						x < 8 && y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y + 1] == 1 && gomoku_Banmen[x + 2][y + 2] == 1 && gomoku_Banmen[x + 3][y + 3] == 1 && gomoku_Banmen[x + 4][y + 4] == 1 ||
						x > 3 && y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y - 1] == 1 && gomoku_Banmen[x - 2][y - 2] == 1 && gomoku_Banmen[x - 3][y - 3] == 1 && gomoku_Banmen[x - 4][y - 4] == 1 ||
						x < 8 && y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y - 1] == 1 && gomoku_Banmen[x + 2][y - 2] == 1 && gomoku_Banmen[x + 3][y - 3] == 1 && gomoku_Banmen[x + 4][y - 4] == 1 ||
						x > 3 && y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y + 1] == 1 && gomoku_Banmen[x - 2][y + 2] == 1 && gomoku_Banmen[x - 3][y + 3] == 1 && gomoku_Banmen[x - 4][y + 4] == 1 ||
						x < 8 && y < 8 && gomoku_Banmen[x][y] == 1 && gomoku_Banmen[x + 1][y + 1] == 0 && gomoku_Banmen[x + 2][y + 2] == 1 && gomoku_Banmen[x + 3][y + 3] == 1 && gomoku_Banmen[x + 4][y + 4] == 1){
						if (gomoku_AImove_Point < 7) {
							gomoku_AImove_Point = 7;
							gomoku_AI_MoveX = x;
							gomoku_AI_MoveY = y;
						}
					}// 盤面に白がつ四つ並んでいて、端のどちらかに石が置かれていない場合白を置くプログラミング
					else if (y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y + 1] == 2 && gomoku_Banmen[x][y + 2] == 2 && gomoku_Banmen[x][y + 3] == 2 && gomoku_Banmen[x][y + 4] == 2 ||
						y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y - 1] == 2 && gomoku_Banmen[x][y - 2] == 2 && gomoku_Banmen[x][y - 3] == 2 && gomoku_Banmen[x][y - 4] == 2 ||
						x < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y] == 2 && gomoku_Banmen[x + 2][y] == 2 && gomoku_Banmen[x + 3][y] == 2 && gomoku_Banmen[x + 4][y] == 2 ||
						x > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y] == 2 && gomoku_Banmen[x - 2][y] == 2 && gomoku_Banmen[x - 3][y] == 2 && gomoku_Banmen[x - 4][y] == 2 ||
						x < 8 && y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y + 1] == 2 && gomoku_Banmen[x + 2][y + 2] == 2 && gomoku_Banmen[x + 3][y + 3] == 2 && gomoku_Banmen[x + 4][y + 4] == 2 ||
						x > 3 && y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y - 1] == 2 && gomoku_Banmen[x - 2][y - 2] == 2 && gomoku_Banmen[x - 3][y - 3] == 2 && gomoku_Banmen[x - 4][y - 4] == 2 ||
						x < 8 && y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y - 1] == 2 && gomoku_Banmen[x + 2][y - 2] == 2 && gomoku_Banmen[x + 3][y - 3] == 2 && gomoku_Banmen[x + 4][y - 4] == 2 ||
						x > 3 && y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y + 1] == 2 && gomoku_Banmen[x - 2][y + 2] == 2 && gomoku_Banmen[x - 3][y + 3] == 2 && gomoku_Banmen[x - 4][y + 4] == 2) {
						gomoku_AImove_Point = 99;
						gomoku_AI_MoveX = x;
						gomoku_AI_MoveY = y;
					}// 盤面に白が三つ並んでいて、両端に石が置かれていない場合白を置くプログラミング
					else if (y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y + 1] == 2 && gomoku_Banmen[x][y + 2] == 2 && gomoku_Banmen[x][y + 3] == 2 && gomoku_Banmen[x][y + 4] == 0 ||
						y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y - 1] == 2 && gomoku_Banmen[x][y - 2] == 2 && gomoku_Banmen[x][y - 3] == 2 && gomoku_Banmen[x][y - 4] == 0 ||
						x < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y] == 2 && gomoku_Banmen[x + 2][y] == 2 && gomoku_Banmen[x + 3][y] == 2 && gomoku_Banmen[x + 4][y] == 0 ||
						x > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y] == 2 && gomoku_Banmen[x - 2][y] == 2 && gomoku_Banmen[x - 3][y] == 2 && gomoku_Banmen[x - 4][y] == 0 ||
						x < 8 && y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y + 1] == 2 && gomoku_Banmen[x + 2][y + 2] == 2 && gomoku_Banmen[x + 3][y + 3] == 2 && gomoku_Banmen[x + 4][y + 4] == 0 ||
						x > 3 && y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y - 1] == 2 && gomoku_Banmen[x - 2][y - 2] == 2 && gomoku_Banmen[x - 3][y - 3] == 2 && gomoku_Banmen[x - 4][y - 4] == 0 ||
						x < 8 && y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y - 1] == 2 && gomoku_Banmen[x + 2][y - 2] == 2 && gomoku_Banmen[x + 3][y - 3] == 2 && gomoku_Banmen[x + 4][y - 4] == 0 ||
						x > 3 && y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y + 1] == 2 && gomoku_Banmen[x - 2][y + 2] == 2 && gomoku_Banmen[x - 3][y + 3] == 2 && gomoku_Banmen[x - 4][y + 4] == 0) {
						if (gomoku_AImove_Point < 6) {
							gomoku_AImove_Point = 6;
							gomoku_AI_MoveX = x;
							gomoku_AI_MoveY = y;
						}
					}// 盤面に黒が三つ並んでいて、両端に石が置かれていない場合白を置くプログラミング
					else if (y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y + 1] == 1 && gomoku_Banmen[x][y + 2] == 1 && gomoku_Banmen[x][y + 3] == 1 && gomoku_Banmen[x][y + 4] == 0 ||
						y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y - 1] == 1 && gomoku_Banmen[x][y - 2] == 1 && gomoku_Banmen[x][y - 3] == 1 && gomoku_Banmen[x][y - 4] == 0 ||
						x < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y] == 1 && gomoku_Banmen[x + 2][y] == 1 && gomoku_Banmen[x + 3][y] == 1 && gomoku_Banmen[x + 4][y] == 0 ||
						x > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y] == 1 && gomoku_Banmen[x - 2][y] == 1 && gomoku_Banmen[x - 3][y] == 1 && gomoku_Banmen[x - 4][y] == 0 ||
						x < 8 && y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y + 1] == 1 && gomoku_Banmen[x + 2][y + 2] == 1 && gomoku_Banmen[x + 3][y + 3] == 1 && gomoku_Banmen[x + 4][y + 4] == 0 ||
						x > 3 && y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y - 1] == 1 && gomoku_Banmen[x - 2][y - 2] == 1 && gomoku_Banmen[x - 3][y - 3] == 1 && gomoku_Banmen[x - 4][y - 4] == 0 ||
						x < 8 && y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y - 1] == 1 && gomoku_Banmen[x + 2][y - 2] == 1 && gomoku_Banmen[x + 3][y - 3] == 1 && gomoku_Banmen[x + 4][y - 4] == 0 ||
						x > 3 && y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y + 1] == 1 && gomoku_Banmen[x - 2][y + 2] == 1 && gomoku_Banmen[x - 3][y + 3] == 1 && gomoku_Banmen[x - 4][y + 4] == 0) {
						if (gomoku_AImove_Point < 5) {
							gomoku_AImove_Point = 5;
							gomoku_AI_MoveX = x;
							gomoku_AI_MoveY = y;
						}
					}// 盤面に白が三つ並んでいて、端のどちらかに石が置かれていない場合白を置くプログラミング
					else if (y < 9 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y + 1] == 2 && gomoku_Banmen[x][y + 2] == 2 && gomoku_Banmen[x][y + 3] == 2 ||
						y > 2 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y - 1] == 2 && gomoku_Banmen[x][y - 2] == 2 && gomoku_Banmen[x][y - 3] == 2 ||
						x < 9 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y] == 2 && gomoku_Banmen[x + 2][y] == 2 && gomoku_Banmen[x + 3][y] == 2 ||
						x > 2 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y] == 2 && gomoku_Banmen[x - 2][y] == 2 && gomoku_Banmen[x - 3][y] == 2 ||
						x < 9 && y < 9 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y + 1] == 2 && gomoku_Banmen[x + 2][y + 2] == 2 && gomoku_Banmen[x + 3][y + 3] == 2 ||
						x > 2 && y > 9 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y - 1] == 2 && gomoku_Banmen[x - 2][y - 2] == 2 && gomoku_Banmen[x - 3][y - 3] == 2 ||
						x < 9 && y > 2 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y - 1] == 2 && gomoku_Banmen[x + 2][y - 2] == 2 && gomoku_Banmen[x + 3][y - 3] == 2 ||
						x > 2 && y < 9 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y + 1] == 2 && gomoku_Banmen[x - 2][y + 2] == 2 && gomoku_Banmen[x - 3][y + 3] == 2) {
						if (gomoku_AImove_Point < 4) {
							gomoku_AImove_Point = 4;
							gomoku_AI_MoveX = x;
							gomoku_AI_MoveY = y;
						}
					}// 盤面に黒が三つ並んでいて、端のどちらかに石が置かれていない場合白を置くプログラミング
					else if (y < 9 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y + 1] == 1 && gomoku_Banmen[x][y + 2] == 1 && gomoku_Banmen[x][y + 3] == 1 ||
						y > 2 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y - 1] == 1 && gomoku_Banmen[x][y - 2] == 1 && gomoku_Banmen[x][y - 3] == 1 ||
						x < 9 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y] == 1 && gomoku_Banmen[x + 2][y] == 2 && gomoku_Banmen[x + 3][y] == 1 ||
						x > 2 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y] == 1 && gomoku_Banmen[x - 2][y] == 2 && gomoku_Banmen[x - 3][y] == 1 ||
						x < 9 && y < 9 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y + 1] == 1 && gomoku_Banmen[x + 2][y + 2] == 1 && gomoku_Banmen[x + 3][y + 3] == 1 ||
						x > 2 && y > 2 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y - 1] == 1 && gomoku_Banmen[x - 2][y - 2] == 1 && gomoku_Banmen[x - 3][y - 3] == 1 ||
						x < 9 && y > 2 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y - 1] == 1 && gomoku_Banmen[x + 2][y - 2] == 1 && gomoku_Banmen[x + 3][y - 3] == 1 ||
						x > 2 && y < 9 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y + 1] == 1 && gomoku_Banmen[x - 2][y + 2] == 1 && gomoku_Banmen[x - 3][y + 3] == 1) {
						if (gomoku_AImove_Point < 3) {
							gomoku_AImove_Point = 3;
							gomoku_AI_MoveX = x;
							gomoku_AI_MoveY = y;
						}
					}// 盤面に白が二つ並んでいて、端のどちらかに石が置かれていない場合白を置くプログラミング
					else if (y < 10 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y + 1] == 2 && gomoku_Banmen[x][y + 2] == 2||
						y > 1 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y - 1] == 2 && gomoku_Banmen[x][y - 2] == 2 ||
						x < 10 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y] == 2 && gomoku_Banmen[x + 2][y] == 2 ||
						x > 1 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y] == 2 && gomoku_Banmen[x - 2][y] == 2 ||
						x < 10 && y < 10 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y + 1] == 2 && gomoku_Banmen[x + 2][y + 2] == 2 ||
						x > 1 && y > 1 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y - 1] == 2 && gomoku_Banmen[x - 2][y - 2] == 2 ||
						x < 10 && y > 1 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y - 1] == 2 && gomoku_Banmen[x + 2][y - 2] == 2 ||
						x > 1 && y < 10 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y + 1] == 2 && gomoku_Banmen[x - 2][y + 2] == 2 ) {
						if (gomoku_AImove_Point < 2) {
							gomoku_AImove_Point = 2;
							gomoku_AI_MoveX = x;
							gomoku_AI_MoveY = y;
						}
					}// 盤面に白が二つ並んでいて、端のどちらかに石が置かれていない場合白を置くプログラミング
					else if (y < 11 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y + 1] == 2 ||
						y > 0 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y - 1] == 2 ||
						x < 11 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y] == 2 ||
						x > 0 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y] == 2 ||
						x < 11 && y < 11 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y + 1] == 2 ||
						x > 0 && y > 0 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y - 1] == 2 ||
						x < 11 && y > 0 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y - 1] == 2 ||
						x > 0 && y < 11 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y + 1] == 2 ) {
						if (gomoku_AImove_Point < 1) {
							gomoku_AImove_Point = 1;
							gomoku_AI_MoveX = x;
							gomoku_AI_MoveY = y;
						}
					}
				}
				gomoku_AI_think = 1;
			}
			if (gomoku_Banmen[gomoku_AI_MoveX][gomoku_AI_MoveY] == 0 && gomoku_Phase == 1) {
				gomoku_Banmen[gomoku_AI_MoveX][gomoku_AI_MoveY] = 2;
				gomoku_AI_MoveX = 0;
				gomoku_AI_MoveY = 0;
				gomoku_Phase = 0;
			}
			for (int r = 0; r < 144 && gomoku_Phase == 1; r++) {
				if (gomoku_Banmen[gomoku_AI_MoveX][gomoku_AI_MoveY] == 0 && gomoku_Phase == 1) {
					gomoku_Banmen[gomoku_AI_MoveX][gomoku_AI_MoveY] = 2;
					gomoku_Phase = 0;
				}
				else {
					gomoku_AI_MoveX++;
				}
				if (gomoku_AI_MoveX > 12 && gomoku_AI_MoveY < 12) {
					gomoku_AI_MoveY++;
					gomoku_AI_MoveX = 0;
				}
			}
		}
		for (int y = 0; y < 13; y++) {
			for (int x = 0; x < 13; x++) {
				// 白(Banmen[x][y] = 2)の勝利判定
				if (gomoku_Banmen[x][y] == 2 && gomoku_Banmen[x + 1][y] == 2 && gomoku_Banmen[x + 2][y] == 2 && gomoku_Banmen[x + 3][y] == 2 && gomoku_Banmen[x + 4][y] == 2 ||
					gomoku_Banmen[x][y] == 2 && gomoku_Banmen[x][y + 1] == 2 && gomoku_Banmen[x][y + 2] == 2 && gomoku_Banmen[x][y + 3] == 2 && gomoku_Banmen[x][y + 4] == 2 ||
					gomoku_Banmen[x][y] == 2 && gomoku_Banmen[x + 1][y + 1] == 2 && gomoku_Banmen[x + 2][y + 2] == 2 && gomoku_Banmen[x + 3][y + 3] == 2 && gomoku_Banmen[x + 4][y + 4] == 2 ||
					gomoku_Banmen[x][y] == 2 && gomoku_Banmen[x - 1][y - 1] == 2 && gomoku_Banmen[x - 2][y - 2] == 2 && gomoku_Banmen[x - 3][y - 3] == 2 && gomoku_Banmen[x - 4][y - 4] == 2 ||
					gomoku_Banmen[x][y] == 2 && gomoku_Banmen[x + 1][y - 1] == 2 && gomoku_Banmen[x + 2][y - 2] == 2 && gomoku_Banmen[x + 3][y - 3] == 2 && gomoku_Banmen[x + 4][y - 4] == 2 ||
					gomoku_Banmen[x][y] == 2 && gomoku_Banmen[x - 1][y + 1] == 2 && gomoku_Banmen[x - 2][y + 2] == 2 && gomoku_Banmen[x - 3][y + 3] == 2 && gomoku_Banmen[x - 4][y + 4] == 2) {
					gomoku_Battle = 2;
				}
			}
		}
	}
	return this;
}

void gomokuScene::Draw() const
{
	DrawGraph(0, 0, gomoku_BackImg, FALSE);
	DrawFormatString(10, 10,0xffffff, "%d", Key_Count);
	DrawGraph(180, 0, TitleImg, TRUE);
	for (int y = 0; y < 13; y++) {
		for (int x = 0; x < 13; x++) {
			DrawFormatString(50, 300, 0xffffff, "%d", bCount);
			DrawFormatString(50, 400, 0xffffff, "%d", wCount);
			if (gomoku_Banmen[x][y] == 1) {
				DrawGraph(270 + (56 * x) + x, -25 + (56 * y) + y, bTopImg, TRUE);
			}
			else if (gomoku_Banmen[x][y] == 2) {
				DrawGraph(270 + (56 * x) + x , -25 + (56 * y) + y, wTopImg, TRUE);
			}
		}
	}
	if (gomoku_Phase == 0 && gomoku_Battle == 0) {
		SetFontSize(60);
		DrawFormatString(50, 300, 0xfffffff, "黒の手番");
	}
	if (gomoku_Phase == 1 && gomoku_Battle == 0) {
		SetFontSize(60);
		DrawFormatString(50, 300, 0xfffffff, "白の手番");
	}
	if (gomoku_Battle == 0) {
		DrawBox(285 + (56 * cX), -15 + (56 * cY), 345 + (56 * cX), 45 + (56 * cY), 0xffff00, FALSE);
	}
	if (gomoku_Battle == 1) {
		SetFontSize(80);
		DrawFormatString(600, 300, 0xFF00FF, ("黒の勝ち"));
	}
	else if (gomoku_Battle == 2) {
		SetFontSize(80);
		DrawFormatString(600, 300, 0xFF00FF, ("白の勝ち"));
	}
	
}
// if(x % 2 == 0 && y % 2 == 0)