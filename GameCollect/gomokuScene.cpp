#include "gomokuScene.h"
#include"DxLib.h"

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
			DrawGraph(260 + (115 * x) + 2 * x, -30 + (55 * y) + y , bTopImg, TRUE);
			DrawGraph(320 + (115 * x) + 2 * x, -30 + (55 * y) + y, wTopImg, TRUE);
		}
	
}
