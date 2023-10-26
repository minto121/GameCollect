#include "Checkermain.h"
#include "DxLib.h"
#include "PadInput.h"

Checkermain::Checkermain() {

	Boardimg = LoadGraph("../images/Checkers/banmen.png");
	PieceB = LoadGraph("../images/Checkers/WK.png");
	PiceW = LoadGraph("../images/Checkers/BK.png");
	Checkerback = LoadGraph("../images/Checkers/back.png");
}

Checkermain::~Checkermain()
{
}

AbstractScene* Checkermain::Update()
{
	return this;
}

void Checkermain::Draw() const
{
	
	DrawGraph(0, 0, Checkerback, FALSE);
	DrawGraph(180, 0, Boardimg, TRUE);
	DrawRotaGraph(480, 110,2,0, PieceB, TRUE);

	
	
	
}

