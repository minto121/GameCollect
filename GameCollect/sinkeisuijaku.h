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


	//ƒgƒ‰ƒ“ƒv‚Ì‰æ‘œ—p•Ï”
	int S_D1;
	int S_D2;
	int S_D3;
	int S_D4;
	int S_D5;
	int S_D6;
	int S_D7;
	int S_D8;
	int S_D9;
	int S_D10;

	int S_H1;
	int S_H2;
	int S_H3;
	int S_H4;
	int S_H5;
	int S_H6;
	int S_H7;
	int S_H8;
	int S_H9;
	int S_H10;
};

