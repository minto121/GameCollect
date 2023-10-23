#include "Reversi.h"
#include"DxLib.h"

Reversi::Reversi()
{
	R_Img = LoadGraph("images/Reversi/banmen.png");
}

Reversi::~Reversi()
{
}

AbstractScene* Reversi::Update()
{
	return this;
}

void Reversi::Draw() const
{
	DrawGraph(0, 0, R_Img, TRUE);
}
