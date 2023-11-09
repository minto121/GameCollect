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
        pointerX -= line.GetgridSize() / 2;  // ���Ɉړ�
    }
    if (Keyflg & PAD_INPUT_RIGHT && pointerX < SCREEN_WIDTH) {
        pointerX += line. GetgridSize() / 2;  // �E�Ɉړ�
    }
    if (Keyflg & PAD_INPUT_UP && pointerY < SCREEN_HEIGHT) {
        pointerY -= line.GetgridSize() / 2;  // ��Ɉړ�
    }
    if (Keyflg & PAD_INPUT_DOWN && pointerY > 0) {
        pointerY += line.GetgridSize() / 2;  // ���Ɉړ�
    }

    line.Update();
	
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

    line.Draw();
}