#pragma once
#include "AbstractScene.h"
class Porker : public AbstractScene
{
private:
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
public:
	Porker();

	~Porker();

	//•`‰æˆÈŠO‚ÌXV‚ğÀs
	AbstractScene* Update() override;

	//•`‰æ‚ÉŠÖ‚·‚é‚±‚Æ‚ğÀ‘•
	void Draw() const override;
};

