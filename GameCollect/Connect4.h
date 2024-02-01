#pragma once

/*クラス名・ヘッダーのファイル名がSixBallPuzzleになっているのは諸事情によるものです。
	実際にはConnect4.hです*/

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
	int Stage[7][6] = {};	//ステージの配列化
	unsigned int Cr;

	int Cursor = 0;	//カーソルのX値
	int Num = 1;	//カーソルの位置
	
	int gStageImg;		//ステージ画像
	int gCursorImg;		//カーソル画像
	int gRedCoinImg;	//赤のコイン
	int gYellowCoinImg;	//黄色のコイン
	int gClearImg;		//クリア表示

	int Clear = 0;		//クリアチェック
	int TimeCnt = 0;	//時間のカウント

	int CheckAnswer;
public:
	Connect4();

	~Connect4();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;

	bool CheckConnect(int x, int y, int type);

	int CheckConnectMin(int x, int y, int type, int cnt); // 繋がっているかのチェック
};

