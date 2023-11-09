#include "SixBallPuzzle.h"
#include "DxLib.h"
#include "PadInput.h"
#include <cstdlib>  //ランダム関数用
#include <ctime>    //srandの初期化に使用


SixBallPuzzle::SixBallPuzzle()
{
	//背景画像読込
	Back_Ground_img = LoadGraph("../images/SixBallPuzzle/BackGroundBall_1.png");
	
	//ボールの分割読込
	LoadDivGraph("../images/SixBallPuzzle/ball.png", 5, 5, 1, 64, 64, Ball_img);	//画像の全体サイズ：320px*64px

	// ボールの初期位置と速度を設定
	for (int i = 0; i < MaxBalls; i++)
	{
		ballX[i] = 100;  // X座標
		ballY[i] = i + 80;  // 初期Y座標を80ピクセルずつずらす
		ballSpeed[i] = 2;  // 落下速度
		ballActive[i] = true;  // ボールがアクティブかどうか
	}
	//乱数生成器を初期化
	//srand(static_cast<unsigned int>(time(0)));
}

SixBallPuzzle::~SixBallPuzzle()
{

}

AbstractScene* SixBallPuzzle::Update()
{
	// ランダムなボールのインデックスを生成
	//randomBallIndex = rand() % 5;  // 0から4の範囲でランダムにボールを選択

	// y座標を自動的に更新して画像を描画
	// 画像の座標を画面内に制限する（画面下端でリセットする）
	if (FallingY < 600)
	{
		FallingY += 2;  //ボールの落下速度
	}

	// y座標を自動的に更新してボールを描画
	for (int i = 0; i < MaxBalls; i++)
	{
		if (ballActive[i])
		{
			ballY[i] += ballSpeed[i];  // ボールを落下させる

			// 画面外に出たら再利用
			if (ballY[i] > ScreenHeight)
			{
				ballY[i] = -64;  // 画面上部から再利用
				ballX[i] = rand() % (ScreenWidth - 64);  // ボールのX座標をランダムに設定
			}
		}
	}
	return this;
}

void SixBallPuzzle::Draw() const
{

	//選択したランダムなボールを描画
	//DrawGraph(100, FallingY, Ball_img[randomBallIndex], TRUE);

	//背景画像の描画
	//DrawGraph(0, 0, Back_Ground_img, FALSE);

	//ボールの分割描画
	DrawGraph(100, FallingY, Ball_img[1],FALSE);

	//ボールの分割描画
	for (int i = 0; i < MaxBalls; i++) 
	{
		if (ballActive[i]) 
		{
			DrawGraph(ballX[i], ballY[i], Ball_img[i], TRUE);
		}
	}
}
