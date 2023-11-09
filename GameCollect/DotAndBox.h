#pragma once
#include "AbstractScene.h"
#include "DrawLine.h"

class DotAndBox {
private:
	Line line;

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
};
