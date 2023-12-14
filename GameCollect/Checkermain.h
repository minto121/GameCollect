#pragma once
#include "AbstractScene.h"
#include <DxLib.h>

class Checkermain : public AbstractScene {
private:
    // 画像データのIDとサイズなどの変数
    int Boardimg;      // 盤の画像
    int PieceB;        // 駒黒の画像
    int PieceR;        // 駒赤の画像
    int PieceBK;
    int PieceRK;
    int Checkerback;   // 背景の画像
    int size = 100;    // 画像のサイズ

    // チェッカーボードの状態 0:赤1:黒
    int board[8][8] = {
        // チェッカーボードの初期配置
        // 数値の意味：
        // 0: 駒なし、1: 赤駒、2: 黒駒、3: 赤の成金、4: 黒の成金
        0, 1, 0, 0, 0, 2, 0, 2,
        1, 0, 1, 0, 0, 0, 2, 0,
        0, 1, 0, 0, 0, 2, 0, 2,
        1, 0, 1, 0, 0, 0, 2, 0,
        0, 1, 0, 0, 0, 2, 0, 2,
        1, 0, 1, 0, 0, 0, 2, 0,
        0, 1, 0, 0, 0, 2, 0, 2,
        1, 0, 1, 0, 0, 0, 2, 0
    };

    // ゲームの状態を管理する変数
    bool F_select = false;  // 選択中の駒があるかどうか
    bool movevail;          // 移動が有効かどうかを表す
    bool cantake = false;
    bool F_totteta = false;
    // カーソルの位置とキー入力関連の変数
    int selectX;    // カーソルのX座標
    int selectY;    // カーソルのY座標
    int g_OldKey;   // 前回のキー入力状態
    int g_NowKey;   // 現在のキー入力状態
    int g_KeyFlg;   // キーの変化を示すフラグ
    int phase = 0;
    // 駒の移動に関する変数
    int StartX;     // 移動させたい駒の座標X
    int StartY;     // 移動させたい駒の座標Y
    int SelectX;    // 駒を移動させい座標X
    int SelectY;    // 駒を移動させい座標Y
    int jumpedX;    // ジャンプした際のX座標
    int jumpedY;    // ジャンプした際のY座標
    int SjumpedX;   // ジャンプした際のX座標
    int SjumpedY;   // ジャンプした際のY座標
    // プレイヤーの駒数を表す変数
    int player1Pieces;
    int player2Pieces;

public:
    Checkermain(); // コンストラクタ

    ~Checkermain(); // デストラクタ

    // 描画以外の更新を実行する
    AbstractScene* Update() override;

    // 描画に関する処理を行う
    void Draw() const override;

    // チェッカーボードの初期状態を設定する
    void InitBoard();

    // 移動の妥当性を判定する
    bool IsMoveValid(int StartX, int StartY, int SelectX, int SelectY);

    // ゲーム終了の判定を行う
    void Gameover();

    // ジャンプ後にさらに駒を取れるかどうかを判定する
    bool CanTakeMore(int startX, int startY, int SelectX, int SelectY);

    
  
};
