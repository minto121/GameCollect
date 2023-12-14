#pragma once
#include "AbstractScene.h"
class sinkeisuijaku :public AbstractScene
{
public:

	sinkeisuijaku();

	int  GetScore(int _x) {
		return  peacount;
	}

	int GetCScore(int _y) {
		return Cpeacount;
	}
private:

	int isPlayerTurn = 1;  // プレイヤーのターンかどうかを示すフラグ
	int  isComputerTurn = 0;  // コンピューターのターンかどうかを示すフラグ

	struct PLAYER {
		int player = 0;
	};

	struct TRUMPS {
		int flg = 0;
		int syurui = 0;
		int flg2 = 100;
		int  visible = 0; // カードを画面に表示するかどうかのフラグ
	};
	
	PLAYER player[2];
	TRUMPS trumps[10][10];

	int trumpflg = 0;

	virtual AbstractScene* Update()override;
	void Draw()const override;


	void ComputerTurn();
	void Memory();
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


	int select1;
	int select2;
	int select3;

	int testcount = 0;

	//int peacount = 0;

	  // 最後に選択されたカードの位置を追跡する変数を追加
	int lastSelect = -1;

	int pTime = 0;
	int cTime = 0;
	int testflg = 0;
	int pea = 0;

	int rebirth = 0;
	int selectedCard[2][2];
	int selectcount = 0;

	int peacount = 0;
	int Cpeacount = 0;
	//サウンド
	int BGM;
	int Select;
	int Select2;

	int soundcount = 0;
	int test1 = 0;


	int Resultflg = 0;

	int MemoryCount[5];
	int Memoryrebirth;
	int Memoryflg = 0;
	int M = 0;
	int M2;
	int M3;

};

