#include "GameMain.h"
#include "DxLib.h"
#include "PadInput.h"
#include "AbstractScene.h"
#include "Line.h"

GameMain::GameMain() {
   

}

GameMain::~GameMain() {

}

AbstractScene* GameMain::Update() {

    dotandbox.Update();
    line.Update();
    return this;
}

void GameMain::Draw() const {
    // �O���b�h���̓_��`��(�h�b�g�̊J�n�ʒu���萔�����Ă��邽�ߍ��x�C�� startX, startY, rows, columns�̕ύX)
    int gridSize = 150;  // �O���b�h�̊Ԋu
    int startX = 480;   // �J�nX���W
    int startY = 250;   // �J�nY���W
    int rows = 3;       // �s��
    int columns = 3;    // ��

    dotandbox.Draw();

    line.Draw();
}