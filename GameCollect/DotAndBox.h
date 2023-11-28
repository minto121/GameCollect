#pragma once
#include "Line.h"
#include "DxLib.h"
#include <math.h>


class Line;  // Line クラスの前方宣言

struct Point {
	int x;
	int y;

	// デフォルトコンストラクタを追加
	Point() : x(0), y(0) {}
};

class DotAndBox {
private:

	Line* line;

	int pointerX;
	int pointerY;

	int g_Oldkey;
	int g_Nowkey;
	int Keyflg;

public:

	

	DotAndBox();
	~DotAndBox();
	void DrawGridOfPoints(int startX, int startY, int gridSize, int rows, int columns) const;
	void Update();
	void Draw() const;

	void Getpointer(int& x, int& y) {
		x = pointerX;
		y = pointerY;
	}

	int GetPointerX() const { return pointerX; }
	int GetPointerY() const { return pointerY; }
};
