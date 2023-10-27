#include "DxLib.h"
#include "DrawLine.h"

void Line::DrawLine() {
    // ここで線を描画
    DrawBox(x1, y1, x2, y2, GetColor(0, 0, 255), FALSE);
}

void Line::Update() {
    // Aボタンが押された場合
    if (CheckHitKey(PAD_INPUT_A)) {
        // プレイヤーが選択した行と列
        row = 490;
        col = 400;

        // 線の座標を計算
        x1 = startX + row * gridSize;
        y1 = startY + col * gridSize;
        x2 = x1 + gridSize;
        y2 = y1;
    }
}

void Line::Draw() {
    DrawLine();
}
