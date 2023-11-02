#include "Chekkermain.h"
#include "DxLib.h"
#include "PadInput.h"

Chekkermain::Chekkermain()
{
	Boardimg = LoadGraph("../images/Checkers/banmen.png");
	Pieceimg = LoadGraph("../images/Checkers/WK.png");
	back = LoadGraph("../images/Checkers/back.png");
}

Chekkermain::~Chekkermain()
{
}

AbstractScene* Chekkermain::Update()
{
	return this;
}

void Chekkermain::Draw() const
{
	/*DrawGraph(0, 0, back, FALSE);
	DrawGraph(180, 0, Boardimg, TRUE);
	DrawRotaGraph(480, 110, 2, 0, Pieceimg, TRUE);
	DrawRotaGraph(480, 110,2,0, Pieceimg, TRUE);*/
}

