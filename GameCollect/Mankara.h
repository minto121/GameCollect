#pragma once
#include "AbstractScene.h"
class Mankara:public AbstractScene
{
private:
    int RedStone;
	int BlueStone;
	int GreenStone;
public:
	Mankara();
	AbstractScene* Update();
	void Draw() const;
};

