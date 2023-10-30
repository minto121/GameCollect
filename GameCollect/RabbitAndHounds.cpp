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
	DrawString(10, 20, "ウサギと猟犬", 0xffffff);
	// 描画する文字列のサイズを設定
	SetFontSize(50);
	DrawString(300, 350, "ウサギ", 0xffffff);
	DrawString(800, 350, "猟犬", 0xffffff);

	Cursor_X = MenuNumber * 60;
	DrawTriangle(260, 360 + Cursor_X, 290, 380 + Cursor_X, 260, 400 + Cursor_X, GetColor(255, 0, 0), TRUE);
}
