#pragma once

class Line {
private:
	int startX;
	int startY;
	int gridSize;
	int row;
	int col;
	int x1;
	int x2;
	int y1;
	int y2;
public:
	void DrawLine();
	void Update();
	void Draw();
};
