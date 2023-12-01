#include "SixBallPuzzle.h"
#include "DxLib.h"
#include "PadInput.h"
#include <cstdlib>  //ランダム関数用
#include <ctime>    //srandの初期化に使用


SixBallPuzzle::SixBallPuzzle()
{
	//背景画像読込
	Back_Ground = LoadGraph("../images/SixBallPuzzle/square.png");
	
	//ボールの分割読込
	LoadDivGraph("../images/SixBallPuzzle/ball.png", 5, 5, 1, 64, 64, Ball_img);	//画像の全体サイズ：320px*64px

	// ボールの初期位置と速度を設定
	for (int i = 0; i < MaxBalls; i++)
	{
		ballX[i] = rand() % (ScreenWidth - 64);  // X座標
		ballY[i] = - 64 * i;  // ボールのY座標をランダムに設定
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

	// y座標を自動的に更新してボールを描画
	for (int i = 0; i < MaxBalls; i++)
	{
		// 画面外に出たら再利用
		if (ballY[i] > ScreenHeight)
		{
			ballY[i] = -64;  // 画面上部から再利用
			ballX[i] = rand() % (ScreenWidth - 64);  // ボールのX座標をランダムに設定
			ballSpeed[i] = 1;  // 落下速度
			ballActive[i] = true;  // ボールがアクティブかどうか
		}
	}
	// y座標を自動的に更新してボールを描画
	for (int i = 0; i < MaxBalls; i++)
	{
		if (ballActive[i])
		{
			ballY[i] += ballSpeed[i];  // ボールを落下させる

			// 画面下部で積み上げ
			if (ballY[i] > ScreenHeight - 64)
			{
				ballY[i] = ScreenHeight - 64;  // 画面下部で停止
				ballSpeed[i] = 0;  // 落下速度を停止

				for (int j = 0; j < MaxBalls; j++)
				{
					// 現在のボールが他のボールと重ならないようにする
					if (i != j && ballActive[j] && ballY[j] < ballY[i] + 64 && ballY[j] + 64 > ballY[i])
					{
						ballY[i] = ballY[j];  // 積み上げる位置を調整
						break;
					}
				}
			}
		}
	}

	return this;
}

void SixBallPuzzle::Draw() const
{

	//選択したランダムなボールを描画
	//DrawGraph(100, FallingY, Ball_img[randomBallIndex], TRUE);

	//ボールの分割描画
	//DrawGraph(100, FallingY, Ball_img[1],FALSE);

	//背景画像の描画
	//DrawGraph(10, 10, Back_Ground, TRUE);

	//ボールの分割描画
	for (int i = 0; i < MaxBalls; i++)
	{
		if (ballActive[i])
		{
			DrawGraph(ballX[i], ballY[i], Ball_img[i], TRUE);
		}
	}
}

void SixBallPuzzle::StageInit(void)
{
}
