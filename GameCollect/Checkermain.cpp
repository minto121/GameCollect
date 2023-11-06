#include "Checkermain.h"
#include "DxLib.h"
#include "PadInput.h"

Checkermain::Checkermain() {

	Boardimg = LoadGraph("../images/Checkers/banmen.png");		 // ボード
	PieceB = LoadGraph("../images/Checkers/WK.png");			 // 駒黒
	PieceW = LoadGraph("../images/Checkers/BK.png");			 // 駒白
	Checkerback = LoadGraph("../images/Checkers/back.png");		 // 背景
	selectX = 0;												 // カーソル移動X座標
	selectY = 0;												 // カーソル移動Y座標
	phase = 0;
}

Checkermain::~Checkermain()
{
}


AbstractScene* Checkermain::Update()
{
	g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;

	// カーソルを動かす処理
	if (phase == 0) {
		if (g_KeyFlg & PAD_INPUT_RIGHT && selectX < 8) {
			selectX += 1;
		}
		if (g_KeyFlg & PAD_INPUT_LEFT && selectX > 0) {
			selectX -= 1;
		}
		if (g_KeyFlg & PAD_INPUT_DOWN && selectY < 8) {
			selectY += 1;
		}
		if (g_KeyFlg & PAD_INPUT_UP && selectY > 0) {
			selectY -= 1;
		}
	}

	// 駒の移動
	 // 駒の移動
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (g_KeyFlg & PAD_INPUT_1) {
				if (board[x][y] == 1 && phase == 0) {
				/*	int StartX = x;
					int StartY = y;
					int SelectX = selectX;
					int SelectY = selectY;*/
					//if (IsMoveValid(StartX, StartY, SelectX, SelectY)) {
						board[selectX][selectY] = 0;  // ここで = を使って値を代入する
						F_select = TRUE;
					//}
				}
				/*else if (board[x][y] == 0 && F_select) {
					if (IsPlaceValid(x, y)) {
						board[x][y] = 1;
						F_select = FALSE;
					}
				}*/
			}
			
		}
	}

	/*for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (g_KeyFlg & PAD_INPUT_1 && board[selectX][selectY] == 1) {
				if (phase==0) {
					board[selectX][selectY] == 0;
					F_select = TRUE;
				}
			}
			if (g_KeyFlg & PAD_INPUT_1&& board[selectX][selectY] == 0) {
				if (F_select == TRUE) {
					board[selectX][selectY] = 1;
					
					F_select = FALSE;
				}
			}
		}
	}*/

	


	return this;
}

void Checkermain::Draw() const
{
	DrawGraph(0, 0, Checkerback, FALSE);    // 背景
	DrawGraph(300, 0, Boardimg, TRUE);      // ボード

	// プレイヤー1の駒を描画
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (board[x][y] == 2) {
				DrawRotaGraph(x * 74 + 400, y * 72 + 108, 2, 0, PieceB, TRUE);
			}
		}
	}

	// プレイヤー2の駒を描画
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (board[x][y] == 1) {
				DrawCircle(x * 74 + 400, y * 72 + 105, 28, GetColor(255, 0, 0), TRUE);
			}
		}
	}

	// カーソルの位置に四角形を描画
	DrawBox(372 + (selectX * 71), 72 + (selectY * 71), 445 + (selectX * 71), 145 + (selectY * 71), GetColor(0, 250, 0), FALSE);

	DrawFormatString(0, 0, 0x000000, "Y: %d", selectY); // カーソル移動Y
	DrawFormatString(0, 30, 0x000000, "X: %d", selectX); // カーソル移動X
	DrawFormatString(0, 100, 0x000000, "F_select: %d", F_select);
}

void Checkermain::InitBoard()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			(board[i][j] = 0);

		}
	}
}
bool Checkermain::IsMoveValid(int startX, int startY, int SelectX, int SelectY)
{
	// 移動先がボードの範囲外である場合、無効
	if (SelectX < 0 || SelectY < 0 || SelectX >= 8 || SelectY >= 8) {
		return false;
	}

	// 移動先にすでに駒がある場合、無効
	if (board[SelectY][SelectX] != 0) {
		return false;
	}

	// 移動先が隣接している場合（通常の移動）
	if (abs(SelectX - startX) == 1 && abs(SelectY - startY) == 1) {
		return true;
	}

	// 移動先が斜めに2つ飛び越える場合（ジャンプ）
	if (abs(SelectX - startX) == 2 && abs(SelectY - startY) == 2) {
		int jumpedX = (SelectX + startX) / 2;
		int jumpedY = (SelectY + startY) / 2;

		// 飛び越えた位置に相手の駒があるか確認
		if (board[jumpedY][jumpedX] == 1) {
			return true;
		}
	}

	return false; // 上記の条件に該当しない場合、無効な移動
}
bool Checkermain::IsPlaceValid(int i, int j)
{
	// 移動先がボードの範囲外である場合、無効
	if (i < 0 || j < 0 || i >= 8 || j >= 8) {
		return false;
	}

	// 移動先にすでに駒がある場合、無効
	if (board[j][i] != 0) {
		return false;
	}

	return true; // 上記の条件に該当しない場合、有効な位置
	
}




