#pragma once

class Line{
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
public:
	
	Line();
	~Line();

	bool IsVerticalLine(int x1, int y1, int x2, int y2);

	void Update();
	void Draw() const;

	int GetgridSize() { return gridSize; }
};
