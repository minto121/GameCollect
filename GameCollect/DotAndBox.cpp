#include "DotAndBox.h"
#include "DxLib.h"
#include "PadInput.h"
#include "AbstractScene.h"

DotAndBox::DotAndBox() {

}

DotAndBox::~DotAndBox() {

}

AbstractScene* DotAndBox::Update() {
	return this;
}

void DotAndBox::Draw() const {
    // 3x3�̓_��`��
    int gridSize = 150;  // �O���b�h�̊Ԋu
    int startX = 500;   // �J�nX���W
    int startY = 200;   // �J�nY���W

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int x = startX + i * gridSize;
            int y = startY + j * gridSize;
            DrawCircle(x, y, 10, GetColor(255, 255, 255), TRUE);
        }
    }
}