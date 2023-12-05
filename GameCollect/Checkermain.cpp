#pragma once
#include "Checkermain.h"
#include "DxLib.h"

Checkermain::Checkermain() {
    // 画像を読み込み、初期化
    Boardimg = LoadGraph("../images/Checkers/banmen.png");   // ボード
    PieceB = LoadGraph("../images/Checkers/WK.png");         // 駒黒
    PieceR = LoadGraph("../images/Checkers/RD.png");         // 駒赤
    PieceBK = LoadGraph("../images/Checkers/KB.png");        //kingkuro
    PieceRK=LoadGraph("../images/Checkers/KR.png");          //kingaka
    Checkerback = LoadGraph("../images/Checkers/back.png");  // 背景
    selectX = 0;                                             // カーソル移動X座標
    selectY = 0;                                             // カーソル移動Y座標
    phase = 0;                                               // 先攻後攻のフラグ
    F_select = false;                                        // 駒の選択状態を初期化
    movevail = false;                                        // 移動が有効かどうかを表す
    cantake = false;
    StartX = 0;                                              // 移動元X座標
    StartY = 0;                                              // 移動元Y座標
    SelectX = 0;                                             // 移動先X座標
    SelectY = 0;                                             // 移動先Y座標
    jumpedX = 0;
    jumpedY = 0;
    player1Pieces = 12;                                      // プレイヤー1の駒の数
    player2Pieces = 12;                                      // プレイヤー2の駒の数
}

Checkermain::~Checkermain() {
    // デストラクタ
}

AbstractScene* Checkermain::Update() {

    /*Gameover();*/
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
                if (g_KeyFlg & PAD_INPUT_1 && (board[selectX][selectY] == 1)) {
                    StartX = selectX;
                    StartY = selectY;
                    F_select = true;
                }
                else if (g_KeyFlg & PAD_INPUT_1 && (board[selectX][selectY] == 4)) {
                    StartX = selectX;
                    StartY = selectY;
                    F_select = true;
                }
                if (g_KeyFlg & PAD_INPUT_1 && board[selectX][selectY] == 0 ) {
                    SelectX = selectX;
                    SelectY = selectY;
                    F_select = false;
                    if (IsMoveValid(StartX, StartY, SelectX, SelectY)) {
                      
                        board[SelectX][SelectY] = board[StartX][StartY];
                        board[StartX][StartY] = 0;
                        CanTakeMore(SelectX, SelectY);
                      
                    }
                    // 特定の条件で成金する処理を追加
                    if (board[SelectX][SelectY] == 1 && SelectY == 7) {
                        board[SelectX][SelectY] = 4; // 4は成金を表す
                    }
                    if (cantake == true) {
                        phase = 0;
                    }
                    else {
                        phase = 1;
                    }
                }

            }
            else if (phase == 1) {
                if (g_KeyFlg & PAD_INPUT_1 && (board[selectX][selectY] == 2)) {
                    StartX = selectX;
                    StartY = selectY;
                    F_select = true;
                }
                else if (g_KeyFlg & PAD_INPUT_1 && (board[selectX][selectY] == 3)) {
                    StartX = selectX;
                    StartY = selectY;
                    F_select = true;
                }
                if (g_KeyFlg & PAD_INPUT_1 && board[selectX][selectY] == 0) {
                    SelectX = selectX;
                    SelectY = selectY;
                    F_select = false;
                    if (IsMoveValid(StartX, StartY, SelectX, SelectY)) {

                        board[SelectX][SelectY] = board[StartX][StartY];
                        board[StartX][StartY] = 0;
                        CanTakeMore(SelectX, SelectY);
                     
                    }
                    // 特定の条件で成金する処理を追加
                    if (board[SelectX][SelectY] == 2 && SelectY == 0) {
                        board[SelectX][SelectY] = 3; // 4は成金を表す
                    }
                    if (cantake == true) {
                        phase = 1;
                    }
                    else {
                        phase = 0;
                    }

                }

            }

        }
    }
    return this;
}

void Checkermain::Draw() const {
    // 背景を描画
    DrawGraph(0, 0, Checkerback, FALSE);
    // ボードを描画
    DrawGraph(180, 0, Boardimg, TRUE);

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
                DrawRotaGraph(x * 73 + 400, y * 72 + 108, 2,0, PieceR, TRUE);
            }
        }
    }

    // 成金の駒を描画
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (board[x][y] == 3) {
                DrawRotaGraph(x * 73 + 400, y * 72 + 108, 2, 0, PieceBK, TRUE);
            }
        }
    }
    // 成金の駒を描画
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (board[x][y] == 4) {
                DrawRotaGraph(x * 73 + 400, y * 72 + 108, 2, 0, PieceRK, TRUE);
            }
        }
    }

   

    // カーソルの位置に四角形を描画
    DrawBox(372 + (selectX * 71), 72 + (selectY * 71), 445 + (selectX * 71), 145 + (selectY * 71), GetColor(0, 250, 0), FALSE);

    // デバッグ情報を表示
    DrawFormatString(0, 0, 0x000000, "Y: %d", selectY);                 // カーソル移動Y
    DrawFormatString(0, 30, 0x000000, "X: %d", selectX);                // カーソル移動X
    DrawFormatString(0, 100, 0x000000, "F_select: %d", F_select);
    DrawFormatString(0, 125, 0x000000, "cantake: %d", cantake);
    DrawFormatString(0, 150, 0x000000, "Phase: %d", phase);
    DrawFormatString(0, 200, 0x000000, "board: %d", board[selectX][selectY]);
    DrawFormatString(0, 300, 0x000000, " player1Pieces: %d", player1Pieces);
    DrawFormatString(0, 350, 0x000000, " player2Pieces: %d", player2Pieces);
}

void Checkermain::InitBoard() {
    // チェッカーボードの初期化
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = 0;
        }
    }
    player1Pieces = 12; // プレイヤー1の駒の数
    player2Pieces = 12; // プレイヤー2の駒の数
}

bool Checkermain::IsMoveValid(int StartX, int StartY, int SelectX, int SelectY) {
    // 移動先がボードの範囲外である場合、無効
    if (SelectX < 0 || SelectY < 0 || SelectX >= 8 || SelectY >= 8) {
        return false;
    }

    // 移動先にすでに駒がある場合、無効
    if (board[SelectX][SelectY] != 0) {
        return false;
    }

   
    // 赤駒が敵陣地の端に到達したら成金になる


    // 赤駒
    if (board[StartX][StartY] == 1){
    // 移動先が隣接している場合（通常の移動）赤駒の右斜め前移動
        if ((SelectX - StartX) == 1 && (SelectY - StartY) == 1) {
            // 1つ前に進むことが許可される条件を追加
            if (board[StartX][StartY] == 1) {
                return true;
            }
        }
        // 赤駒の左斜め前移動
        else if ((SelectX - StartX) == -1 && (SelectY - StartY) == 1) {
            // 1つ前に進むことが許可される条件を追加
            if (board[StartX][StartY] == 1) {
                return true;
            }
        }
        //else if (SelectY==7) {
        //        board[StartX][StartY] = 0;
        //        board[SelectX][SelectY] = 4; // 4は成金を表す
        //    return false;
        //}
    }
    // 黒駒
    if (board[StartX][StartY] == 2) {
        // 黒駒の右斜め前移動
        if ((SelectX - StartX) == -1 && (SelectY - StartY) == -1) {
            // 1つ前に進むことが許可される条件を追加
            if (board[StartX][StartY] == 2) {
                return true;
            }
        }
        // 黒駒の左斜め前移動
        else  if ((SelectX - StartX) == 1 && (SelectY - StartY) == -1) {
            // 1つ前に進むことが許可される条件を追加
            if (board[StartX][StartY] == 2) {
                return true;
            }
        }
        // 黒駒が敵陣地の端に到達したら成金になる
        //else if (SelectY == 0) {
        //    board[StartX][StartY] = 0;
        //    board[SelectX][SelectY] = 3; // 3は成金を表す
        //    return false;
        //}
    }
    // 黒駒
    if (board[StartX][StartY] == 3){
        if ((SelectX - StartX) == 1 && (SelectY - StartY) == 1) {
            // 1つ前に進むことが許可される条件を追加（成金黒駒の移動）
            if (board[StartX][StartY] == 3) {
                return true;
            }
        }
        else  if ((SelectX - StartX) == -1 && (SelectY - StartY) == 1) {
            // 1つ前に進むことが許可される条件を追加（成金黒駒の移動）
            if (board[StartX][StartY] == 3) {
                return true;
            }
        }
        else if ((SelectX - StartX) == -1 && (SelectY - StartY) == -1) {
            // 1つ前に進むことが許可される条件を追加（成金黒駒左斜め後ろの移動）
            if (board[StartX][StartY] == 3) {
                return true;
            }
        }
        else if ((SelectX - StartX) == 1 && (SelectY - StartY) == -1) {
            // 1つ前に進むことが許可される条件を追加（成金黒駒右斜め後ろの移動）
            if (board[StartX][StartY] == 3) {
                return true;
            }
        }

    }
    // 赤駒
    if (board[StartX][StartY] == 4){
        if ((SelectX - StartX) == 1 && (SelectY - StartY) == 1) {
            // 1つ前に進むことが許可される条件を追加（成金赤駒左斜め後ろの移動）
            if (board[StartX][StartY] == 4) {
                return true;
            }
        }
        else  if ((SelectX - StartX) == -1 && (SelectY - StartY) == 1) {
            // 1つ前に進むことが許可される条件を追加（成金赤駒右斜め後ろの移動）
            if (board[StartX][StartY] == 4) {
                return true;
            }
        }
        else  if ((SelectX - StartX) == -1 && (SelectY - StartY) == -1) {
            // 1つ前に進むことが許可される条件を追加（成金赤駒の移動）
            if (board[StartX][StartY] == 4) {
                return true;
            }
        }
        else    if ((SelectX - StartX) == 1 && (SelectY - StartY) == -1) {
            // 1つ前に進むことが許可される条件を追加（成金赤駒の移動）
            if (board[StartX][StartY] == 4) {
                return true;
            }
        }
    }

 

    // 移動先が斜めに2つ飛び越える場合（ジャンプ）aka
    // 赤駒のジャンプ条件をチェック
    if (board[StartX][StartY] == 1) {
        // 上下左右斜めそれぞれのジャンプ可能な場合を個別にチェック
        if ((SelectX - StartX == -2 && SelectY - StartY == 2) || (SelectX - StartX == 2 && SelectY - StartY == 2)) {
            jumpedX = (SelectX + StartX) / 2;
            jumpedY = (SelectY + StartY) / 2;
            // 飛び越えた位置に相手の駒があるか確認
            if (board[jumpedX][jumpedY] == 2 || (board[jumpedX][jumpedY] == 3)) {
                // 飛び越えた相手の駒を削除
                board[jumpedX][jumpedY] = 0;

                return true;
            }
        }


    }

    // 移動先が斜めに2つ飛び越える場合（ジャンプ）kuro
   // 黒駒のジャンプ条件をチェック
    if (board[StartX][StartY] == 2) {
        // 上下左右斜めそれぞれのジャンプ可能な場合を個別にチェック
        if ((SelectX - StartX == 2 && SelectY - StartY == -2) || (SelectX - StartX == -2 && SelectY - StartY == -2)) {
            jumpedX = (SelectX + StartX) / 2;
            jumpedY = (SelectY + StartY) / 2;
            // 飛び越えた位置に相手の駒があるか確認
            if (board[jumpedX][jumpedY] == 1 ||(board[jumpedX][jumpedY] == 4)) {
                // 飛び越えた相手の駒を削除
                board[jumpedX][jumpedY] = 0;

                return true;
            }
        }


    }
   // 黒駒のジャンプ条件をチェック（成金）
    if (board[StartX][StartY] == 3) {
        // 上下左右斜めそれぞれのジャンプ可能な場合を個別にチェック
        if ((SelectX - StartX == 2 && SelectY - StartY == -2) || (SelectX - StartX == -2 && SelectY - StartY == -2)|| (SelectX - StartX == -2 && SelectY - StartY == 2) || (SelectX - StartX == 2 && SelectY - StartY == 2)) {
            jumpedX = (SelectX + StartX) / 2;
            jumpedY = (SelectY + StartY) / 2;
            // 飛び越えた位置に相手の駒があるか確認
            if ((board[jumpedX][jumpedY] == 1)||(board[jumpedX][jumpedY] == 4)) {
                // 飛び越えた相手の駒を削除
                board[jumpedX][jumpedY] = 0;

                return true;
            }
        }

    }
    // 赤駒のジャンプ条件をチェック（成金）
    if (board[StartX][StartY] == 4) {
        // 上下左右斜めそれぞれのジャンプ可能な場合を個別にチェック
        if ((SelectX - StartX == 2 && SelectY - StartY == -2) || (SelectX - StartX == -2 && SelectY - StartY == -2) || (SelectX - StartX == -2 && SelectY - StartY == 2) || (SelectX - StartX == 2 && SelectY - StartY == 2)) {
            jumpedX = (SelectX + StartX) / 2;
            jumpedY = (SelectY + StartY) / 2;
            // 飛び越えた位置に相手の駒があるか確認
            if ((board[jumpedX][jumpedY] == 2) || (board[jumpedX][jumpedY] == 3)) {
                // 飛び越えた相手の駒を削除
                board[jumpedX][jumpedY] = 0;

                return true;
            }
        }

    }
   
    return false; // 上記の条件に該当しない場合、無効な移動
}

void Checkermain::Gameover()
{
    // プレイヤー1の駒の数を更新
    player1Pieces = 0;
    // プレイヤー2の駒の数を更新
    player2Pieces = 0;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (board[x][y] == 1 || board[x][y] == 3) {
                player1Pieces++;
            }
            else if (board[x][y] == 2 || board[x][y] == 4) {
                player2Pieces++;
            }
        }
    }
    // どちらかのプレイヤーが駒を持っていない場合、勝敗がついたと判定
    if (player1Pieces == 0) {
        // プレイヤー2の勝利
        printf("bbb");
        // または、必要に応じて別の処理を追加
    }
    else if (player2Pieces == 0) {
        // プレイヤー1の勝利
        printf("aaaa");
        // または、必要に応じて別の処理を追加
    }
}



bool Checkermain::CanTakeMore(int SelectX, int SelectY)
{ // 駒を取れるかどうかを示すフラグ
    cantake = 0;

    // 駒が盤面外にある場合は取れない
    if (SelectX < 0 || SelectY < 0 || SelectX >= 8 || SelectY >= 8) {
        return false;
    }
    // 移動先にすでに駒がある場合、無効
    if (board[SelectX+2][SelectY+2]|| board[SelectX - 2][SelectY - 2]|| board[SelectX - 2][SelectY + 2]|| board[SelectX + 2][SelectY - 2] != 0) {
        return false;
    }
     // 赤駒のジャンプ条件をチェック
    if (board[StartX][StartY] == 1) {
        if  (board[SelectX + 2][SelectY + 2] || board[SelectX - 2][SelectY + 2]) {
            return false;
        }
        // 上下左右斜めそれぞれのジャンプ可能な場合を個別にチェック
        if (((SelectX + 2) - SelectX == -2 && (SelectY + 2) - SelectY == 2) || ((SelectX + 2) - SelectX == 2 && (SelectY + 2) - SelectY == 2)) {
            jumpedX = ((SelectX + 2) + SelectX) / 2;
            jumpedY = ((SelectY + 2) + SelectY) / 2;
            // 飛び越えた位置に相手の駒があるか確認
            if (board[jumpedX][jumpedY] == 2 || (board[jumpedX][jumpedY] == 3)) {
                cantake = true;
          
                return false;
            }
            else if (board[jumpedX][jumpedY] == 0) {
                cantake = false;
             
                return false;
            }
        }
        else if (board[StartX][StartY] == 2) {
            if (board[SelectX - 2][SelectY - 2] || board[SelectX + 2][SelectY - 2]) {
                return false;
            }
            if (board[SelectX - 2][SelectY - 2] || board[SelectX + 2][SelectY - 2]) {
                return false;
            }
            // 上下左右斜めそれぞれのジャンプ可能な場合を個別にチェック
            if (((SelectX+2) - SelectX == 2 && (SelectY+2) - SelectY == -2) || ((SelectX+2) - SelectX == -2 && (SelectY+2) - SelectY == -2)) {
                jumpedX = (SelectX + SelectX) / 2;
                jumpedY = (SelectY + SelectX) / 2;
                // 飛び越えた位置に相手の駒があるか確認
                if (board[jumpedX][jumpedY] == 1 || (board[jumpedX][jumpedY] == 4)) {
                    // 飛び越えた相手の駒を削除
                    cantake = true;
                
                    
                    return true;
                }
                else if (board[jumpedX][jumpedY] == 0) {
                    cantake = false;
                  
                    return false;
                }
            }


        }

    }

    return false;
}
