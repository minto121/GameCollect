#include "DotAndBox.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Line.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define MAX_POINTS 1000  // �ۑ��ł���ő�̓_�̐�


// �z����g�p���ĕ`�悵���_�̍��W��ۑ�
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

            // �`�悵���_�̍��W��ۑ�
            if (numDrawnPoints < MAX_POINTS) {
                drawnPoints[numDrawnPoints].x = x;
                drawnPoints[numDrawnPoints].y = y;
                numDrawnPoints++;

                // �`�悵���_�̍��W�� Line �N���X�ɓn��
                line->SetDrawnPoint(x, y);
            }
        }
    }
}
void DotAndBox::Update() {

    
    g_Oldkey = g_Nowkey;
    g_Nowkey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    Keyflg = g_Nowkey & ~g_Oldkey;

    // �ړ���̈ʒu���ꎞ�I�Ɍv�Z
    int tempX = pointerX;
    int tempY = pointerY;

    if (Keyflg & PAD_INPUT_LEFT) {
        tempX -= line->GetgridSize();  // ���Ɉړ�
    }
    if (Keyflg & PAD_INPUT_RIGHT) {
        tempX += line->GetgridSize();  // �E�Ɉړ�
    }
    if (Keyflg & PAD_INPUT_UP) {
        tempY -= line->GetgridSize();  // ��Ɉړ�
    }
    if (Keyflg & PAD_INPUT_DOWN) {
        tempY += line->GetgridSize();  // ���Ɉړ�
    }

    // ��ʂ���͂ݏo�Ȃ��悤�ɏC��
    if (tempX > 0 && tempX < SCREEN_WIDTH) {
        pointerX = tempX;
    }

    if (tempY > 0 && tempY < SCREEN_HEIGHT) {
        pointerY = tempY;
    }

    line->Update();
    
}


void DotAndBox::Draw() const {


    // �|�C���^�[��`��
    DrawCircle(pointerX, pointerY, 10, GetColor(255, 0, 0), TRUE);

 

     // �O���b�h���̓_��`��(�h�b�g�̊J�n�ʒu���萔�����Ă��邽�ߍ��x�C�� startX, startY, rows, columns�̕ύX)
    int gridSize = 150;  // �O���b�h�̊Ԋu
    int startX = 480;   // �J�nX���W
    int startY = 250;   // �J�nY���W
    int rows = 3;       // �s��
    int columns = 3;    // ��

    DrawGridOfPoints(startX, startY, gridSize, rows, columns);

    line->Draw();
}
