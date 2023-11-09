#include "DxLib.h"
#include "DrawLine.h"
#include "PadInput.h"
#include "DotAndBox.h"

Line::Line() {

    startX = 0;
    startY = 0;

    // �v���C���[���I�������s�Ɨ�
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
}

Line::~Line() {

}

//bool Line::IsVerticalLine(int x1, int y1, int x2, int y2) {
//    if (x1 == x2) {
//        x1 = startX + gridSize - 50;
//    }
//}

void Line::Update() {

    g_Oldkey = g_Nowkey;
    g_Nowkey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    Keyflg = g_Nowkey & ~g_Oldkey;
       
    if (Keyflg & PAD_INPUT_A) { // �{�^��1�܂���Z�L�[�̓��̓t���O�������Ă�����

        x1 = startX + col * gridSize + gridSize / 2;  // �O���b�h�Z���̒�������X�^�[�g
        y1 = startY + row * gridSize;
        x2 = x1;  // �������Ȃ̂�x���W�͓���
        y2 = y1 - gridSize;  // ������ɕ`��

    }
}

    void Line::Draw() const {
        if (Drawflg == true) {
            // �����Ő���`��
            DrawBox(x1, y1, x2, y2, GetColor(0, 0, 255), FALSE);
        }
    }
