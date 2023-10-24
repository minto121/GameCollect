#include "DrawLine.h"
#include "DxLib.h"
#include "PadInput.h"

void Line::DrawLine() {
    // A�{�^���������ꂽ�ꍇ
    if (CheckHitKey(PAD_INPUT_A)) {

        // �����Ő���`��
        int row = 490; // �v���C���[���I�������s
        int col = 400; // �v���C���[���I��������
        int x1 = startX + row * gridSize;
        int y1 = startY + col * gridSize;
        int x2 = x1 + gridSize;
        int y2 = y1;
        DrawBox(x1, y1, x2, y2, GetColor(255, 0, 0), FALSE);
    }
}
