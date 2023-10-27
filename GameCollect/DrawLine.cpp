#include "DxLib.h"
#include "DrawLine.h"

void Line::DrawLine() {
    // �����Ő���`��
    DrawBox(x1, y1, x2, y2, GetColor(0, 0, 255), FALSE);
}

void Line::Update() {
    // A�{�^���������ꂽ�ꍇ
    if (CheckHitKey(PAD_INPUT_A)) {
        // �v���C���[���I�������s�Ɨ�
        row = 490;
        col = 400;

        // ���̍��W���v�Z
        x1 = startX + row * gridSize;
        y1 = startY + col * gridSize;
        x2 = x1 + gridSize;
        y2 = y1;
    }
}

void Line::Draw() {
    DrawLine();
}
