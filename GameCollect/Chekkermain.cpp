#include "Chekkermain.h"
#include "DxLib.h"
#include "PadInput.h"

Chekkermain::Chekkermain()
{
	Boardimg = LoadGraph("../images/Checkers/Chekkerboard.png");
	Pieceimg = 0;
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
	DrawGraph(500, 0, Boardimg, TRUE);
}
