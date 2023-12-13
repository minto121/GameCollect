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
	// 石の数とポケット
	struct STONE gStone[16][6];

	struct STONE2
	{
		int img;
	} ;
	// 石の数とポケット
	struct STONE2 gStone2[16][6];

	struct GOAL
	{
		int img;
	} ;
	// 石の色と個数
	struct GOAL gGoal[30][2];








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
	int StonePocket[12]; // 石入れてるポケット
	int sideAddition;      // 移動させるための処理
	int Stonenum;          // 配列の中の石の総数

	int CountUp;
	int moveStone; 
	int moveStone2;
	// ポケットの数と格納されている石の数
	int P1StoneSave[6]; 
	// ポケットの数と入っている石の数
	int P2StoneSave[6]; 

	int JustGoal; //ぴったりゴール用 

	int MoveStoneFlg; // 動いたかどうか確認するフラグ
	int MoveStoneFlg2; // 動いたかどうか確認するフラグ
	int MoveStoneFlg3; // 動いたかどうか確認するフラグ
	int MoveStoneFlg4; // 動いたかどうか確認するフラグ
	int MoveStoneFlg5; // 動いたかどうか確認するフラグ
	int MoveStoneFlg6; // 動いたかどうか確認するフラグ

public:
	Mankara();
	AbstractScene* Update();
	void Draw() const;
	// 石が移動した時の内部処理
	void MoveStone();
	void WinLose();
};