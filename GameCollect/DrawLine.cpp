#include "DrawLine.h"
#include "DxLib.h"
#include "PadInput.h"

void Line::DrawLine() {
    // Aボタンが押された場合
    if (CheckHitKey(PAD_INPUT_A)) {

        // ここで線を描画
        int row = 490; // プレイヤーが選択した行
        int col = 400; // プレイヤーが選択した列
        int x1 = startX + row * gridSize;
        int y1 = startY + col * gridSize;
        int x2 = x1 + gridSize;
        int y2 = y1;
        DrawBox(x1, y1, x2, y2, GetColor(255, 0, 0), FALSE);
    }
}
