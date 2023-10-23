#include "DotAndBox.h"
#include "DxLib.h"
#include "PadInput.h"
#include "AbstractScene.h"

DotAndBox::DotAndBox() {

}

DotAndBox::~DotAndBox() {

}

void DotAndBox::DrawGridOfPoints(int startX, int startY, int gridSize, int rows, int columns) const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int x = startX + i * gridSize;
            int y = startY + j * gridSize;
            DrawCircle(x, y, 10, GetColor(255, 255, 255), TRUE);
        }
    }
}

AbstractScene* DotAndBox::Update() {
	return this;
}

void DotAndBox::Draw() const {
     // グリッド内の点を描画(ドットの開始位置が定数化しているため今度修正 StartX, startY, rows, columnsの変更)
    int gridSize = 150;  // グリッドの間隔
    int startX = 480;   // 開始X座標
    int startY = 250;   // 開始Y座標
    int rows = 3;       // 行数
    int columns = 3;    // 列数

    DrawGridOfPoints(startX, startY, gridSize, rows, columns);
}