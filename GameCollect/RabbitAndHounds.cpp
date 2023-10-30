#include"RabbitAndHounds.h"
#include "DxLib.h"
#include "PadInput.h"

static int MenuNumber = 0;
int Cursor_X = 0;

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
	// �`�悷�镶����̃T�C�Y��ݒ�
	SetFontSize(50);
	DrawString(300, 350, "�E�T�M", 0xffffff);
	DrawString(800, 350, "��", 0xffffff);

	Cursor_X = MenuNumber * 60;
	DrawTriangle(510, 370 + Cursor_X, 540, 390 + Cursor_X, 510, 410 + Cursor_X, GetColor(255, 0, 0), TRUE);
}
