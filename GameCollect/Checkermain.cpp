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
}

Checkermain::~Checkermain()
{
}


AbstractScene* Checkermain::Update()
{
	g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;
	//上移動
	if (g_KeyFlg & PAD_INPUT_UP) {
		if (selectY >= 0 && selectY <= 7) {
			selectY = selectY - 1;
		}
		if (selectY < 0) {
			selectY = 7;
		}
	}
	//下移動
	if (g_KeyFlg & PAD_INPUT_DOWN) {
		if (selectY >=0  && selectY < 8) {
			selectY = selectY + 1;
		}
		if (selectY > 7 ) {
			selectY = 0;
		}
	}
	//右移動
	if (g_KeyFlg & PAD_INPUT_LEFT) {
		if (selectX >= 0 && selectX <= 7) {
			selectX = selectX - 1;
		}
		if (selectX < 0) {
			selectX = 7;
		}
	}
	//左移動
	if (g_KeyFlg & PAD_INPUT_RIGHT) {
		if (selectX >= 0 && selectX < 8) {
			selectX = selectX + 1;
		}
		if (selectX > 7) {
			selectX = 0;
		}
	}
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (g_KeyFlg & PAD_INPUT_1) {

				if (phase == 0 && board[x][y] == 1) {
					F_select = TRUE;

				}
			}
			if (F_select == TRUE && board[x-1][y-1]) {
				board[x - 1][y - 1] = 1;
				board[x][y] = 0;
			}
			if (F_select == TRUE && board[x - 1][y - 1]) {
				board[x + 1][y + 1] = 1;
				board[x][y] = 0;
			}
		}
		int padx, pady;
		// カーソルの位置からクリックされたセルを特定
		int clickedX = selectX;
		int clickedY = selectY;
		
		// プレイヤーが選択した駒の座標が (selectedX, selectedY) にあります
        // ここで移動の妥当性をチェックし、駒の移動を処理します
		//IsMoveValid(selectX,  selectY,  clickedX,  clickedY);
	
	}


	return this;
}

void Checkermain::Draw() const
{
	
	DrawGraph(0, 0, Checkerback, FALSE);	// 背景
	DrawGraph(300, 0, Boardimg, TRUE);		// ボード
	 //プレイヤー1の駒を描画
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if(board[x][y]==2)
			DrawRotaGraph(x * 74 + 400, y * 72 + 108, 2, 0, PieceB, TRUE);
		}
	}
	// プレイヤー2の駒を描画
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (board[x][y] == 1)
				DrawCircle(x * 74 + 400, y * 72 + 105, 28, GetColor(255, 0, 0), TRUE);
		}
	}

	//for (int y = 0; y < 3; y++) {
	//	for (int x = (y % 2 == 0) ? 1 : 0; x < 8; x += 2) {
	//		DrawCircle(x * 73 + 400, y * 75 + 100, 28, GetColor(255, 0, 0), TRUE);
	//		/*DrawRotaGraph(x * 75 + 400, y * 80 + 110, 2, 0, PieceW, TRUE);*/
	//	}
	//}
	DrawBox(372 + (selectX * 71), 72 + (selectY * 71), 445 + (selectX * 71), 145 + (selectY * 71), GetColor(0, 250, 0), FALSE);    // 四角形を描画

	DrawFormatString(0, 0, 0x000000, "%d", selectY);		//カーソル移動Y
	DrawFormatString(0,30, 0x000000, "%d", selectX);		//カーソル移動X
	DrawFormatString(0, 100, 0x000000, "%d", F_select);


	
}

void Checkermain::InitBoard()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			(board[i][j] == 0);

		}
	}
}
bool Checkermain::IsMoveValid(int startX, int startY, int endX, int endY)
{
	// 移動の妥当性をチェックするロジックをここに追加
	// 飛び越えるルールなども実装可能

	if (endX < 0 || endY < 0 || endX >= 8 || endY >= 8) {
		return false; // ボード外への移動は無効
	}

	if (board[endY][endX] != 0) {
		return false; // 移動先に駒がある場合は無効
	}

	// 1つ前後左右に移動する場合
	if (abs(endX - startX) == 1 && abs(endY - startY) == 1) {
		return true;
	}

	// 駒の移動ルールに合致しない場合もここでチェック
	// 他のカスタムルールを実装するなど、他の条件にも従うことができます

	return false; // デフォルトでは無効な移動として扱う
}



