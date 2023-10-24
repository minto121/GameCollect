#include "gomokuScene.h"
#include"DxLib.h"
#include <stdio.h>

gomokuScene::gomokuScene()
{
	TitleImg = LoadGraph("../images/Gomoku/gomoku.png");
	wTopImg = LoadGraph("../images/Gomoku/BK.png");
	bTopImg = LoadGraph("../images/Gomoku/WK.png");
}

gomokuScene::~gomokuScene()
{}

AbstractScene* gomokuScene::Update()
{
	return this;
}

void gomokuScene::Draw() const
{
	DrawGraph(180, 0, TitleImg, TRUE);
	for (int y = 0; y < 13; y++)
		for (int x = 0; x < 6; x++) {
			DrawGraph(270 + (114 * x) + x * 0.8 , -25 + (56 * y) + y * 0.8 , bTopImg, TRUE);
			DrawGraph(326 + (114 * x) + x * 0.8 , -25 + (56 * y) + y * 0.8, wTopImg, TRUE);
		}
	DrawBox(345, 45, 405, 105, 0xffff00 , FALSE);
	
}
// if(x % 2 == 0 && y % 2 == 0)