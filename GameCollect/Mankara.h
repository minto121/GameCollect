#pragma once
#include "AbstractScene.h"
#include <DxLib.h>
class Mankara :public AbstractScene
{
private:
	int Board; // ゲームボードの画像
	int Background; // 背景画像

	//int P1PocketImg;
	//int P2PocketImg;

	int P1Turn;
	int P2Turn;

	struct STONE
	{
		int img;
	} ;
	// 色と個数
	struct STONE gStone[6][16];

	struct STONE2
	{
		int img;
	} ;
	// 石の色と個数
	struct STONE2 gStone2[6][16];


	// 1Pが選択しているポケット
	int PlayerPocket;
	// 2Pが選択しているポケット
	int PartnerPocket;

	// 1P用ポケット
	int P1Pocket[6];

	// 2P用ポケット
	int P2Pocket[6];
	
	//1Pのゴール
	int P1BigPocket; 
	//2Pのゴール
	int P2BigPocket;

	/*int BigPocket[6][40];
	int BigPocket2[6][40];*/

	// 石の画像
	int StoneImg[6]; 

	int Pocket_cnt;

	int InitialStone;
	int Stone_cnt;
	int movePocket;
	int Stone_count;
	int StonePocket[2][6]; // 石入れてるポケット
	int sideAddition;      // 移動させるための処理
	int Stonenum;          // 配列の中の石の総数

	int CountUp;

	bool StoneFlg;
	int moveStone; 
	int moveStone2;
	// ポケットの数と入っている石の数
	int P1StoneSave[6][4]; 
	// ポケットの数と入っている石の数
	int P2StoneSave[6][4]; 

	int JustGoal; //ぴったりゴール用 

public:
	Mankara();
	AbstractScene* Update();
	void Draw() const;
	// 石が移動した時の内部処理
	void MoveStone();
};