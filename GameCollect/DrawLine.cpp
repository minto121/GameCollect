#include "DxLib.h"
#include "DrawLine.h"
#include "PadInput.h"
#include "DotAndBox.h"

Line::Line() {

    startX = 0;
    startY = 0;

    // プレイヤーが選択した行と列
    row = 490;
    col = 400;

    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;

    g_Oldkey;
    g_Nowkey;
    Keyflg;

    Drawflg = false;
}

Line::~Line() {

}

//bool Line::IsVerticalLine(int x1, int y1, int x2, int y2) {
//    if (x1 == x2) {
//        x1 = startX + gridSize - 50;
//    }
//}

void Line::Update() {

    g_Oldkey = g_Nowkey;
    g_Nowkey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    Keyflg = g_Nowkey & ~g_Oldkey;
       
    if (Keyflg & PAD_INPUT_A) { // ボタン1またはZキーの入力フラグが立っていたら

        x1 = startX + col * gridSize + gridSize / 2;  // グリッドセルの中央からスタート
        y1 = startY + row * gridSize;
        x2 = x1;  // 垂直線なのでx座標は同じ
        y2 = y1 - gridSize;  // 上向きに描画

    }
}

    void Line::Draw() const {
        if (Drawflg == true) {
            // ここで線を描画
            DrawBox(x1, y1, x2, y2, GetColor(0, 0, 255), FALSE);
        }
    }
