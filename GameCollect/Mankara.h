#pragma once
#include "AbstractScene.h"
class Mankara :public AbstractScene
{
private:

	

	int Board;
	int Background;
	
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

	struct STONE
	{
		int flg = 1;
		int redimg[8];
		int blueimg[8];
		int greenimg[8];
		int yellowimg[8];
		int purpleimg[8];
		int whiteimg[8];

	} ;

	struct STONE gStone;





	// 1P用ポケット
	int P1Pocket[6];
	
	int Pocket1[1][5];
	// 2P用ポケット
	int P2Pocket[6];
	

	int P1BigPocket;
	int P2BigPocket;


	int StoneImg[6];

	int Pocket_cnt;

	int Stone_cnt;

public:
	Mankara();
	AbstractScene* Update();
	void Draw() const;
};

