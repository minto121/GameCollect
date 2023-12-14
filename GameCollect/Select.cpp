#include"DxLib.h"
#include"PadInput.h"
#include"Title.h"
#include"Select.h"

GameSelect::GameSelect()
{
	int a = 8;
}

GameSelect::~GameSelect()
{
}

AbstractScene* GameSelect::Update()
{
}

void GameSelect::Draw()const
{
	DrawFormatString(0, 0, GetColor(255,0,0), "Select");
}