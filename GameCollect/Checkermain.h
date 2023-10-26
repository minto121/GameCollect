#pragma once
#include "AbstractScene.h"
class Checkermain:
	public AbstractScene
{

private:
	int Boardimg; //@”Õ
	int PieceB; //@‹î•
	int PiceW; // ‹î”’
	int Checkerback; // ”wŒi

public:
	Checkermain();

	~Checkermain();

	//•`‰æˆÈŠO‚ÌXV‚ğÀs
	AbstractScene* Update() override;

	//•`‰æ‚ÉŠÖ‚·‚é‚±‚Æ‚ğÀ‘•
	void Draw() const override;

};

