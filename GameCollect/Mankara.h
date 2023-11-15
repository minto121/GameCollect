#pragma once
#include "AbstractScene.h"
class Mankara :public AbstractScene
{
private:

	

	int Board; // ゲームボードの画像
	int Background; // 背景画像

	int P1Turn;
	int P2Turn;

	struct STONE
	{
		int flg = 1;
		int img[6][8];
	} ;

	struct STONE gStone;


	int PlayerPocket;


	// 1P用ポケット
	int P1Pocket[6];
	// 2P用ポケット
	int P2Pocket[6];
	

	int P1BigPocket; //1Pのゴール
	int P2BigPocket; //2Pのゴール


	int StoneImg[6]; // 石の画像

	int Pocket_cnt;

	int InitialStone;
	int Stone_cnt;
	int movePocket;

	int StonePocket[12]; // 石入れてるポケット
	int sideAddition;      // 移動させるための処理
	int Stonenum;          // 配列の中の石の総数

public:
	Mankara();
	AbstractScene* Update();
	void Draw() const;
};

