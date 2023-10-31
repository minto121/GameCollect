#pragma once
#include "AbstractScene.h"
class Porker : public AbstractScene
{
private:
	int b;
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

	int Mark1;

public:
	Porker();

	~Porker();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;



	void ROUND_INIT();

	void P_CALL();

	void ENEMIE_CHOISE();

	void PLAYER_RAISE();

	
};

