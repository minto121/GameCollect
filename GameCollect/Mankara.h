#pragma once
#include "AbstractScene.h"
class Mankara:public AbstractScene
{
private:
    int RedStone;
	int BlueStone;
	int GreenStone;
	int YellowStone;
	int PurpleStone;
	int WhiteStone;
	int redStone[8];
	int blueStone[8];
	int greenStone[8];
	int yellowStone[8];
	int purpleStone[8];
	int whiteStone[8];
	// 1P用ポケット
	int Pocket1;
	int Pocket2;
	int Pocket3;
	int Pocket4;
	int Pocket5;
	int Pocket6;
	int P1Pocket[6];

	// 2P用ポケット
	int Pocket7;
	int Pocket8;
	int Pocket9;
	int Pocket10;
	int Pocket11;
	int Pocket12;
	int P2Pocket[6];
public:
	Mankara();
	AbstractScene* Update();
	void Draw() const;
};

