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
	DrawString(10, 20, "�E�T�M�Ɨ�", 0xffffff);
}

