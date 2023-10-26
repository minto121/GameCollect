#include"RabbitAndHounds.h"
#include "DxLib.h"
#include "PadInput.h"

RabbitAndHounds::RabbitAndHounds()
{

}

RabbitAndHounds::~RabbitAndHounds()
{
}

AbstractScene* RabbitAndHounds::Update()
{
	return this;
}

void RabbitAndHounds::Draw() const
{
	DrawRotaGraph(480, 110, 2, 0, Pieceimg, TRUE);
}

