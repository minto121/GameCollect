//#pragma once
//#include "AbstractScene.h"
//#include <math.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//const int MaxBalls = 1;
//const int HEIGHT = 720;
//const int WIDTH = 1280;
//
//
//class SixBallPuzzle:public AbstractScene{
//
//private:
//	/*定数の宣言*/
//	const int BLOCKSIZE = 24;	// ブロック画像のサイズ
//	const int NEWBLOCK_X = 4;	// NewブロックX座標
//	const int NEWBLOCK_Y = 0;	// NewブロックY座標
//
//	/*画像用変数*/
//	int Ball_img[4];		//ボール
//	int Back_Ground;		//背景画像
//
//	//int FallingX = 360;			//落下するブロックのX座標（固定位置）
//	//int FallingY = 100;			//落下するブロックのY座標（初期位置）
//	//int randomBallIndex;
//	
//	int g01dKey;			// 前回の入力キー
//	int gNowKey;			// 今回の入力キー
//	int gKeyFlg;			// 入力キー情報
//
//	int Random = 0;						//乱数の取得
//	int gStage[HEIGHT][WIDTH];						//ステージ配列
//	int gBlockImg[10];								//ブロック画像
//	int gLevel;										//	レベルアップ変数
//	int gSpeed[6] = { 1000,800,600,500,300,150 };	//	落下スピード配列
//
//	int BallY;
//
//	float ballX[MaxBalls];     // X座標の配列
//	float ballY[MaxBalls];     // Y座標の配列
//	float ballSpeed[MaxBalls]; // 落下速度の配列
//	bool ballActive[MaxBalls]; // ボールがアクティブかどうかの配列
//	
//	int gNewBlock[4][4] = { 0 };				//新しいブロック用
//	int gNextBlock[4][4] = { 0 };				//次のブロック用
//	int gStokBlock[4][4] = { 0 };				//ストックブロック用
//	int gStokFlg = 0;							//ストックフラグ
//
//	int gBlockList[3][5][3] = {
//	{ {0,0,0},{0,1,1},{0,1,1},{0,0,0} },
//	{ {0,0,0},{0,0,0},{2,2,2},{0,0,0} },
//	{ {0,0,0},{3,0,0},{3,3,3},{0,0,0} },
//	};
//
//	int gPosX = NEWBLOCK_X;	//　NewブロックのX座標
//	int gPosY = NEWBLOCK_Y;	//　NewブロックのY座標
//
//	int gStartTime;			//　時間計測の開始時間
//
//public:
//	void CreateBlock(void);				//ブロック生成とNEXTブロックの移動
//	void ControlBoll(void);			// ブロックの座標処理
//	int CheckOverlap(int x2, int y2);	//　ブロックの移動可能チェック処理
//	void TurnBlock(void);				// ブロックの回転処理
//	void LockBlock(int x2, int y2);		// 着地したブロックを固定済みブロックに加える
//	void CheckLines(void);				//　ブロックが横一列の時の処理
//	void ChangeBlock(void);				//　ブロックの交換（ストック処理）
//
//
//	SixBallPuzzle();
//
//	~SixBallPuzzle();
//
//	//描画以外の更新を実行
//	AbstractScene* Update() override;
//
//	//描画に関することを実装
//	void Draw() const override;
//
//};
//
