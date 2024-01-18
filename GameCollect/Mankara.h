#pragma once
#include "AbstractScene.h"
#include <DxLib.h>
class Mankara :public AbstractScene
{
private:
	int Board; // ゲームボードの画像
	int Background; // 背景画像

	int PocketEnter;// 0：未選択　１：選択した　２：相手のターン
	int MyTurn; // 自分のターンかどうか
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

	// 勝敗用フラグ
	int ResultFlg1;
	int ResultFlg2;
	// 勝敗を出す
	int ResultDraw1;
	int ResultDraw2;
	// ターン切り替え用フラグ
	int InputFlg;

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

	//ゲーム中の動く石の総数
	int FullStone;

	// 石の画像
	int StoneImg[6]; 

	int Pocket_cnt;

	// 初期石
	int InitialStone;
	int Stone_count;
	int StonePocket[12]; // 石入れてるポケット
	
	// ポケットの数と格納されている石の数
	int P1StoneSave[6]; 
	// ポケットの数と入っている石の数
	int P2StoneSave[6]; 


	int tmp;
	int tmp2;

public:
	Mankara();
	AbstractScene* Update();
	void Draw() const;
	// 石が移動した時の内部処理
	void MoveStone();
};