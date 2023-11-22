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
	

public:
	SixBallPuzzle();

	~SixBallPuzzle();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;

};

