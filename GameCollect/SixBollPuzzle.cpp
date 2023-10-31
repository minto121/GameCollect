#include "SixBollPuzzle.h"
#include "DxLib.h"
#include "PadInput.h"

SixBollPuzzle::SixBollPuzzle()
{
	//背景画像読込
	Back_Ground_img = LoadGraph("../images/SixBallPuzzle/BackGround01.png");
	
	//Ball_img = LoadGraph("../images/SixBallPuzzle/ball.png");

	//ボールの分割読込
	LoadDivGraph("../images/SixBallPuzzle/ball.png", 5, 5, 1, 64, 64, Ball_img);	//画像の全体サイズ：320px*64px

}

SixBollPuzzle::~SixBollPuzzle()
{

}

AbstractScene* SixBollPuzzle::Update()
{
	//分割した画像をランダムで読む込む
	/*for (int i = 0; i < 3; i++) {
		Ball_img[i] = LoadGraph(imagePaths[i]);
	}*/

	// y座標を自動的に更新して画像を描画
	// 画像の座標を画面内に制限する（画面下端でリセットする）
	if (FallingY < 600)
	{
		FallingY += 2;  //ボールの落下速度
	}

	return this;
}

void SixBollPuzzle::Draw() const{

	//背景画像の描画
	DrawGraph(0, 0, Back_Ground_img, FALSE);

	//ボールの分割描画
	DrawGraph(100, FallingY, Ball_img[1], TRUE);
	DrawGraph(136, FallingY, Ball_img[2], TRUE);
	DrawGraph(118, FallingY - 36, Ball_img[3], TRUE);
}
