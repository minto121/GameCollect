#pragma once

#include "AbstractScene.h"
#include "DxLib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//画面サイズ (縦)→720
//画面サイズ (横))→1280

//const int HEIGHT = 12;
//const int WIDTH = 12;
const int BLOCKSIZE = 48;
const int MARGIN = 0;

class Connect4 :public AbstractScene{

private:
	int Board[6][7];
	unsigned int Cr;

	int Cursor;		//カーソル
	int Num = 0;	//カーソルの位置
	int gKeyFlg;	//今のキー

	int gStageImg;	//ステージ画像
	int gCursorImg;	//カーソル画像

public:

	int flg;		//フラグ（０：表示しない　１：表示する）
	int x, y;		//座標
	int w, h;		//幅、高さ
	int img;		//画像番号
	int backup;		//画像バックアップ

	//struct Block gStage[HEIGHT][WIDTH];

	Connect4();

	~Connect4();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;
};

