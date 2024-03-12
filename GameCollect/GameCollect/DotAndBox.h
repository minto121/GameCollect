#pragma once
#include "DxLib.h"
#include "AbstractScene.h"
#include <math.h>
#define MAX_POINTS 1000  // �ۑ��ł���ő�̓_�̐�
#define MAXLINENUMBER 20
#define MAX_DATA 5
#define MAXBOX 5

struct Point {
	int x;
	int y;
};

struct Linepoint {
	Point start;
	Point end;
};


// �V�������W����ۑ�����\����
struct LineInfo {
	int LinestartX;
	int LinestartY;
	int LineendX;
	int LineendY;
	int Drawnturn;
};


class DotAndBox
{
private:

	int pointerX;
	int pointerY;

	int g_Oldkey;
	int g_Nowkey;
	int Keyflg;

	int startX;
	int startY;
	int endX;
	int endY;
	int gridSize;
	int row;
	int col;

	bool Drawflg;

	// �V�������W����ۑ�����z��
	LineInfo drawnLines[MAX_POINTS];
	int numDrawnLines;
	LineInfo selectedLine;

	int Line_check[MAXLINENUMBER];
	int Box_check[MAXBOX];

	// �`�悵���_�̍��W��ێ�����ϐ�
	int drawnPointX;
	int drawnPointY;

	int selectedPointX;  // �I�����ꂽ�_�̍��W
	int selectedPointY;
	
	int guidePointX;
	int guidePointY;
	bool guidePointflg;

	int currentturn = 1;

	int Rline;
	int Bline;

	int Bflg;
	int Bcnt;
	int Rcnt;

	int OnClicked;

public:

	DotAndBox();
	virtual ~DotAndBox();
	void DrawGridOfPoints(int startX, int startY, int gridSize, int rows, int columns) const;
	void Update();
	void Draw() const;
	int Result();


	int GetBcnt() const {
		return Bcnt;
	}
	int GetRcnt() const {
		return Rcnt;
	}

	void SetBcnt(int b) {
		Bcnt = 0;
	}

	void SetRcnt(int r) {
		Rcnt = 0;
	}

	void Getpointer(int& x, int& y){
		x = pointerX;
		y = pointerY;
	}

	void SetPointer(int x, int y) {
		pointerX = x;
		pointerY = y;
	}

	int GetgridSize() const;
	void SetgridSize(int size);

	void DrawGuideLine(int startX, int startY, int endX, int endY, int color, int thickness)const;

	void AddLineInfo(int startX, int startY, int endX, int endY);
	void DrawSavedLine(const LineInfo lineinfo[MAXLINENUMBER], const int Line_check[]) const;
	void DrawCreatedBox(const LineInfo lineinfo[MAXLINENUMBER], const int Line_check[]) const;
	void GetNearestPoint(int pointerX, int pointerY, int startX, int startY, int gridSize, int rows, int columns, int& nearestX, int& nearestY) const;
	void SelectNearestPointOnLine(int pointerX, int pointerY);

	void SetDrawnPoint(int x, int y);
	int GetDrawnPointX();
	int GetDrawnPointY();
	void ResetSelection();

	bool IsValidLine(const LineInfo lineinfo[MAXLINENUMBER], const int Line_check[]) const;

	bool IsAlreadyLined(const int Line_check[], int lineIndex);

	int GetCurrentTurn(){
		return currentturn;
	}

	void SwitchTurn();
	int GetLineColor();
	
	int GetLineNumber(int sx, int sy, int ex, int ey);

	int BoxCheck(const int Line_check[]);

	int OnButtonClicked() {

		g_Oldkey = g_Nowkey;
		g_Nowkey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		Keyflg = g_Nowkey & ~g_Oldkey;

		if (Keyflg & PAD_INPUT_B) {
			return 1;
		}
		return 0;
	}
};
