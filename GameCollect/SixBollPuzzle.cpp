#include "SixBollPuzzle.h"
#include "DxLib.h"
#include "PadInput.h"

SixBollPuzzle::SixBollPuzzle()
{
	Back_Ground_img = LoadGraph("../images/SixBallPazzle/BackGroundBoll_1.png");
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
}
