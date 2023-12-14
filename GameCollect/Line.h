#pragma once

#include "DotAndBox.h"
#include "DxLib.h"
#include <math.h>

class DotAndBox;

class Line {
private:

    DotAndBox* dotandbox;

    int startX;
    int startY;
    int gridSize;
    int row;
    int col;
 

    int g_Oldkey;
    int g_Nowkey;
    int Keyflg;

    bool Drawflg;

    // 描画した点の座標を保持する変数
    int drawnPointX;
    int drawnPointY;

    int selectedPointX;  // 選択された点の座標
    int selectedPointY;
    bool firstButtonClick;  // 最初のボタンクリックかどうかのフラグ

public:
    Line(DotAndBox* dotandbox);
    Line();
    ~Line();

    void Update();
    void Draw() const;

    // DotAndBox クラスから座標を受け取る関数
    void SetDrawnPoint(int x, int y);

    int GetgridSize() { return gridSize; }

    // 新しいメソッドを追加
    void SelectNearestPoint(int pointerX, int pointerY);

    void ResetSelection();
};
