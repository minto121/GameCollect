#include "LastCard.h"
#include "DxLib.h"
#include "PadInput.h"

LastCard::LastCard()
{
	Card;

	CardImg;

	LoadDivGraph("images/LastCard/LastCard.png", 65, 13, 5, 128, 256, CardImg);
}

LastCard::~LastCard()
{
}

AbstractScene* LastCard::Update()
{
	if (CheckHitKey(KEY_INPUT_O))
	{
		return nullptr;
	}
	return this;
}

void LastCard::Draw() const
{
	DrawGraph(35, 49, CardImg[2], FALSE);
}
