#pragma once
#include"AbstractScene.h"
#define NUM_FUDA 4  //札の種類　４
#define MONTH 12  //月の種類　１２
//#define ALL_FUDA[NUM_FUDA * MONTH] //札総数

class Hanafuda:
	public AbstractScene
{
private:
	//カードの構造体
	 struct FUDA{
		int fuda[48];  //札
		int Month;  //月
		int draw_num[NUM_FUDA * MONTH];
 	};
	 struct FUDA Fuda;
	//プレイヤーの構造体
	struct PLAYER {
		FUDA hand[NUM_FUDA];  //手札のカード配列
		int num_hand; //手札のカードの枚数
	}Player;
	struct PLAYER player;
	//static FUDA Fuda[NUM_FUDA];  //カードの配列
	int  FudaImg[48]; //札画像48枚
	int F_Img;
	int E_fudaImg;
	int E_fuda[7];
	int P_fudaImg;
	int P_fuda[7];
	int UraImg;  //札裏画像
	int U_Img;
	int Stage;        //背景画像
	int MouseX, MouseY;  //マウス座標
	int i;
	int j; //乱数用フラグ
	int z;
	int  Playerflg;  //順番用 親フラグ（１：順番　０：待ち）
	int Partnerflg;	//順番用 子フラグ（１：順番　０：待ち）
	int P_judge;  //プレイヤー用 月判定
	int E_judge;  //AI用 月判定
	int Judgeflg;
	int Startflg;  //ゲームスタートフラグ
	int OyaGimeflg; //親決めフラグ()
	float FudaX, FudaY;  //札座標
	int shuffleflg;  //札配布用フラグ
	int Fudaflg;
	int Phase;
	int Monthflg;
public:
	Hanafuda();
	~Hanafuda();
	virtual AbstractScene* Update()override;
	void Draw()const;
	void shuffleFuda(); //札配布
	void OyaGime() ; // 親決め

	int Kas();
	int Tan();
	int Tane();
	int Akatan();
	int Aotan();
	int Inosikatyou();
	int Hanami();
	int Tukimi();
	int Sankou();
	int Sikou();
	int Amesikou();
	int Gokou();
	int Koikoi();
	int Syobu();
	void Month() { //月判定
		//プレイヤー月判定
		switch (i) {
		case 0:
		case 1:
		case 2:
		case 3:
			P_judge = 1;
			break;
		case 4:
		case 5:
		case 6:
		case 7:
			P_judge = 2;
			break;
		case 8:
		case 9:
		case 10:
		case 11:
			P_judge = 3;
			break;
		case 12:
		case 13:
		case 14:
		case 15:
			P_judge = 4;
			break;
		case 16:
		case 17:
		case 18:
		case 19:
			P_judge = 5;
			break;
		case 20:
		case 21:
		case 22:
		case 23:
			P_judge = 6;
			break;
		case 24:
		case 25:
		case 26:
		case 27:
			P_judge = 7;
			break;
		case 28:
		case 29:
		case 30:
		case 31:
			P_judge = 8;
			break;
		case 32:
		case 33:
		case 34:
		case 35:
			P_judge = 9;
			break;
		case 36:
		case 37:
		case 38:
		case 39:
			P_judge = 10;
			break;
		case 40:
		case 41:
		case 42:
		case 43:
			P_judge = 11;
			break;
		case 44:
		case 45:
		case 46:
		case 47:
			P_judge = 12;
			break;
		}
		//AI用月判定
		switch (j) {
		case 0:
		case 1:
		case 2:
		case 3:
			E_judge = 1;
			break;
		case 4:
		case 5:
		case 6:
		case 7:
			E_judge = 2;
			break;
		case 8:
		case 9:
		case 10:
		case 11:
			E_judge = 3;
			break;
		case 12:
		case 13:
		case 14:
		case 15:
			E_judge = 4;
			break;
		case 16:
		case 17:
		case 18:
		case 19:
			E_judge = 5;
			break;
		case 20:
		case 21:
		case 22:
		case 23:
			E_judge = 6;
			break;
		case 24:
		case 25:
		case 26:
		case 27:
			E_judge = 7;
			break;
		case 28:
		case 29:
		case 30:
		case 31:
			E_judge = 8;
			break;
		case 32:
		case 33:
		case 34:
		case 35:
			E_judge = 9;
			break;
		case 36:
		case 37:
		case 38:
		case 39:
			E_judge = 10;
			break;
		case 40:
		case 41:
		case 42:
		case 43:
			E_judge = 11;
			break;
		case 44:
		case 45:
		case 46:
		case 47:
			E_judge = 12;
			break;
		}
	};  
};