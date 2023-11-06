#pragma once
#include "AbstractScene.h"
class Mankara :public AbstractScene
{
private:

	/*struct StoneSet
	{
		float x;
		float y;
		float detection;
		int img[6];
		int count;
		bool Flg;
		int Event;
	};
	struct StoneSet Stone[8];*/
	int Board;
	int Background;
	int RedStone;
	int BlueStone;
	int GreenStone;
	int YellowStone;
	int PurpleStone;
	int WhiteStone;

	int Stone[6][8];

	int redStone[8];
	int blueStone[8];
	int greenStone[8];
	int yellowStone[8];
	int purpleStone[8];
	int whiteStone[8];
	int RINE;
	int i;
	int j;
	int P1Turn;
	int P2Turn;


	// 1P用ポケット
	int P1Pocket[6];
	
	int Pocket1[1][5];
	// 2P用ポケット
	int P2Pocket[6];
	

	int P1BigPocket;
	int P2BigPocket;


	int StoneImg[6];

public:
	Mankara();
	AbstractScene* Update();
	void Draw() const;
};

