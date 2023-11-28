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
	bCount = 0;
	wCount = 0;
	gomoku_Turn = 99;
	gomoku_PlayerTurn = 99;
	gomoku_Pfs = 0;
	gomoku_AITurn = 99;
	gomoku_Efs = 0;
	gomoku_AImove_Point = 0;
	gomoku_AI_MoveX = 0;
	gomoku_AI_MoveY = 0;
	gomoku_AI_think = 0;
	g_OldKey = 0;
	g_NowKey = 0;
	g_KeyFlg = 0;
	for (int y = 0; y < 13; y++)
		for (int x = 0; x < 13; x++) {
			gomoku_Banmen[x][y] = 0;
			}
	gomoku_Phase = 0;
	gomoku_Battle = 0;
	gomoku_TurnSetFlg = 0;
	gomoku_Player_WaitTime = 0;
	gomoku_AI_WaitTime = 0;
	gomoku_Result_WaitTime = 0;
	gomoku_elapsedturn = 0;



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
		if (Key_Count <= 1 && gomoku_TurnSetFlg != 1) {
			gomoku_Turn = (rand() % 2); // 0または1を生成
			gomoku_PlayerTurn = gomoku_Turn;
			gomoku_Pfs = gomoku_PlayerTurn + 1;
			gomoku_TurnSetFlg = 1;
		}
		if (gomoku_PlayerTurn == 0) {
			gomoku_AITurn = 1;
			gomoku_Efs = 2;
		}
		else {
			gomoku_AITurn = 0;
			gomoku_Efs = 1;
		}
		if (gomoku_PlayerTurn == 0 && gomoku_elapsedturn == 0) {
			cX = 6;
			cY = 6;
		}
		if (gomoku_Phase == gomoku_PlayerTurn) {
			gomoku_Player_WaitTime++;
		}
		else {
			gomoku_Player_WaitTime = 0;
		}
		// カーソルを動かす処理
		if (gomoku_Phase == gomoku_PlayerTurn && gomoku_Player_WaitTime > 180) {
			if (g_KeyFlg & PAD_INPUT_RIGHT && cX < 13) {
				if (Key_Count >= 1) {
					cX += 1;
				}
				if (g_KeyFlg & PAD_INPUT_RIGHT && cX == 13) {
					cX = 0;
				}
			}
			if (g_KeyFlg & PAD_INPUT_LEFT && cX > -1) {
				if (Key_Count >= 1) {
					cX -= 1;
				}
				if (g_KeyFlg & PAD_INPUT_LEFT && cX == -1) {
					cX = 12;
				}
			}
			if (g_KeyFlg & PAD_INPUT_DOWN && cY < 13) {
				if (Key_Count >= 1) {
					cY += 1;
				}
				if (g_KeyFlg & PAD_INPUT_DOWN && cY == 13) {
					cY = 0;
				}
			}
			if (g_KeyFlg & PAD_INPUT_UP && cY > -1) {
				if (Key_Count >= 1) {
					cY -= 1;
				}
				if (g_KeyFlg & PAD_INPUT_UP && cY == -1) {
					cY = 12;
				}
			}
		}
		// まだ石が置かれていない盤面に石を置き、手番を交代する
		if (g_KeyFlg & PAD_INPUT_1 && gomoku_Phase == gomoku_PlayerTurn) {
			Key_Count++;
		}
		if (g_KeyFlg & PAD_INPUT_1 && gomoku_Banmen[cX][cY] == 0 && Key_Count >= 2) {
			if (gomoku_Phase == gomoku_PlayerTurn) {
				bCount += 1;
				gomoku_Banmen[cX][cY] = gomoku_Pfs;
				gomoku_elapsedturn++;
				gomoku_Phase = gomoku_AITurn;
			}
		}
		for (int y = 0; y < 13; y++) {
			for (int x = 0; x < 13; x++) {
				// 黒(Banmen[x][y] = 1)の勝利判定
				if (x < 8 && gomoku_Banmen[x][y] == gomoku_Pfs && gomoku_Banmen[x + 1][y] == gomoku_Pfs && gomoku_Banmen[x + 2][y] == gomoku_Pfs && gomoku_Banmen[x + 3][y] == gomoku_Pfs && gomoku_Banmen[x + 4][y] == gomoku_Pfs ||
					x > 3 && gomoku_Banmen[x][y] == gomoku_Pfs && gomoku_Banmen[x - 1][y] == gomoku_Pfs && gomoku_Banmen[x - 2][y] == gomoku_Pfs && gomoku_Banmen[x - 3][y] == gomoku_Pfs && gomoku_Banmen[x - 4][y] == gomoku_Pfs ||
					y < 8 && gomoku_Banmen[x][y] == gomoku_Pfs && gomoku_Banmen[x][y + 1] == gomoku_Pfs && gomoku_Banmen[x][y + 2] == gomoku_Pfs && gomoku_Banmen[x][y + 3] == gomoku_Pfs && gomoku_Banmen[x][y + 4] == gomoku_Pfs ||
					y > 3 && gomoku_Banmen[x][y] == gomoku_Pfs && gomoku_Banmen[x][y - 1] == gomoku_Pfs && gomoku_Banmen[x][y - 2] == gomoku_Pfs && gomoku_Banmen[x][y - 3] == gomoku_Pfs && gomoku_Banmen[x][y - 4] == gomoku_Pfs ||
					x < 8 && y < 8 && gomoku_Banmen[x][y] == gomoku_Pfs && gomoku_Banmen[x + 1][y + 1] == gomoku_Pfs && gomoku_Banmen[x + 2][y + 2] == gomoku_Pfs && gomoku_Banmen[x + 3][y + 3] == gomoku_Pfs && gomoku_Banmen[x + 4][y + 4] == gomoku_Pfs ||
					x > 3 && y > 3 && gomoku_Banmen[x][y] == gomoku_Pfs && gomoku_Banmen[x - 1][y - 1] == gomoku_Pfs && gomoku_Banmen[x - 2][y - 2] == gomoku_Pfs && gomoku_Banmen[x - 3][y - 3] == gomoku_Pfs && gomoku_Banmen[x - 4][y - 4] == gomoku_Pfs ||
					x < 8 && y > 3 && gomoku_Banmen[x][y] == gomoku_Pfs && gomoku_Banmen[x + 1][y - 1] == gomoku_Pfs && gomoku_Banmen[x + 2][y - 2] == gomoku_Pfs && gomoku_Banmen[x + 3][y - 3] == gomoku_Pfs && gomoku_Banmen[x + 4][y - 4] == gomoku_Pfs ||
					x < 8 && y > 3 && gomoku_Banmen[x][y] == gomoku_Pfs && gomoku_Banmen[x - 1][y + 1] == gomoku_Pfs && gomoku_Banmen[x - 2][y + 2] == gomoku_Pfs && gomoku_Banmen[x - 3][y + 3] == gomoku_Pfs && gomoku_Banmen[x - 4][y + 4] == gomoku_Pfs) {
					gomoku_Battle = 1;
				}
			}
		}
		// AI用の変数の初期化
		gomoku_AI_MoveX = 0;
		gomoku_AI_MoveY = 0;
		gomoku_AI_think = 0;
		gomoku_AImove_Point = 0;
		/*gomoku_AI_WaitTime = 0;*/
		// ここからAI
		// 
		if (gomoku_Phase == gomoku_AITurn) {
			gomoku_AI_WaitTime++;
		}
		else {
			gomoku_AI_WaitTime = 0;
		}
		// AIが先攻だったときに必ず行う手
		if (gomoku_AI_WaitTime > 180) {
			if (gomoku_AITurn == 0 && gomoku_Banmen[6][6] == 0 && gomoku_elapsedturn == 0) {
				gomoku_Banmen[5][5] = gomoku_Efs;
				Key_Count++;
				gomoku_elapsedturn++;
				gomoku_Phase = gomoku_PlayerTurn;
			}
			if (gomoku_Battle == 0 && gomoku_Phase == gomoku_AITurn && gomoku_AI_think == 0 && gomoku_elapsedturn > 0) {
				for (int y = 0; y < 13; y++) {
					for (int x = 0; x < 13; x++) {
						if (Key_Count == 2 && gomoku_Banmen[x][y] == gomoku_Pfs && gomoku_AITurn == 1) {
							gomoku_AImove_Point = 100;
							gomoku_AI_MoveX = x + 1;
							gomoku_AI_MoveY = y + 1;
						}
						// 盤面に黒がつ四つ並んでいて、端のどちらかに石が置かれていない場合白を置くプログラミング
						if (y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y + 1] == gomoku_Pfs && gomoku_Banmen[x][y + 2] == gomoku_Pfs && gomoku_Banmen[x][y + 3] == gomoku_Pfs && gomoku_Banmen[x][y + 4] == gomoku_Pfs ||
							y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y - 1] == gomoku_Pfs && gomoku_Banmen[x][y - 2] == gomoku_Pfs && gomoku_Banmen[x][y - 3] == gomoku_Pfs && gomoku_Banmen[x][y - 4] == gomoku_Pfs ||
							x < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y] == gomoku_Pfs && gomoku_Banmen[x + 2][y] == gomoku_Pfs && gomoku_Banmen[x + 3][y] == gomoku_Pfs && gomoku_Banmen[x + 4][y] == gomoku_Pfs ||
							x > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y] == gomoku_Pfs && gomoku_Banmen[x - 2][y] == gomoku_Pfs && gomoku_Banmen[x - 3][y] == gomoku_Pfs && gomoku_Banmen[x - 4][y] == gomoku_Pfs ||
							x < 8 && y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y + 1] == gomoku_Pfs && gomoku_Banmen[x + 2][y + 2] == gomoku_Pfs && gomoku_Banmen[x + 3][y + 3] == gomoku_Pfs && gomoku_Banmen[x + 4][y + 4] == gomoku_Pfs ||
							x > 3 && y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y - 1] == gomoku_Pfs && gomoku_Banmen[x - 2][y - 2] == gomoku_Pfs && gomoku_Banmen[x - 3][y - 3] == gomoku_Pfs && gomoku_Banmen[x - 4][y - 4] == gomoku_Pfs ||
							x < 8 && y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y - 1] == gomoku_Pfs && gomoku_Banmen[x + 2][y - 2] == gomoku_Pfs && gomoku_Banmen[x + 3][y - 3] == gomoku_Pfs && gomoku_Banmen[x + 4][y - 4] == gomoku_Pfs ||
							x > 3 && y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y + 1] == gomoku_Pfs && gomoku_Banmen[x - 2][y + 2] == gomoku_Pfs && gomoku_Banmen[x - 3][y + 3] == gomoku_Pfs && gomoku_Banmen[x - 4][y + 4] == gomoku_Pfs ||
							x < 8 && y < 8 && gomoku_Banmen[x][y] == gomoku_Pfs && gomoku_Banmen[x + 1][y + 1] == 0 && gomoku_Banmen[x + 2][y + 2] == gomoku_Pfs && gomoku_Banmen[x + 3][y + 3] == gomoku_Pfs && gomoku_Banmen[x + 4][y + 4] == gomoku_Pfs) {
							if (gomoku_AImove_Point < 7) {
								gomoku_AImove_Point = 7;
								gomoku_AI_MoveX = x;
								gomoku_AI_MoveY = y;
							}
						}// 盤面に白がつ四つ並んでいて、端のどちらかに石が置かれていない場合白を置くプログラミング
						else if (y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y + 1] == gomoku_Efs && gomoku_Banmen[x][y + 2] == gomoku_Efs && gomoku_Banmen[x][y + 3] == gomoku_Efs && gomoku_Banmen[x][y + 4] == gomoku_Efs ||
							y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y - 1] == gomoku_Efs && gomoku_Banmen[x][y - 2] == gomoku_Efs && gomoku_Banmen[x][y - 3] == gomoku_Efs && gomoku_Banmen[x][y - 4] == gomoku_Efs ||
							x < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y] == gomoku_Efs && gomoku_Banmen[x + 2][y] == gomoku_Efs && gomoku_Banmen[x + 3][y] == gomoku_Efs && gomoku_Banmen[x + 4][y] == gomoku_Efs ||
							x > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y] == gomoku_Efs && gomoku_Banmen[x - 2][y] == gomoku_Efs && gomoku_Banmen[x - 3][y] == gomoku_Efs && gomoku_Banmen[x - 4][y] == gomoku_Efs ||
							x < 8 && y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y + 1] == gomoku_Efs && gomoku_Banmen[x + 2][y + 2] == gomoku_Efs && gomoku_Banmen[x + 3][y + 3] == gomoku_Efs && gomoku_Banmen[x + 4][y + 4] == gomoku_Efs ||
							x > 3 && y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y - 1] == gomoku_Efs && gomoku_Banmen[x - 2][y - 2] == gomoku_Efs && gomoku_Banmen[x - 3][y - 3] == gomoku_Efs && gomoku_Banmen[x - 4][y - 4] == gomoku_Efs ||
							x < 8 && y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y - 1] == gomoku_Efs && gomoku_Banmen[x + 2][y - 2] == gomoku_Efs && gomoku_Banmen[x + 3][y - 3] == gomoku_Efs && gomoku_Banmen[x + 4][y - 4] == gomoku_Efs ||
							x > 3 && y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y + 1] == gomoku_Efs && gomoku_Banmen[x - 2][y + 2] == gomoku_Efs && gomoku_Banmen[x - 3][y + 3] == gomoku_Efs && gomoku_Banmen[x - 4][y + 4] == gomoku_Efs) {
							gomoku_AImove_Point = 99;
							gomoku_AI_MoveX = x;
							gomoku_AI_MoveY = y;
						}// 盤面に白が三つ並んでいて、両端に石が置かれていない場合白を置くプログラミング
						else if (y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y + 1] == gomoku_Efs && gomoku_Banmen[x][y + 2] == gomoku_Efs && gomoku_Banmen[x][y + 3] == gomoku_Efs && gomoku_Banmen[x][y + 4] == 0 ||
							y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y - 1] == gomoku_Efs && gomoku_Banmen[x][y - 2] == gomoku_Efs && gomoku_Banmen[x][y - 3] == gomoku_Efs && gomoku_Banmen[x][y - 4] == 0 ||
							x < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y] == gomoku_Efs && gomoku_Banmen[x + 2][y] == gomoku_Efs && gomoku_Banmen[x + 3][y] == gomoku_Efs && gomoku_Banmen[x + 4][y] == 0 ||
							x > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y] == gomoku_Efs && gomoku_Banmen[x - 2][y] == gomoku_Efs && gomoku_Banmen[x - 3][y] == gomoku_Efs && gomoku_Banmen[x - 4][y] == 0 ||
							x < 8 && y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y + 1] == gomoku_Efs && gomoku_Banmen[x + 2][y + 2] == gomoku_Efs && gomoku_Banmen[x + 3][y + 3] == gomoku_Efs && gomoku_Banmen[x + 4][y + 4] == 0 ||
							x > 3 && y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y - 1] == gomoku_Efs && gomoku_Banmen[x - 2][y - 2] == gomoku_Efs && gomoku_Banmen[x - 3][y - 3] == gomoku_Efs && gomoku_Banmen[x - 4][y - 4] == 0 ||
							x < 8 && y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y - 1] == gomoku_Efs && gomoku_Banmen[x + 2][y - 2] == gomoku_Efs && gomoku_Banmen[x + 3][y - 3] == gomoku_Efs && gomoku_Banmen[x + 4][y - 4] == 0 ||
							x > 3 && y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y + 1] == gomoku_Efs && gomoku_Banmen[x - 2][y + 2] == gomoku_Efs && gomoku_Banmen[x - 3][y + 3] == gomoku_Efs && gomoku_Banmen[x - 4][y + 4] == 0) {
							if (gomoku_AImove_Point < 6) {
								gomoku_AImove_Point = 6;
								gomoku_AI_MoveX = x;
								gomoku_AI_MoveY = y;
							}
						}// 盤面に黒が三つ並んでいて、両端に石が置かれていない場合白を置くプログラミング
						else if (y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y + 1] == gomoku_Pfs && gomoku_Banmen[x][y + 2] == gomoku_Pfs && gomoku_Banmen[x][y + 3] == gomoku_Pfs && gomoku_Banmen[x][y + 4] == 0 ||
							y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y - 1] == gomoku_Pfs && gomoku_Banmen[x][y - 2] == gomoku_Pfs && gomoku_Banmen[x][y - 3] == gomoku_Pfs && gomoku_Banmen[x][y - 4] == 0 ||
							x < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y] == gomoku_Pfs && gomoku_Banmen[x + 2][y] == gomoku_Pfs && gomoku_Banmen[x + 3][y] == gomoku_Pfs && gomoku_Banmen[x + 4][y] == 0 ||
							x > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y] == gomoku_Pfs && gomoku_Banmen[x - 2][y] == gomoku_Pfs && gomoku_Banmen[x - 3][y] == gomoku_Pfs && gomoku_Banmen[x - 4][y] == 0 ||
							x < 8 && y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y + 1] == gomoku_Pfs && gomoku_Banmen[x + 2][y + 2] == gomoku_Pfs && gomoku_Banmen[x + 3][y + 3] == gomoku_Pfs && gomoku_Banmen[x + 4][y + 4] == 0 ||
							x > 3 && y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y - 1] == gomoku_Pfs && gomoku_Banmen[x - 2][y - 2] == gomoku_Pfs && gomoku_Banmen[x - 3][y - 3] == gomoku_Pfs && gomoku_Banmen[x - 4][y - 4] == 0 ||
							x < 8 && y > 3 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y - 1] == gomoku_Pfs && gomoku_Banmen[x + 2][y - 2] == gomoku_Pfs && gomoku_Banmen[x + 3][y - 3] == gomoku_Pfs && gomoku_Banmen[x + 4][y - 4] == 0 ||
							x > 3 && y < 8 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y + 1] == gomoku_Pfs && gomoku_Banmen[x - 2][y + 2] == gomoku_Pfs && gomoku_Banmen[x - 3][y + 3] == gomoku_Pfs && gomoku_Banmen[x - 4][y + 4] == 0) {
							if (gomoku_AImove_Point < 5) {
								gomoku_AImove_Point = 5;
								gomoku_AI_MoveX = x;
								gomoku_AI_MoveY = y;
							}
						}// 盤面に白が三つ並んでいて、端のどちらかに石が置かれていない場合白を置くプログラミング
						else if (y < 9 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y + 1] == gomoku_Efs && gomoku_Banmen[x][y + 2] == gomoku_Efs && gomoku_Banmen[x][y + 3] == gomoku_Efs ||
							y > 2 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y - 1] == gomoku_Efs && gomoku_Banmen[x][y - 2] == gomoku_Efs && gomoku_Banmen[x][y - 3] == gomoku_Efs ||
							x < 9 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y] == gomoku_Efs && gomoku_Banmen[x + 2][y] == gomoku_Efs && gomoku_Banmen[x + 3][y] == gomoku_Efs ||
							x > 2 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y] == gomoku_Efs && gomoku_Banmen[x - 2][y] == gomoku_Efs && gomoku_Banmen[x - 3][y] == gomoku_Efs ||
							x < 9 && y < 9 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y + 1] == gomoku_Efs && gomoku_Banmen[x + 2][y + 2] == gomoku_Efs && gomoku_Banmen[x + 3][y + 3] == gomoku_Efs ||
							x > 2 && y > 9 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y - 1] == gomoku_Efs && gomoku_Banmen[x - 2][y - 2] == gomoku_Efs && gomoku_Banmen[x - 3][y - 3] == gomoku_Efs ||
							x < 9 && y > 2 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y - 1] == gomoku_Efs && gomoku_Banmen[x + 2][y - 2] == gomoku_Efs && gomoku_Banmen[x + 3][y - 3] == gomoku_Efs ||
							x > 2 && y < 9 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y + 1] == gomoku_Efs && gomoku_Banmen[x - 2][y + 2] == gomoku_Efs && gomoku_Banmen[x - 3][y + 3] == gomoku_Efs) {
							if (gomoku_AImove_Point < 4) {
								gomoku_AImove_Point = 4;
								gomoku_AI_MoveX = x;
								gomoku_AI_MoveY = y;
							}
						}// 盤面に黒が三つ並んでいて、端のどちらかに石が置かれていない場合白を置くプログラミング
						else if (y < 9 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y + 1] == gomoku_Pfs && gomoku_Banmen[x][y + 2] == gomoku_Pfs && gomoku_Banmen[x][y + 3] == gomoku_Pfs ||
							y > 2 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y - 1] == gomoku_Pfs && gomoku_Banmen[x][y - 2] == gomoku_Pfs && gomoku_Banmen[x][y - 3] == gomoku_Pfs ||
							x < 9 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y] == gomoku_Pfs && gomoku_Banmen[x + 2][y] == gomoku_Pfs && gomoku_Banmen[x + 3][y] == gomoku_Pfs ||
							x > 2 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y] == gomoku_Pfs && gomoku_Banmen[x - 2][y] == gomoku_Pfs && gomoku_Banmen[x - 3][y] == gomoku_Pfs ||
							x < 9 && y < 9 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y + 1] == gomoku_Pfs && gomoku_Banmen[x + 2][y + 2] == gomoku_Pfs && gomoku_Banmen[x + 3][y + 3] == gomoku_Pfs ||
							x > 2 && y > 2 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y - 1] == gomoku_Pfs && gomoku_Banmen[x - 2][y - 2] == gomoku_Pfs && gomoku_Banmen[x - 3][y - 3] == gomoku_Pfs ||
							x < 9 && y > 2 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y - 1] == gomoku_Pfs && gomoku_Banmen[x + 2][y - 2] == gomoku_Pfs && gomoku_Banmen[x + 3][y - 3] == gomoku_Pfs ||
							x > 2 && y < 9 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y + 1] == gomoku_Pfs && gomoku_Banmen[x - 2][y + 2] == gomoku_Pfs && gomoku_Banmen[x - 3][y + 3] == gomoku_Pfs) {
							if (gomoku_AImove_Point < 3) {
								gomoku_AImove_Point = 3;
								gomoku_AI_MoveX = x;
								gomoku_AI_MoveY = y;
							}
						}// 盤面に白が二つ並んでいて、端のどちらかに石が置かれていない場合白を置くプログラミング
						else if (y < 10 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y + 1] == gomoku_Efs && gomoku_Banmen[x][y + 2] == gomoku_Efs ||
							y > 1 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y - 1] == gomoku_Efs && gomoku_Banmen[x][y - 2] == gomoku_Efs ||
							x < 10 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y] == gomoku_Efs && gomoku_Banmen[x + 2][y] == gomoku_Efs ||
							x > 1 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y] == gomoku_Efs && gomoku_Banmen[x - 2][y] == gomoku_Efs ||
							x < 10 && y < 10 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y + 1] == gomoku_Efs && gomoku_Banmen[x + 2][y + 2] == gomoku_Efs ||
							x > 1 && y > 1 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y - 1] == gomoku_Efs && gomoku_Banmen[x - 2][y - 2] == gomoku_Efs ||
							x < 10 && y > 1 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y - 1] == gomoku_Efs && gomoku_Banmen[x + 2][y - 2] == gomoku_Efs ||
							x > 1 && y < 10 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y + 1] == gomoku_Efs && gomoku_Banmen[x - 2][y + 2] == gomoku_Efs) {
							if (gomoku_AImove_Point < 2) {
								gomoku_AImove_Point = 2;
								gomoku_AI_MoveX = x;
								gomoku_AI_MoveY = y;
							}
						}// 盤面に白が一つ並んでいて、端のどちらかに石が置かれていない場合白を置くプログラミング
						else if (y < 11 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y + 1] == gomoku_Efs ||
							y > 0 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x][y - 1] == gomoku_Efs ||
							x < 11 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y] == gomoku_Efs ||
							x > 0 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y] == gomoku_Efs ||
							x < 11 && y < 11 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y + 1] == gomoku_Efs ||
							x > 0 && y > 0 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y - 1] == gomoku_Efs ||
							x < 11 && y > 0 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x + 1][y - 1] == gomoku_Efs ||
							x > 0 && y < 11 && gomoku_Banmen[x][y] == 0 && gomoku_Banmen[x - 1][y + 1] == gomoku_Efs) {
							if (gomoku_AImove_Point < 1) {
								gomoku_AImove_Point = 1;
								gomoku_AI_MoveX = x;
								gomoku_AI_MoveY = y;
							}



						}
					}
					gomoku_AI_think = 1;
				}
				if (gomoku_Banmen[gomoku_AI_MoveX][gomoku_AI_MoveY] == 0 && gomoku_Phase == gomoku_AITurn) {
					gomoku_Banmen[gomoku_AI_MoveX][gomoku_AI_MoveY] = gomoku_Efs;
					gomoku_AI_MoveX = 0;
					gomoku_AI_MoveY = 0;
					gomoku_elapsedturn++;
					gomoku_Phase = gomoku_PlayerTurn;
				}
				for (int r = 0; r < 144 && gomoku_Phase == gomoku_AITurn; r++) {
					if (gomoku_Banmen[gomoku_AI_MoveX][gomoku_AI_MoveY] == 0 && gomoku_Phase == gomoku_AITurn) {
						gomoku_Banmen[gomoku_AI_MoveX][gomoku_AI_MoveY] = gomoku_Efs;
						gomoku_elapsedturn++;
						gomoku_Phase = gomoku_PlayerTurn;
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
					if (x < 8 && gomoku_Banmen[x][y] == gomoku_Efs && gomoku_Banmen[x + 1][y] == gomoku_Efs && gomoku_Banmen[x + 2][y] == gomoku_Efs && gomoku_Banmen[x + 3][y] == gomoku_Efs && gomoku_Banmen[x + 4][y] == gomoku_Efs ||
						y < 8 && gomoku_Banmen[x][y] == gomoku_Efs && gomoku_Banmen[x][y + 1] == gomoku_Efs && gomoku_Banmen[x][y + 2] == gomoku_Efs && gomoku_Banmen[x][y + 3] == gomoku_Efs && gomoku_Banmen[x][y + 4] == gomoku_Efs ||
						x < 8 && y < 8 && gomoku_Banmen[x][y] == gomoku_Efs && gomoku_Banmen[x + 1][y + 1] == gomoku_Efs && gomoku_Banmen[x + 2][y + 2] == gomoku_Efs && gomoku_Banmen[x + 3][y + 3] == gomoku_Efs && gomoku_Banmen[x + 4][y + 4] == gomoku_Efs ||
						x > 3 && y > 3 && gomoku_Banmen[x][y] == gomoku_Efs && gomoku_Banmen[x - 1][y - 1] == gomoku_Efs && gomoku_Banmen[x - 2][y - 2] == gomoku_Efs && gomoku_Banmen[x - 3][y - 3] == gomoku_Efs && gomoku_Banmen[x - 4][y - 4] == gomoku_Efs ||
						x < 8 && y > 3 && gomoku_Banmen[x][y] == gomoku_Efs && gomoku_Banmen[x + 1][y - 1] == gomoku_Efs && gomoku_Banmen[x + 2][y - 2] == gomoku_Efs && gomoku_Banmen[x + 3][y - 3] == gomoku_Efs && gomoku_Banmen[x + 4][y - 4] == gomoku_Efs ||
						x > 3 && y < 8 && gomoku_Banmen[x][y] == gomoku_Efs && gomoku_Banmen[x - 1][y + 1] == gomoku_Efs && gomoku_Banmen[x - 2][y + 2] == gomoku_Efs && gomoku_Banmen[x - 3][y + 3] == gomoku_Efs && gomoku_Banmen[x - 4][y + 4] == gomoku_Efs) {
						gomoku_Battle = 2;
					}
				}
			}
		}
	}
	else {
		gomoku_Result_WaitTime++;
		if (gomoku_Result_WaitTime > 210 && g_KeyFlg & PAD_INPUT_1 && gomoku_Battle == 1 || gomoku_Battle == 2) {
				return new gomokuTitle();
			}
	}
	return this;
}


void gomokuScene::Draw() const
{
	DrawGraph(0, 0, gomoku_BackImg, FALSE);
	DrawFormatString(10, 10,0xffffff, "%d", gomoku_Result_WaitTime);
	DrawGraph(180, 0, TitleImg, TRUE);
	for (int y = 0; y < 13; y++) {
		for (int x = 0; x < 13; x++) {
			if (gomoku_Banmen[x][y] == 1) {
				DrawGraph(270 + (56 * x) + x, -25 + (56 * y) + y, bTopImg, TRUE);
			}
			else if (gomoku_Banmen[x][y] == 2) {
				DrawGraph(270 + (56 * x) + x , -25 + (56 * y) + y, wTopImg, TRUE);
			}
		}
	}
	if (gomoku_Player_WaitTime > 60 && gomoku_Player_WaitTime < 150 && gomoku_Battle == 0 && gomoku_elapsedturn != 0) {
		SetFontSize(80);
		DrawFormatString(500, 300, 0xFF00FF, "自分の手番");
	}
	else if (gomoku_elapsedturn == 0 && gomoku_TurnSetFlg == 1 && gomoku_Player_WaitTime > 0 && gomoku_Player_WaitTime < 90 && gomoku_Battle == 0) {
		SetFontSize(80);
		DrawFormatString(500, 300, 0xFF00FF, "自分の手番");
	}
	if (gomoku_AI_WaitTime > 60 && gomoku_AI_WaitTime < 150 && gomoku_Battle == 0 && gomoku_elapsedturn != 0) {
		SetFontSize(80);
		DrawFormatString(500, 300, 0xFF00FF, "相手の手番");
	}
	else if (gomoku_elapsedturn == 0 && gomoku_TurnSetFlg == 1 && gomoku_AI_WaitTime > 0 && gomoku_AI_WaitTime < 90 && gomoku_Battle == 0){
		SetFontSize(80);
		DrawFormatString(500, 300, 0xFF00FF, "相手の手番");
	}
	if (gomoku_Battle == 0 && gomoku_Phase == gomoku_PlayerTurn) {
		DrawBox(285 + (56 * cX), -15 + (56 * cY), 345 + (56 * cX), 45 + (56 * cY), 0xffff00, FALSE);
	}
	if (gomoku_Battle == 1) {
		SetFontSize(80);
		DrawFormatString(500, 300, 0xFF00FF, ("WIN"));
	}
	else if (gomoku_Battle == 2) {
		SetFontSize(80);
		DrawFormatString(500, 300, 0xFF00FF, ("LOSE"));
	}
	if (gomoku_Battle != 0 && gomoku_Result_WaitTime > 150) {
		DrawFormatString(600, 600, 0x000000, ("Aボタンでタイトルに戻る"));
	}
	
}
// プレイヤーターン
//void gomokuScene::gomoku_Player_Turn()
//{
//}
//// AI処理用関数
//void gomokuScene::gomoku_AI_Turn()
//{
//	
//}