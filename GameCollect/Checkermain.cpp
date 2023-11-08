#pragma once
#include "Checkermain.h"
#include "DxLib.h"

Checkermain::Checkermain() {
    // 画像を読み込み、初期化
    Boardimg = LoadGraph("../images/Checkers/banmen.png");    // ボード
    PieceB = LoadGraph("../images/Checkers/WK.png");         // 駒黒
    PieceW = LoadGraph("../images/Checkers/BK.png");         // 駒白
    Checkerback = LoadGraph("../images/Checkers/back.png");  // 背景
    selectX = 0;                                             // カーソル移動X座標
    selectY = 0;                                             // カーソル移動Y座標
    phase = 0;                                               // 先攻後攻のフラグ
    F_select = false; // 駒の選択状態を初期化
    StartX = 0;      // 移動元X座標
    StartY = 0;      // 移動元Y座標
    SelectX = 0;     // 移動先X座標
    SelectY = 0;     // 移動先Y座標
    jumpedX = 0;
    jumpedY = 0;
}

Checkermain::~Checkermain() {
    // デストラクタ
}

AbstractScene* Checkermain::Update() {
    // キー入力の状態を更新
    g_OldKey = g_NowKey;
    g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    g_KeyFlg = g_NowKey & ~g_OldKey;

    // カーソルを動かす処理
    if (g_KeyFlg & PAD_INPUT_RIGHT && selectX < 7) {
        selectX += 1;
    }
    if (g_KeyFlg & PAD_INPUT_LEFT && selectX > 0) {
        selectX -= 1;
    }
    if (g_KeyFlg & PAD_INPUT_DOWN && selectY < 7) {
        selectY += 1;
    }
    if (g_KeyFlg & PAD_INPUT_UP && selectY > 0) {
        selectY -= 1;
    }

    // 駒の移動
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (phase == 0) {
                if (g_KeyFlg & PAD_INPUT_1 && board[selectX][selectY] == 1) {
                    StartX = selectX;
                    StartY = selectY;
                    F_select = true;
                }
                if (g_KeyFlg & PAD_INPUT_1 && board[selectX][selectY] == 0) {
                    SelectX = selectX;
                    SelectY = selectY;
                    F_select = false;
                    if (IsMoveValid(StartX, StartY, SelectX, SelectY)) {
                        board[SelectX][SelectY] = 1;
                        board[StartX][StartY] = 0;
                        phase = 1;
                    }
                }
            }
            else if (phase == 1) {
                if (g_KeyFlg & PAD_INPUT_1 && board[selectX][selectY] == 2) {
                    StartX = selectX;
                    StartY = selectY;
                    F_select = true;
                }
                if (g_KeyFlg & PAD_INPUT_1 && board[selectX][selectY] == 0) {
                    SelectX = selectX;
                    SelectY = selectY;
                    F_select = false;
                    if (IsMoveValid(StartX, StartY, SelectX, SelectY)) {
                        board[SelectX][SelectY] = 2;
                        board[StartX][StartY] = 0;
                        phase = 0;
                    }
                }
            }
            // ゲームオーバー
            if (board[x][y] == 0) {

            }
        }
      
    }
   

    return this;
}

void Checkermain::Draw() const {
    // 背景を描画
    DrawGraph(0, 0, Checkerback, FALSE);
    // ボードを描画
    DrawGraph(300, 0, Boardimg, TRUE);

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
    // 成金の駒を描画
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (board[x][y] == 3) {
                DrawCircle(x * 74 + 400, y * 72 + 105, 28, GetColor(255,255, 0), TRUE);
            }
        }
    }

    // カーソルの位置に四角形を描画
    DrawBox(372 + (selectX * 71), 72 + (selectY * 71), 445 + (selectX * 71), 145 + (selectY * 71), GetColor(0, 250, 0), FALSE);

    // デバッグ情報を表示
    DrawFormatString(0, 0, 0x000000, "Y: %d", selectY); // カーソル移動Y
    DrawFormatString(0, 30, 0x000000, "X: %d", selectX); // カーソル移動X
    DrawFormatString(0, 100, 0x000000, "F_select: %d", F_select);
}

void Checkermain::InitBoard() {
    // チェッカーボードの初期化
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = 0;
        }
    }
}

bool Checkermain::IsMoveValid(int startX, int startY, int SelectX, int SelectY) {
    // 移動先がボードの範囲外である場合、無効
    if (SelectX < 0 || SelectY < 0 || SelectX >= 8 || SelectY >= 8) {
        return false;
    }

    // 移動先にすでに駒がある場合、無効
    if (board[SelectX][SelectY] != 0) {
        return false;
    }

   

    // 移動先が隣接している場合（通常の移動）
    if (abs(SelectX - startX) == 1 && SelectY - startY == 1) {
        // 1つ前に進むことが許可される条件を追加
        if (board[startX][startY] == 1 || board[startX][startY] == 3) {
            return true;
        }
    }
    if (abs(SelectX - startX) == -1 && SelectY - startY == 1) {
        // 1つ前に進むことが許可される条件を追加
        if (board[startX][startY] == 1 || board[startX][startY] == 2) {
            return true;
        }
    }
    if (abs(SelectX - startX) == 1 && SelectY - startY == -1) {
        // 1つ前に進むことが許可される条件を追加
        if (board[startX][startY] == 2 || board[startX][startY] == 3) {
            return true;
        }
    }
    if (abs(SelectX - startX) == -1 && SelectY - startY == -1) {
        // 1つ前に進むことが許可される条件を追加
        if (board[startX][startY] == 2 || board[startX][startY] == 3) {
            return true;
        }
    }
    // 移動先が斜めに1つずつ移動する場合（成金の移動）
    if (abs(SelectX - startX) == 1 && abs(SelectY - startY) == 1) {
        if (board[startX][startY] == 3) {
            return true;
        }
    }
    // 移動先が斜めに2つ飛び越える場合（ジャンプ）
    if (abs(SelectX - startX) == 2 && abs(SelectY - startY) == 2) {
        jumpedX = (SelectX + startX) / 2;
        jumpedY = (SelectY + startY) / 2;

        // 飛び越えた位置に相手の駒があるか確認
        if (board[jumpedX][jumpedY] != 0) {
            // 飛び越えた相手の駒を削除
            board[jumpedX][jumpedY] = 0;

            // 駒が自陣地の端に到達したら成金になる
            if (SelectY == 0 || SelectY==7) {
                board[SelectX][SelectY] = 3; // 3は成金を表す
            }

            return true;
        }
    }
   
    return false; // 上記の条件に該当しない場合、無効な移動
}
