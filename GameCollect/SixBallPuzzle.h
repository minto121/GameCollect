#pragma once
#include "AbstractScene.h"

const int MaxBalls = 50;

class SixBallPuzzle:
	public AbstractScene
{

private:
	int ScreenHeight = 720;
	int ScreenWidth = 1280;

	/*画像用変数*/
	int Ball_img[4];		//ボール
	int Back_Ground;		//背景画像

	//int FallingX = 360;			//落下するブロックのX座標（固定位置）
	//int FallingY = 100;		//落下するブロックのY座標（初期位置）
	//int randomBallIndex;
	
	float ballX[MaxBalls];     // X座標の配列
	float ballY[MaxBalls];     // Y座標の配列
	float ballSpeed[MaxBalls]; // 落下速度の配列
	bool ballActive[MaxBalls];  // ボールがアクティブかどうかの配列
	
	int gNewBlock[4][4] = { 0 };		//新しいブロック用
	int gNextBlock[4][4] = { 0 };		//次のブロック用
	int gStokBlock[4][4] = { 0 };		//	ストックブロック用
	int gStokFlg = 0;					//	ストックフラグ

	int gBlockList[7][4][4] = {
	{ {0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0} },
	{ {0,0,0,0},{0,0,0,0},{2,2,2,2},{0,0,0,0} },
	{ {0,0,0,0},{3,0,0,0},{3,3,3,0},{0,0,0,0} },
	{ {0,0,0,0},{0,0,0,4},{0,4,4,4},{0,0,0,0} },
	{ {0,0,0,0},{0,5,5,0},{0,0,5,5},{0,0,0,0} },
	{ {0,0,0,0},{0,6,6,0},{6,6,0,0},{0,0,0,0} },
	{ {0,0,0,0},{0,7,0,0},{7,7,7,0},{0,0,0,0} },
	};

public:
	void StageInit(void); // ステージの初期化
	void DrawStage(void); // ステージ描画
	void CreateBlock(void); //ブロック生成とNEXTブロックの移動
	void ControlBlock(void); // ブロックの座標処理
	int CheckOverlap(int x2, int y2);	//　ブロックの移動可能チェック処理
	void TurnBlock(void);	//ブロックの回転処理
	void LockBlock(int x2, int y2);	//着地したブロックを固定済みブロックに加える
	void CheckLines(void);		//　ブロックが横一列の時の処理
	void ChangeBlock(void);		//　ブロックの交換（ストック処理）

	SixBallPuzzle();

	~SixBallPuzzle();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;

};

