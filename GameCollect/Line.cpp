
#include "DxLib.h"
#include "Line.h"
#include <math.h>


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

    firstButtonClick = true;  // 初回のクリックかどうかを管理するフラグを初期化
    selectedPointX = 0;
    selectedPointY = 0;

}

Line::~Line() {

}


void Line::Update() {
    g_Oldkey = g_Nowkey;
    g_Nowkey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    Keyflg = g_Nowkey & ~g_Oldkey;

    if (Keyflg & PAD_INPUT_A) {
        if (!Drawflg) {
            // 線がまだ引かれていない場合
            SelectNearestPoint(startX, startY);
        }
        else {
            // すでに線が引かれている場合
            DrawLine(startX, startY, selectedPointX, selectedPointY, GetColor(255, 255, 255));
            // 選択された点と現在のポインター位置を結ぶ線を描画
            DrawLine(selectedPointX, selectedPointY, drawnPointX, drawnPointY, GetColor(255, 255, 255));
            // 選択された点を青く描画
            DrawCircle(selectedPointX, selectedPointY, 10, GetColor(0, 0, 255), TRUE);
        }
    }
}

void Line::Draw() const {
    if (Drawflg == true) {
        // ここで線を描画
        DrawLine(startX, startY, drawnPointX, drawnPointY, GetColor(0, 0, 255));
    }

    // 選択された点の座標を描画
    DrawFormatString(10, 10, GetColor(255, 255, 255), "Selected Point: (%d, %d)", selectedPointX, selectedPointY);  
    // 選択された点の座標を描画
    DrawFormatString(10, 40, GetColor(255, 255, 255), "Start Point: (%d, %d)", startX, startY);
    // 選択された点の座標を描画
    DrawFormatString(10, 70, GetColor(255, 255, 255), "drawn Point: (%d, %d)", drawnPointX, drawnPointY);

}

    // DotAndBox クラスから座標を受け取る関数
    void Line::SetDrawnPoint(int x, int y) {
        drawnPointX = x;
        drawnPointY = y;
        Drawflg = true;
    }

    void Line::SelectNearestPoint(int pointerX, int pointerY) {
        int nearestPointX = startX;
        int nearestPointY = startY;
        double minDistance = sqrt(pow(startX - pointerX, 2) + pow(startY - pointerY, 2));

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                int x = startX + i * gridSize;
                int y = startY + j * gridSize;
                double distance = sqrt(pow(x - pointerX, 2) + pow(y - pointerY, 2));

                if (distance < minDistance) {
                    minDistance = distance;
                    nearestPointX = x;
                    nearestPointY = y;
                }
            }
        }

        SetDrawnPoint(nearestPointX, nearestPointY);
        Drawflg = true;

        // startX と startY を更新
        startX = nearestPointX;
        startY = nearestPointY;

        // 選択された点の座標を保存
        selectedPointX = nearestPointX;
        selectedPointY = nearestPointY;
    }

    void Line::ResetSelection() {
        Drawflg = false;
        selectedPointX = 0;
        selectedPointY = 0;
        firstButtonClick = true;  // 初回のクリックかどうかを管理するフラグをリセット
    }