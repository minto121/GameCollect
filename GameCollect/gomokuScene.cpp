#include "gomokuScene.h"
#include"DxLib.h"

gomokuScene::gomokuScene()
{
	TitleImg = LoadGraph("../images/Gomoku/gomoku.png");
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
}
