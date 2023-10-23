#include "DotAndBox.h"
#include "DxLib.h"
#include "PadInput.h"
#include "AbstractScene.h"

DotAndBox::DotAndBox() {

}

DotAndBox::~DotAndBox() {

}

AbstractScene* DotAndBox::Update() {
	return this;
}

void DotAndBox::Draw() const {
    // 3x3の点を描画
    int gridSize = 150;  // グリッドの間隔
    int startX = 500;   // 開始X座標
    int startY = 200;   // 開始Y座標

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int x = startX + i * gridSize;
            int y = startY + j * gridSize;
            DrawCircle(x, y, 10, GetColor(255, 255, 255), TRUE);
        }
    }
}