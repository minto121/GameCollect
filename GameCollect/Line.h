#pragma once

#include "DotAndBox.h"
#include "DxLib.h"
#include <math.h>

class DotAndBox;

class Line {
private:

    DotAndBox* dotandbox;

    int startX;
    int startY;
    int gridSize;
    int row;
    int col;
 

    int g_Oldkey;
    int g_Nowkey;
    int Keyflg;

    bool Drawflg;

    // �`�悵���_�̍��W��ێ�����ϐ�
    int drawnPointX;
    int drawnPointY;

    int selectedPointX;  // �I�����ꂽ�_�̍��W
    int selectedPointY;
    bool firstButtonClick;  // �ŏ��̃{�^���N���b�N���ǂ����̃t���O

public:
    Line(DotAndBox* dotandbox);
    Line();
    ~Line();

    void Update();
    void Draw() const;

    // DotAndBox �N���X������W���󂯎��֐�
    void SetDrawnPoint(int x, int y);

    int GetgridSize() { return gridSize; }

    // �V�������\�b�h��ǉ�
    void SelectNearestPoint(int pointerX, int pointerY);

    void ResetSelection();
};
