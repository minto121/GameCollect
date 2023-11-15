#pragma once
#include "AbstractScene.h"
class sinkeisuijaku :public AbstractScene
{
public:

	sinkeisuijaku();

private:

	int isPlayerTurn = 1;  // プレイヤーのターンかどうかを示すフラグ
	int  isComputerTurn = 0;  // コンピューターのターンかどうかを示すフラグ

	struct PLAYER {
		int player = 0;
	};

	struct TRUMPS {
		int flg = 0;
		int syurui = 0;
		int syunflg = 0;
		int  visible = 0; // カードを画面に表示するかどうかのフラグ
	};
	
	PLAYER player[2];
	TRUMPS trumps[10][10];

	int trumpflg = 0;

	virtual AbstractScene* Update()override;
	void Draw()const override;


	void ComputerTurn();
	void CheckMatched();

	int first;

	int S_timg;
	int S_back;

	int g_KeyFlg;
	int S_ber = 0;
	int S2_ber = 0;
	int g_MenuY = 0;
	int g_OldKey;
	int g_NowKey;


	//トランプの画像用変数
	int S_T[55];


	int S_TD[10];
	int S_TH[10];


	int grid[4][5];
	int shuffle_flg = 0;

	int x;
	int r;
	int r2;
	int count = 0;
	int randend = 0;

	int T_Draw[10];
	int rCount = 0;
	int r2Count = 0;


	int syun1;
	int syun2;
	int syun3;

	int testcount = 0;

	int syuncount = 0;

	int Time = 0;

	int testflg = 0;

	int pea = 0;
};

