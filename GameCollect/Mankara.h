#pragma once
#include "AbstractScene.h"
class Mankara:public AbstractScene
{
private:
    int RedStone;
	int BlueStone;
	int GreenStone;
	int YellowStone;
	// 1P用ポケット
	int Pocket1;
	int Pocket2;
	int Pocket3;
	int Pocket4;
	int Pocket5;
	int Pocket6;
	// 2P用ポケット
	int Pocket7;
	int Pocket8;
	int Pocket9;
	int Pocket10;
	int Pocket11;
	int Pocket12;
public:
	Mankara();
	AbstractScene* Update();
	void Draw() const;
};

