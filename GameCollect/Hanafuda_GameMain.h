#pragma once
#include"AbstractScene.h"
#define NUM_FUDA 4  //札の種類　４
#define MONTH 12  //月の種類　１２
#define FUDA 8    //場に出ている札


class Hanafuda:
	public AbstractScene
{
private:
	//カードの構造体
	// struct FUDA{
	//	long fuda[48];  //札
	//	int Month;  //月
	//	int draw_num[NUM_FUDA * MONTH];
 //	};
	// struct FUDA Fuda;
	////プレイヤーの構造体
	//struct PLAYER {
	//	int hand[8];  //手札のカード配列
	//	int num_hand; //手札のカードの枚数
	//}Player;
	//struct PLAYER player;
	//struct ENEMY {
	//	int hand[8];
	//	int num_hand;
	//};
	//struct ENEMY Enemy;
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
	int b;
	int  Playerflg;  //順番用 親フラグ（１：順番　０：待ち）
	int Partnerflg;	//順番用 子フラグ（１：順番　０：待ち）
	int P_judge;  //プレイヤー用 月判定
	int E_judge;  //AI用 月判定
	int Judgeflg;
	int Startflg;  //ゲームスタートフラグ
	int OyaGimeflg; //親決めフラグ()
	float P_FudaX, P_FudaY;//札座標
	float E_FudaX, E_FudaY;
	int shuffleflg;  //札配布用フラグ
	int Fudaflg;
	int Phase;
	int Monthflg;
	//int a; //札配布時用変数
	long P_numhand[8];
	int E_numhand[8];
	int tick;
	int Gameflg;
	int Pnum_hand; //手札枚数カウント
	long P_hand[8];//手札配列
	int HandImg_1;
	int n;
	int Field[8];
	int Fieldflg;
	int P_shuffleflg;
	int E_shuffleflg;
public:
	Hanafuda();
	~Hanafuda();
	virtual AbstractScene* Update()override;
	void Draw()const;
	void shuffleFuda(); //札配布
	void OyaGime() ; // 親決め
	void Month();
	void Oya();
	void Ko();
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
};