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
	int Boardimg; //　盤
	int PieceB; //　駒黒
	int PieceW; // 駒白
	int Checkerback; // 背景
	int size = 100;
	int board[8][8];
		
	/*{
		0, 1, 0, 1, 0, 1, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 0,
		0, 1, 0, 1, 0, 1, 0, 1,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 2, 0, 2, 0, 2, 0, 2,
		2, 0, 2, 0, 2, 0, 2, 0,
		0, 2, 0, 2, 0, 2, 0, 2, };*/
	int selectX;
	int selectY;
	int g_OldKey ;
	int g_NowKey;
	int g_KeyFlg ;

public:
	Checkermain();

	~Checkermain();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;

	// ブロック配列の初期化
	void InitBlock() const ;
};

