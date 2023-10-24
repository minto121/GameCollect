#include "SixBollPuzzle.h"
#include "DxLib.h"
#include "PadInput.h"

SixBollPuzzle::SixBollPuzzle()
{
	Back_Ground_img = LoadGraph("../images/SixBallPuzzle/square.png");
	Back_Ground_img = LoadGraph("../images/SixBallPuzzle/ball.png");

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
	DrawGraph(0, 0, Back_Ground_img, FALSE);
	DrawGraph(0, 0, Ball_img, FALSE);

}
