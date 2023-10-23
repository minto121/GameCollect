#include "DotAndBox.h"
#include "DxLib.h"
#include "PadInput.h"
#include "AbstractScene.h"

DotAndBox::DotAndBox() {

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

AbstractScene* DotAndBox::Update() {
	return this;
}

void DotAndBox::Draw() const {
     // �O���b�h���̓_��`��(�h�b�g�̊J�n�ʒu���萔�����Ă��邽�ߍ��x�C�� StartX, startY, rows, columns�̕ύX)
    int gridSize = 150;  // �O���b�h�̊Ԋu
    int startX = 480;   // �J�nX���W
    int startY = 250;   // �J�nY���W
    int rows = 3;       // �s��
    int columns = 3;    // ��

    DrawGridOfPoints(startX, startY, gridSize, rows, columns);
}