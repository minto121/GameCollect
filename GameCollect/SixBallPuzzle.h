#pragma once
#include "AbstractScene.h"

class SixBallPuzzle:
	public AbstractScene
{

private:
	int Ball_img[4];		//ボール
	int Back_Ground_img;	//背景画像
	int FallingX;			//落下するブロックのX座標（固定位置）
	int FallingY = 100;		//落下するブロックのY座標（初期位置）
	int randomBallIndex;
	/*int BallX;
	int BallY;*/

public:
	SixBallPuzzle();

	~SixBallPuzzle();

	//描画以外の更新を実行
	AbstractScene* Update() override;

	//描画に関することを実装
	void Draw() const override;

};

