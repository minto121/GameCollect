#pragma once
#include "AbstractScene.h"
#include <DxLib.h>

class Checkermain : public AbstractScene
{
private:
    int Boardimg;     // 盤の画像
    int PieceB;       // 駒黒の画像
    int PieceW;       // 駒白の画像
    int Checkerback;  // 背景の画像
    int size = 100;   // 画像のサイズ

    int board[8][8] = {
        // チェッカーボードの初期配置
        0, 1, 0, 0, 0, 2, 0, 2,
        1, 0, 1, 0, 0, 0, 2, 0,
        0, 1, 0, 0, 0, 2, 0, 2,
        1, 0, 1, 0, 0, 0, 2, 0,
        0, 1, 0, 0, 0, 2, 0, 2,
        1, 0, 1, 0, 0, 0, 2, 0,
        0, 1, 0, 0, 0, 2, 0, 2,
        1, 0, 1, 0, 0, 0, 2, 0
    };

    bool F_select = false;  // 選択中の駒があるかどうか
    bool phase;             // 先攻（0）後攻（1）を表す

    int selectX;    // カーソルのX座標
    int selectY;    // カーソルのY座標

    int g_OldKey;   // 前回のキー入力状態
    int g_NowKey;   // 現在のキー入力状態
    int g_KeyFlg;   // キーの変化を示すフラグ

    int StartX;     // 移動させたい駒の座標X
    int StartY;     // 移動させたい駒の座標Y
    int SelectX;    // 駒を移動させい座標X
    int SelectY;    // 駒を移動させい座標Y
    int jumpedX;
    int jumpedY;

public:
    Checkermain();

    ~Checkermain();

    // 描画以外の更新を実行
    AbstractScene* Update() override;

    // 描画に関することを実装
    void Draw() const override;

    // チェッカーボードの初期状態を設定
    void InitBoard();

    // 移動判定
    bool IsMoveValid(int startX, int startY, int SelectX, int SelectY);

    void Gameover();

};
