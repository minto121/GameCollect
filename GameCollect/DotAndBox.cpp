#include "DotAndBox.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Line.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define MAX_POINTS 1000  // 保存できる最大の点の数


// 配列を使用して描画した点の座標を保存
Point drawnPoints[MAX_POINTS];
int numDrawnPoints = 0;

DotAndBox::DotAndBox() {

    pointerX = 450;
    pointerY = 275;

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

            // 描画した点の座標を保存
            if (numDrawnPoints < MAX_POINTS) {
                drawnPoints[numDrawnPoints].x = x;
                drawnPoints[numDrawnPoints].y = y;
                numDrawnPoints++;

                // 描画した点の座標を Line クラスに渡す
                line->SetDrawnPoint(x, y);
            }
        }
    }
}
void DotAndBox::Update() {

    
    g_Oldkey = g_Nowkey;
    g_Nowkey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    Keyflg = g_Nowkey & ~g_Oldkey;

    // 移動後の位置を一時的に計算
    int tempX = pointerX;
    int tempY = pointerY;

    if (Keyflg & PAD_INPUT_LEFT) {
        tempX -= line->GetgridSize();  // 左に移動
    }
    if (Keyflg & PAD_INPUT_RIGHT) {
        tempX += line->GetgridSize();  // 右に移動
    }
    if (Keyflg & PAD_INPUT_UP) {
        tempY -= line->GetgridSize();  // 上に移動
    }
    if (Keyflg & PAD_INPUT_DOWN) {
        tempY += line->GetgridSize();  // 下に移動
    }

    // 画面からはみ出ないように修正
    if (tempX > 0 && tempX < SCREEN_WIDTH) {
        pointerX = tempX;
    }

    if (tempY > 0 && tempY < SCREEN_HEIGHT) {
        pointerY = tempY;
    }

    line->Update();
    
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

    line->Draw();
}
