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
	int WTflg1;
	int WTflg2;
	int WTflg3;
	int WTRelese1;
	int WTRelese2;
	int WTRelese3;
	int BTN_RELESE_FLG1;
	int BTN_RELESE_FLG2;
	int BTN_RELESE_FLG3;
	int BTN_RELESE_FLG4;
	int BTN_RELESE_FLG5;
	int BTN_RELESE_FLG6;
	int P_F_flg;
	int RC_H_flg;
	int CARD_URA_H_flg;

	int Tranpu_Img[56];
	int Back;
	int P_rand1;
	int P_rand2;
	int E_rand1;
	int E_rand2;
	int C_rand1;
	int C_rand2;
	int C_rand3;
	int C_rand4;
	int C_rand5;

	int C_flg1;
	int C_flg2;
	int C_flg3;

	int P_CARD1_S;//プレイヤーカード1の商格納用
	int P_CARD2_S;//プレイヤーカード2の商格納用

	int P_CARD1_A;//プレイヤーカード1の余り格納用
	int P_CARD2_A;//プレイヤーカード2の余り格納用

	int E_CARD1_S;//敵カード1の商格納用
	int E_CARD2_S;//敵カード2の商格納用

	int E_CARD1_A;//敵カード1の余り格納用
	int E_CARD2_A;//敵カード2の余り格納用

	int C_CARD1_S;//場に出ているカード1の商格納用
	int C_CARD2_S;//場に出ているカード2の商格納用
	int C_CARD3_S;//場に出ているカード3の商格納用
	int C_CARD4_S;//場に出ているカード4の商格納用
	int C_CARD5_S;//場に出ているカード5の商格納用

	int C_CARD1_A;//場に出ているカード1の余り格納用
	int C_CARD2_A;//場に出ているカード2の余り格納用
	int C_CARD3_A;//場に出ているカード3の余り格納用
	int C_CARD4_A;//場に出ているカード4の余り格納用
	int C_CARD5_A;//場に出ているカード5の余り格納用
	int P_PEA_FLG;//プレイヤーのペアのフラグ

public:
	Porker();

	~Porker();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;



	void ROUND_INIT();

	void PLAYER_CALL();

	void PLAYER_RAISE();

	void ENEMIE_CHOISE();

	void CARD_ANALYSIS();

	void CARD_YAKU();
};

