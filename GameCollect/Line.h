#pragma once

#include "DotAndBox.h"
#include <math.h>

class DotAndBox;


class Line {
private:


	int startX;
	int startY;
	int gridSize = 150;
	int row;
	int col;
	int x1;
	int x2;
	int y1;
	int y2;

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
