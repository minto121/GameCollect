#pragma once
#include "AbstractScene.h"
class sinkeisuijaku :public AbstractScene
{
public:

private:


	struct TRUMPS {
		int flg;
		int syurui;
	};
	
	 struct Card{
		int cardValue;//カードの値
		int flg;//カードが選択されたかどうか
	};

	TRUMPS trumps[10][10];

	int trumpflg = 0;

	virtual AbstractScene* Update()override;
	void Draw()const override;

	void Select();

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

	int z[20];
};

