#pragma once
#include "AbstractScene.h"
class sinkeisuijaku :public AbstractScene
{
public:

	sinkeisuijaku();

private:


	struct TRUMPS {
		int flg = 0;
		int syurui = 0;
		int syunflg = 0;
	};
	

	TRUMPS trumps[10][10];

	int trumpflg = 0;

	virtual AbstractScene* Update()override;
	void Draw()const override;


	int first;

	int S_timg;
	int S_back;

	int g_KeyFlg;
	int S_ber = 0;
	int S2_ber = 0;
	int g_MenuY = 0;
	int g_OldKey;
	int g_NowKey;


	//ƒgƒ‰ƒ“ƒv‚Ì‰æ‘œ—p•Ï”
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
	int syuncount = 0;


};

