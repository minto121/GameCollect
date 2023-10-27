#include "SixBollPuzzle.h"
#include "DxLib.h"
#include "PadInput.h"

SixBollPuzzle::SixBollPuzzle()
{
	//éläpÇÃògâÊëúì«çû
	//Back_Ground_img = LoadGraph("../images/SixBallPuzzle/square.png");
	
	//Ball_img = LoadGraph("../images/SixBallPuzzle/ball.png");

	LoadDivGraph("../images/SixBallPuzzle/ball.png", 5, 1, 5, 70, 12, Ball_img);

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
	DrawGraph(50, 80, Ball_img[1], FALSE);
}
