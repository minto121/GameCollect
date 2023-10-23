#pragma once
#include "AbstractScene.h"

class DotAndBox :public AbstractScene {
private:

public:
	DotAndBox();
	~DotAndBox();
	void DrawGridOfPoints(int startX, int startY, int gridSize, int rows, int columns) const;
	virtual AbstractScene* Update() override;
	void Draw() const override;
};
