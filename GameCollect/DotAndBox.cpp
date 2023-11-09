#include "DotAndBox.h"
#include "DxLib.h"
#include "PadInput.h"
#include "DrawLine.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

DotAndBox::DotAndBox() {
    pointerX = 0;
    pointerY = 350;

    int ScreenWidth = SCREEN_WIDTH;
    int ScreenHeight = SCREEN_HEIGHT;
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

void DotAndBox::Update() {
    
    g_Oldkey = g_Nowkey;
    g_Nowkey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    Keyflg = g_Nowkey & ~g_Oldkey;

    if (Keyflg & PAD_INPUT_LEFT && pointerX > 0) {
        pointerX -= line.GetgridSize() / 2;  // 左に移動
    }
    if (Keyflg & PAD_INPUT_RIGHT && pointerX < SCREEN_WIDTH) {
        pointerX += line. GetgridSize() / 2;  // 右に移動
    }
    if (Keyflg & PAD_INPUT_UP && pointerY < SCREEN_HEIGHT) {
        pointerY -= line.GetgridSize() / 2;  // 上に移動
    }
    if (Keyflg & PAD_INPUT_DOWN && pointerY > 0) {
        pointerY += line.GetgridSize() / 2;  // 下に移動
    }

    line.Update();
	
}

void DotAndBox::Draw() const {

    // ポインターを描画
    DrawCircle(pointerX, pointerY, 10, GetColor(255, 0, 0), TRUE);

     // グリッド内の点を描画(ドットの開始位置が定数化しているため今度修正 startX, startY, rows, columnsの変更)
    int gridSize = 150;  // グリッドの間隔
    int startX = 480;   // 開始X座標
    int startY = 250;   // 開始Y座標
    int rows = 3;       // 行数
    int columns = 3;    // 列数

    DrawGridOfPoints(startX, startY, gridSize, rows, columns);

    line.Draw();
}