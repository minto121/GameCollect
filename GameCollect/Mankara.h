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

	struct REDSTONE
	{
		int flg = 1;
		int img[8];
	} ;

	struct REDSTONE RedStone;

	struct BLUESTONE
	{
		int flg = 1;
		int img[8];
	};

	struct BLUESTONE BlueStone;

	struct GREENSTONE
	{
		int flg = 1;
		int img[8];
	};

	struct GREENSTONE GreenStone;

	struct YELLOWSTONE
	{
		int flg = 1;
		int img[8];
	};

	struct YELLOWSTONE YellowStone;

	struct PURPLESTONE
	{
		int flg = 1;
		int img[8];
	};

	struct PURPLESTONE PurpleStone;

	struct WHITESTONE
	{
		int flg = 1;
		int img[8];
	};

	struct WHITESTONE WhiteStone;

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

