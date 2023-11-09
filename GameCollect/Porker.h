#pragma once
#include "AbstractScene.h"
class Porker : public AbstractScene
{
private:
	
	int a;
	int wt;
	int ps1;
	int es1;
	int Bs;
	int BTN_flg;
	int P_FPS;
	int P_TEKI;
	int WP;
	int WP2;
	int WP3;
	int WP4;
	int WP_FLG[5];
	int YP[4];
	int YP2[4];
	int YE[4];

	int Winflg;
	int Loseflg;
	int Drawflg;
	int E_Fouldflg;
	int E_CAllflg;
	int E_Raiseflg;
	int P_Call_H_flg;
	int P_Raise_H_flg;
	int P_Fould_H_flg;
	int E_Fould_H_flg;
	int G_Over_H_flg;
	int WTflg[3];
	
	int WTRelese[3];
	
	int BTN_RELESE_FLG[6];
	
	int P_F_flg;
	int RC_H_flg;
	int CARD_URA_H_flg;

	int Tranpu_Img[56];
	int Back;
	int P_rand[2];
	
	int E_rand[2];
	
	int C_rand[5];
	
	int C_flg[3];

	int P_CARD_S[2];//プレイヤーカードの商格納用
	int P_CARD_A[2];//プレイヤーカードの余り格納用

	int E_CARD_S[2];//敵カードの商格納用
	int E_CARD_A[2];//敵カードの余り格納用

	int C_CARD_S[5];//場に出ているカード1~5の商格納用
	int C_CARD_A[5];//場に出ているカード1~5の余り格納用
	
	
	int P_PEA_FLG[4];//プレイヤーの1ペアのフラグ
	int P_2PEA_FLG;//プレイヤーの2ペアのフラグ
	int P_THREE_FLG;//プレイヤーのスリーカードのフラグ
	int P_FH_FLG;

public:
	Porker();

	~Porker();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;


	
	void ROUND_INIT();//ラウンド初期化

	void PLAYER_CALL();//プレイヤーのコール用関数

	void PLAYER_RAISE();//プレイヤーのレイズ用関数

	void ENEMIE_CHOISE();//敵の選択用関数

	void CARD_ANALYSIS();//カードの数字とマークを調べる用の関数

	void P_CARD_YAKU();//役つくりのための関数

	void P_CARD_YAKU3CARD();

	void P_CARD_FULLHOUSE();

};

