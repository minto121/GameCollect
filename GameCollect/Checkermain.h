#pragma once
#include "AbstractScene.h"
#include <DxLib.h>


#define Speace 0
#define Black 1
#define White 2
class Checkermain:
	public AbstractScene
{

private:
	int Boardimg; //@”Õ
	int PieceB; //@‹î•
	int PieceW; // ‹î”’
	int Checkerback; // ”wŒi
	int size = 100;
	int board[8][8] =
	{
	0, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 0,
	0, 1, 0, 1, 0, 1, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 2, 0, 2, 0, 2, 0, 2,
	2, 0, 2, 0, 2, 0, 2, 0,
	0, 2, 0, 2, 0, 2, 0, 2, };
	int selectX;
	int selectY;

	int g_OldKey ;
	int g_NowKey;
	int g_KeyFlg ;

public:
	Checkermain();

	~Checkermain();

	//•`‰æˆÈŠO‚ÌXV‚ğÀs
	AbstractScene* Update() override;

	//•`‰æ‚ÉŠÖ‚·‚é‚±‚Æ‚ğÀ‘•
	void Draw() const override;


};

