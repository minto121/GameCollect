#include "Chekkermain.h"
#include "DxLib.h"
#include "PadInput.h"

Chekkermain::Chekkermain()
{
	Boardimg = LoadGraph("../images/Checkers/banmen.png");
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
	DrawGraph(400, 0, Boardimg, TRUE);
}
