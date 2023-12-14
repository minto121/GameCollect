#include "GameMain.h"
#include "DxLib.h"
#include "PadInput.h"
#include "AbstractScene.h"
#include "Line.h"

GameMain::GameMain() {
   

}

GameMain::~GameMain() {

}

AbstractScene* GameMain::Update() {

    dotandbox.Update();
    line.Update();
    return this;
}

void GameMain::Draw() const {
    // グリッド内の点を描画(ドットの開始位置が定数化しているため今度修正 startX, startY, rows, columnsの変更)
    int gridSize = 150;  // グリッドの間隔
    int startX = 480;   // 開始X座標
    int startY = 250;   // 開始Y座標
    int rows = 3;       // 行数
    int columns = 3;    // 列数

    dotandbox.Draw();

    line.Draw();
}