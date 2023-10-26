#pragma once
#include "AbstractScene.h"
class Porker : public AbstractScene
{
private:
	int a;
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


	int Tranpu_Img[52];
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

	void PLAYER_FOULD();
};

