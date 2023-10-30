#include "SixBollPuzzle.h"
#include "DxLib.h"
#include "PadInput.h"

SixBollPuzzle::SixBollPuzzle()
{
	//éläpÇÃògâÊëúì«çû
	//Back_Ground_img = LoadGraph("../images/SixBallPuzzle/square.png");
	
	//Ball_img = LoadGraph("../images/SixBallPuzzle/ball.png");

	LoadDivGraph("../images/SixBallPuzzle/ball.png", 4, 1, 5, 64, 64, Ball_img); //320px*64px

}

SixBollPuzzle::~SixBollPuzzle()
{

}

AbstractScene* SixBollPuzzle::Update()
{
	return this;
}

void SixBollPuzzle::Draw() const
{
	//DrawGraph(0, 0, Back_Ground_img, FALSE);
	//DrawGraph(0, 0, Ball_img, FALSE);
	DrawGraph(50, 80, Ball_img[4], FALSE);
}
