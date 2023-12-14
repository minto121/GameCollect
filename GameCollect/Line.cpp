
#include "DxLib.h"
#include "Line.h"
#include <math.h>


Line::Line(DotAndBox* dotandbox) : dotandbox(dotandbox) {
    
}

Line::Line(){

   
    startX = 0;
    startY = 0;

    // �v���C���[���I�������s�Ɨ�
    row = 490;
    col = 400;

    g_Oldkey;
    g_Nowkey;
    Keyflg;

    Drawflg = false;

    firstButtonClick = true;  // ����̃N���b�N���ǂ������Ǘ�����t���O��������
    selectedPointX = 0;
    selectedPointY = 0;

    dotandbox = new DotAndBox;
}


Line::~Line() {
    delete dotandbox;
}


void Line::Update() {
    g_Oldkey = g_Nowkey;
    g_Nowkey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    Keyflg = g_Nowkey & ~g_Oldkey;

    if (Keyflg & PAD_INPUT_A) {
        if (!Drawflg) {
            // �����܂�������Ă��Ȃ��ꍇ
            SelectNearestPoint(startX, startY);
        }
        else {
            // ���łɐ���������Ă���ꍇ
            DrawLine(startX, startY, selectedPointX, selectedPointY, GetColor(255, 255, 255));
            // �I�����ꂽ�_�ƌ��݂̃|�C���^�[�ʒu�����Ԑ���`��
            DrawLine(selectedPointX, selectedPointY, drawnPointX, drawnPointY, GetColor(255, 255, 255));
            // �I�����ꂽ�_����`��
            DrawCircle(selectedPointX, selectedPointY, 10, GetColor(0, 0, 255), TRUE);
        }
    }
}

void Line::Draw() const {
    if (Drawflg == true) {
        // �����Ő���`��
        DrawLine(startX, startY, drawnPointX, drawnPointY, GetColor(0, 0, 255));
    }

    // �I�����ꂽ�_�̍��W��`��
    DrawFormatString(10, 10, GetColor(255, 255, 255), "Selected Point: (%d, %d)", selectedPointX, selectedPointY);  
    // �I�����ꂽ�_�̍��W��`��
    DrawFormatString(10, 40, GetColor(255, 255, 255), "Start Point: (%d, %d)", startX, startY);
    // �I�����ꂽ�_�̍��W��`��
    DrawFormatString(10, 70, GetColor(255, 255, 255), "drawn Point: (%d, %d)", drawnPointX, drawnPointY);

}

    void Line::SelectNearestPoint(int pointerX, int pointerY) {
        int nearestPointX = startX;
        int nearestPointY = startY;
        double minDistance = sqrt(pow(startX - pointerX, 2) + pow(startY - pointerY, 2));

        // �ŏ��̓_����J�[�\���܂ł̐���̓_��I��
        int deltaX = pointerX - startX;
        int deltaY = pointerY - startY;

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                int x = startX + i * gridSize;
                int y = startY + j * gridSize;
                double distance = sqrt(pow(x - pointerX, 2) + pow(y - pointerY, 2));

                // �ŏ��̓_����J�[�\���܂ł̐���̓_��I��
                if (deltaX != 0) {
                    int calculatedY = startY + (deltaY * (x - startX)) / deltaX;
                    if (y == calculatedY && distance < minDistance) {
                        minDistance = distance;
                        nearestPointX = x;
                        nearestPointY = y;
                    }
                }
                else if (deltaY != 0) {
                    int calculatedX = startX + (deltaX * (y - startY)) / deltaY;
                    if (x == calculatedX && distance < minDistance) {
                        minDistance = distance;
                        nearestPointX = x;
                        nearestPointY = y;
                    }
                }
            }
        }

        SetDrawnPoint(nearestPointX, nearestPointY);
        Drawflg = true;

        // startX �� startY ���X�V
        startX = nearestPointX;
        startY = nearestPointY;

        // �I�����ꂽ�_�̍��W��ۑ�
        selectedPointX = nearestPointX;
        selectedPointY = nearestPointY;
    }

    void Line::ResetSelection() {
        Drawflg = false;
        selectedPointX = 0;
        selectedPointY = 0;
        firstButtonClick = true;  // ����̃N���b�N���ǂ������Ǘ�����t���O�����Z�b�g
    }

    void Line::SetDrawnPoint(int x, int y) {
        drawnPointX = x;
        drawnPointY = y;

        // DotAndBox �N���X�ɕ`�悳�ꂽ�_�̍��W��n��
        dotandbox->SetPointer(x, y);
    }