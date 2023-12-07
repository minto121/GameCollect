#pragma once
#include "AbstractScene.h"
#include"DxLib.h"
#include"gomoku_TitleScene.h"
class gomoku_HelpScene : public AbstractScene
{
private:
	int gomoku_PadImg;
	int gomokuHelp_BackImg;
	int g_OldKey;
	int g_NowKey;
	int g_KeyFlg;
public:
	gomoku_HelpScene();
	~gomoku_HelpScene();
	AbstractScene* Update() override;
	void Draw() const override;
};

