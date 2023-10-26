#include "SixBollPuzzle.h"
#include "DxLib.h"
#include "PadInput.h"

SixBollPuzzle::SixBollPuzzle()
{
	//éläpÇÃògâÊëúì«çû
	Back_Ground_img = LoadGraph("../images/SixBallPuzzle/square.png");
	//
	Ball_img = LoadGraph("../images/SixBallPuzzle/boll.png");

	//if (LoadDivGraph("images/boll.png", 3, 3, 3, 160, 200, Ball_img) == -1);

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
	DrawGraph(0, 0, Ball_img, TRUE);
}
