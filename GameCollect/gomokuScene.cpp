#include "gomokuScene.h"
#include"DxLib.h"

gomokuScene::gomokuScene()
{
	TitleImg = LoadGraph("../images/Gomoku/gomoku.png");
	TopImg = LoadGraph("../images/Gomoku/BK.png");
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
	DrawGraph(360, 20, TopImg, TRUE);
}
