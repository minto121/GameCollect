#include "DotAndBox.h"
#include "DxLib.h"
#include "PadInput.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


//DotAndBox dotandbox;
// �z����g�p���ĕ`�悵���_�̍��W��ۑ�
Point drawnPoints[MAX_POINTS];
int numDrawnPoints = 0;

// �V�������W����ۑ�����z��
int numDrawnLines = 0;
LineInfo Line[MAX_POINTS];
LineInfo data[MAX_POINTS] = {};


LineInfo savedLines[MAX_POINTS] = {};
int numSavedLines;

LineInfo lineinfo[MAXLINENUMBER];
int numLines[MAXLINENUMBER] = { 0 };

DotAndBox::DotAndBox() : guidePointflg(false)
{
	endX = 0;
	endY = 0;

	pointerX = 450;
	pointerY = 275;

	int ScreenWidth = SCREEN_WIDTH;
	int ScreenHeight = SCREEN_HEIGHT;

	// �O���b�h���̓_��`��(�h�b�g�̊J�n�ʒu���萔�����Ă��邽�ߍ��x�C�� startX, startY, rows, columns�̕ύX)
	gridSize = 150;  // �O���b�h�̊Ԋu
	startX = 480;   // �J�nX���W
	startY = 250;   // �J�nY���W

	Drawflg = false;

	selectedPointX = 0;
	selectedPointY = 0;

	drawnPointX = 0;
	drawnPointY = 0;

	numDrawnLines = 0;

	selectedLine.LinestartX = 0;
	selectedLine.LinestartY = 0;
	selectedLine.LineendX = 0;
	selectedLine.LineendY = 0;

	// savedLines �z���������
	for (int i = 0; i < MAX_POINTS; ++i) {
		savedLines[i] = {}; // �f�t�H���g�R���X�g���N�^�ŏ�����
	}

	for (int i = 0; i < 20; i++)
	{
		Line_check[i] = 0;
	}
	for (int i = 0; i < 5; i++)
	{
		Box_check[i] = 0;
	}

	currentturn = 0;

	Bcnt = 4;
	Rcnt = 0;

	OnClicked = 0;
}

DotAndBox::~DotAndBox() {

}

void DotAndBox::DrawGridOfPoints(int startX, int startY, int gridSize, int rows, int columns) const {
	int lineThickness = 5;  // ���̑���
	int originalrows = rows;
	int originalcolumns = columns;
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			int x = startX + i * gridSize;
			int y = startY + j * gridSize;
			DrawCircle(x, y, 10, GetColor(255, 255, 255), TRUE);
		}
	}
	// �K�C�h�̕`��
	int guideX, guideY;
	GetNearestPoint(pointerX, pointerY, startX, startY, gridSize, rows, columns, guideX, guideY);
	DrawCircle(guideX, guideY, 12, GetColor(0, 255, 0), TRUE, 3);  // �K�C�h�����΂ŕ`��

}

void DotAndBox::Update() {

	g_Oldkey = g_Nowkey;
	g_Nowkey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	Keyflg = g_Nowkey & ~g_Oldkey;

	// �ړ���̈ʒu���ꎞ�I�Ɍv�Z
	int tempX = pointerX;
	int tempY = pointerY;

	if (Keyflg & PAD_INPUT_LEFT) {
		tempX -= GetgridSize();  // ���Ɉړ�
	}
	if (Keyflg & PAD_INPUT_RIGHT) {
		tempX += GetgridSize();  // �E�Ɉړ�
	}
	if (Keyflg & PAD_INPUT_UP) {
		tempY -= GetgridSize();  // ��Ɉړ�
	}
	if (Keyflg & PAD_INPUT_DOWN) {
		tempY += GetgridSize();  // ���Ɉړ�
	}

	// ��ʂ���͂ݏo�Ȃ��悤�ɏC��
	if (tempX > GetgridSize() * 3 && tempX < SCREEN_WIDTH - GetgridSize() * 3) {
		pointerX = tempX;
	}

	if (tempY > GetgridSize() && tempY < SCREEN_HEIGHT - GetgridSize()) {
		pointerY = tempY;
	}

	if (Keyflg & PAD_INPUT_A) {
		if (guidePointflg) {
			GetLineNumber(guidePointX, guidePointY, pointerX, pointerY);

			AddLineInfo(guidePointX, guidePointY, pointerX, pointerY);

			guidePointflg = false;
		}
		else {

			// �K�C�h�_��ۑ�
			guidePointX = pointerX;
			guidePointY = pointerY;
			guidePointflg = true;

			Drawflg = true;
		}

	}

	BoxCheck(Line_check);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int x = startX + i * gridSize;
			int y = startY + j * gridSize;
			DrawCircle(x, y, 10, GetColor(255, 255, 255), TRUE);

			// �`�悵���_�̍��W��ۑ�
			if (numDrawnPoints < MAX_POINTS) {
				drawnPoints[numDrawnPoints].x = x;
				drawnPoints[numDrawnPoints].y = y;
				numDrawnPoints++;

				// �`�悵���_�̍��W��n��
				SetDrawnPoint(x, y);

			}
		}
	}

	SetgridSize(gridSize);
}

void DotAndBox::Draw() const {

	// �|�C���^�[��`��
	DrawCircle(pointerX - 30, pointerY + 30, 10, GetColor(0, 255, 0), TRUE);

	// �O���b�h���̓_��`��(�h�b�g�̊J�n�ʒu���萔�����Ă��邽�ߍ��x�C�� startX, startY, rows, columns�̕ύX)
	//int gridSize = 150;  // �O���b�h�̊Ԋu
	//int startX = 480;   // �J�nX���W
	//int startY = 250;   // �J�nY���W
	int rows = 3;       // �s��
	int columns = 3;    // ��



	DrawGridOfPoints(startX, startY, gridSize, rows, columns);

	SetFontSize(30);
	DrawSavedLine(lineinfo, Line_check);

	DxLib::DrawFormatString(480, 100, GetColor(100, 100, 255), "Blue : %d", Bcnt);
	DxLib::DrawFormatString(660, 100, GetColor(255, 0, 0), "Red : %d", Rcnt);
	
	if (Bcnt + Rcnt == 4) {
		if (Bcnt == Rcnt) {
			SetFontSize(100);
			DxLib::DrawFormatString(425, 300, GetColor(0, 255, 0), "��������");
		}
		else if (Bcnt > Rcnt) {
			SetFontSize(100);
			DxLib::DrawFormatString(425, 300, GetColor(50, 50, 255), "�̏���");
		}
		else if (Bcnt < Rcnt) {
			SetFontSize(100);
			DxLib::DrawFormatString(425, 300, GetColor(255, 0, 0), "�Ԃ̏���");
		}
	}
}

int DotAndBox::Result() {

	SetBcnt(Bcnt);
	SetRcnt(Rcnt);

	if (BoxCheck(Line_check) != 0) {
		for (int i = 0; i < MAXBOX; i++) {
			if (Box_check[i] == 1) {
				Bcnt++;
			}
			else if (Box_check[i] == 2 ) {
				Rcnt++;

			}
		}
	}

	if(Bcnt + Rcnt == 4)
	if (Bcnt == Rcnt) {
		return 1;
	}
	else if (Bcnt > Rcnt) {
		return 2;
	}
	else if (Bcnt < Rcnt) {
		return 3;
	}
	return 0;
}


void DotAndBox::SetDrawnPoint(int x, int y) {
	drawnPointX = x;
	drawnPointY = y;

	SetPointer(x, y);
}

int DotAndBox::GetDrawnPointX() {
	return drawnPointX;
}

int DotAndBox::GetDrawnPointY() {
	return drawnPointY;
}

void DotAndBox::SetgridSize(int size) {
	gridSize = size;
}

int DotAndBox::GetgridSize() const {
	return gridSize;
}

void DotAndBox::GetNearestPoint(int pointerX, int pointerY, int startX, int startY, int gridSize, int rows, int columns, int& nearestX, int& nearestY) const {

	LineInfo line;
	line.LinestartX = startX;
	line.LinestartY = startY;
	line.LineendX = endX;
	line.LineendY = endY;

	int linestartX = line.LinestartX;
	int linestartY = line.LinestartY;
	int lineendX = line.LineendX;
	int lineendY = line.LineendY;

	double lineLength = sqrt(pow(endX - startX, 2) + pow(endY - startY, 2));
	double u = ((pointerX - startX) * (endX - startX) + (pointerY - startY) * (endY - startY)) / (lineLength * lineLength);

	if (u < 0.0) {
		// �J�[�\���������̎n�_�����O�ɂ���ꍇ
		nearestX = linestartX;
		nearestY = linestartY;
	}
	else if (u > 1.0) {
		// �J�[�\���������̏I�_�������ɂ���ꍇ
		nearestX = endX;
		nearestY = endY;
	}
	else {
		// �J�[�\����������ɂ���ꍇ
		nearestX = static_cast<int>(linestartX + u * (endX - linestartX));
		nearestY = static_cast<int>(linestartY + u * (endY - linestartY));
	}

	double minDistance = sqrt(pow(startX - pointerX, 2) + pow(startY - pointerY, 2));

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			int x = startX + i * gridSize;
			int y = startY + j * gridSize;
			double distance = sqrt(pow(x - pointerX, 2) + pow(y - pointerY, 2));

			if (distance < minDistance) {
				minDistance = distance;
				nearestX = x;
				nearestY = y;
			}
		}
	}
}

void DotAndBox::SelectNearestPointOnLine(int pointerX, int pointerY) {
	int nearestPointX, nearestPointY;

	for (int i = 0; i < numDrawnLines; ++i) {
		const LineInfo& line = data[i];

		// �J�[�\��������̓_��I��
		GetNearestPoint(pointerX, pointerY, line.LinestartX, line.LinestartY, 3, 3, 3, nearestPointX, nearestPointY);

		// �I�����ꂽ�_�̍��W��ۑ�
		SetDrawnPoint(nearestPointX, nearestPointY);
		Drawflg = true;

		// �V�������̏����쐬
		LineInfo newLine = { nearestPointX, nearestPointY, drawnPointX, drawnPointY };

		// �I�����ꂽ���̏����X�V
		selectedLine = newLine;

	}
}

void DotAndBox::DrawGuideLine(int startX, int startY, int endX, int endY, int color, int thickness) const {
	DrawLine(startX, startY, endX, endY, color, thickness);
}

void DotAndBox::AddLineInfo(int startX, int startY, int endX, int endY) {
	int lineNumber = GetLineNumber(startX, startY, endX, endY); // GetLineNumber �֐����Ăяo���Đ��̔ԍ����擾

	 //X�̎n�_���I�_���傫���Ƃ�
	if (startX > endX) {
		int x = startX;
		startX = endX;
		endX = x;
	}
	//Y�̎n�_���I�_���傫���Ƃ�
	if (startY > endY) {
		int y = startY;
		startY = endY;
		endY = y;
	}

	// ���W�̕ۑ�
	lineinfo[lineNumber].LinestartX = startX;
	lineinfo[lineNumber].LinestartY = startY;
	lineinfo[lineNumber].LineendX = endX;
	lineinfo[lineNumber].LineendY = endY;
	lineinfo[lineNumber].Drawnturn = GetLineColor();

	Line_check[lineNumber] = 1;

	this->SwitchTurn();

}

bool DotAndBox::IsAlreadyLined(const int Line_check[], int lineIndex) {
	if (Line_check[lineIndex] == 1) {
		return true;   // �d������
	}
	return false; // �d���Ȃ�
}

void DotAndBox::DrawSavedLine(const LineInfo lineinfo[MAXLINENUMBER], const int Line_check[]) const {
	for (int i = 0; i < MAXLINENUMBER; ++i) {
		const LineInfo& line = lineinfo[i];
		if (Line_check[i] != 0) {
			// ���̎n�_���W�ƏI�_���W�������Ƃ��[���łȂ��ꍇ�ɕ`�揈�����s��
			if (line.LinestartX != 0 && line.LinestartY != 0 && line.LineendX != 0 && line.LineendY != 0) {
				DrawGuideLine(line.LinestartX, line.LinestartY, line.LineendX, line.LineendY, line.Drawnturn, 3);
				//dotandbox.BoxCheck(Line_check);
			}
		}
	}
}

void DotAndBox::DrawCreatedBox(const LineInfo lineinfo[MAXLINENUMBER], const int Line_check[]) const {
	for (int i = 0; i < MAXLINENUMBER; ++i) {
		const LineInfo& line = lineinfo[i];
		if (Line_check[i] != 0) {
		}
	}
}

bool DotAndBox::IsValidLine(const LineInfo lineinfo[MAXLINENUMBER], const int line_check[]) const {
	for (int i = 0; i < MAXLINENUMBER; ++i) {
		const LineInfo& line = lineinfo[i];
		// �c���̐��̂ݕ`�悷��ꍇ
		if (line.LinestartX != line.LineendX && line.LinestartY != line.LineendY) {
			return false;
		}

		// ���̒����ȉ��̐��͕`�悵�Ȃ��ꍇ�i��FgridSize��1.5�{�ȉ��j
		double length = sqrt(pow(line.LineendX - line.LinestartX, 2) + pow(line.LineendY - line.LinestartY, 2));
		if (length <= GetgridSize() * 1.5) {
			return false;
		}
		//�������łɈ�����Ă���ꍇ
	   /* if (!IsAlreadyLined)*/
			// �����_���������ꍇ
		if (line.LinestartX == line.LineendX && line.LinestartY == line.LineendY) {
			return false;
		}
	}

	return true;
}

void DotAndBox::SwitchTurn() {
	if (currentturn == 1) {
		currentturn = 2; // �^�[�����v���C���[2�ɐ؂�ւ���
	}
	else {
		currentturn = 1; // �^�[�����v���C���[1�ɐ؂�ւ���
	}
}

int DotAndBox::GetLineColor() {
	if (GetCurrentTurn() == 1) {
		return GetColor(255, 0, 0); // �v���C���[1�̃^�[���Ȃ��Ԃ�
	}
	else {
		return GetColor(0, 0, 255); // �v���C���[2�̃^�[���Ȃ�Ԃ�Ԃ�
	}
}

int DotAndBox::GetLineNumber(int startX, int startY, int endX, int endY) {

	//X�̎n�_���I�_���傫���Ƃ�
	if (startX > endX) {
		int x = startX;
		startX = endX;
		endX = x;
	}
	//Y�̎n�_���I�_���傫���Ƃ�
	if (startY > endY) {
		int y = startY;
		startY = endY;
		endY = y;
	}

	if (startX == 480) {
		if (startY == 250) {
			if (endX == 630) {
				return 0;
			}
			else if (endX == 480) {
				return 2;
			}
		}
		else if (startY == 400) {
			if (endX == 630) {
				return 5;
			}
			else if (endX == 480) {
				return 7;
			}
		}
		else if (startY == 550) {
			if (endX == 630) {
				return 10;
			}
		}
	}
	else if (startX == 630) {
		if (startY == 250) {
			if (endX == 780) {
				return 1;
			}
			else if (endX == 630) {
				return 3;
			}
		}
		else if (startY == 400) {
			if (endX == 780) {
				return 6;
			}
			else if (endX == 630) {
				return 8;
			}
		}
		else if (startY == 550) {
			if (endX == 780) {
				return 11;
			}
		}
	}
	else if (startX == 780) {
		if (startY == 250) {
			if (endX == 780) {
				return 4;
			}
		}
		else if (startY == 400) {
			if (endX == 780) {
				return 9;
			}
		}
	}
	return -10;
}

int DotAndBox::BoxCheck(const int Line_check[]) {
	if ((Line_check[0] != 0 && Line_check[2] != 0) && Line_check[3] != 0 && Line_check[5] != 0) {
		if (Box_check[0] == 0) {
			Box_check[0] = GetCurrentTurn();
			return 1;
		}
	}
	if ((Line_check[1] != 0 && Line_check[4] != 0) && Line_check[3] != 0 && Line_check[6] != 0) {
		if (Box_check[1] == 0) {
			Box_check[1] = GetCurrentTurn();
			return 1;
		}
	}
	if ((Line_check[7] != 0 && Line_check[10] != 0) && Line_check[5] != 0 && Line_check[8] != 0) {
		if (Box_check[2] == 0) {
			Box_check[2] = GetCurrentTurn();
			return 1;
		}
	}
	if ((Line_check[9] != 0 && Line_check[11] != 0) && Line_check[6] != 0 && Line_check[8] != 0) {
		if (Box_check[3] == 0) {
			Box_check[3] = GetCurrentTurn();
			return 1;
		}
	}
	if (Line_check[3] != 0) {
		if ((Line_check[0] != 0 && Line_check[2] != 0) && Line_check[5] != 0) {
			if (Box_check[0] == 0) {
				Box_check[0] = GetCurrentTurn();
			}
		}
		if ((Line_check[1] != 0 && Line_check[4] != 0) && Line_check[6] != 0) {
			if (Box_check[1] == 0) {
				Box_check[1] = GetCurrentTurn();
			}
		}
		return 1;
	}
	if (Line_check[5] != 0) {
		if ((Line_check[0] && Line_check[2] != 0) && Line_check[3] != 0) {
			if (Box_check[0] == 0) {
				Box_check[0] = GetCurrentTurn();
			}

		}
		if ((Line_check[7] != 0 && Line_check[10] != 0) && Line_check[8] != 0) {
			if (Box_check[2] == 0) {
				Box_check[2] = GetCurrentTurn();
			}
		}
		return 1;
	}
	if (Line_check[6] != 0) {
		if ((Line_check[1] && Line_check[4] != 0) && Line_check[3] != 0) {
			if (Box_check[1] == 0) {
				Box_check[1] = GetCurrentTurn();
			}
		}
		if ((Line_check[9] != 0 && Line_check[11] != 0) && Line_check[8] != 0) {
			if (Box_check[3] == 0) {
				Box_check[3] = GetCurrentTurn();
			}
		}
		return 1;
	}
	if (Line_check[8] != 0) {
		if ((Line_check[7] && Line_check[10] != 0) && Line_check[5] != 0) {
			if (Box_check[2] == 0) {
				Box_check[2] = GetCurrentTurn();
			}
		}
		if ((Line_check[9] != 0 && Line_check[11] != 0) && Line_check[6] != 0) {
			if (Box_check[3] == 0) {
				Box_check[3] = GetCurrentTurn();
			}
		}
		return 1;
	}
	return 0;
}