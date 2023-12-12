#pragma once
#include "AbstractScene.h"
#include"DxLib.h"
#include"gomoku_TitleScene.h"
class gomoku_HelpScene : public AbstractScene
{
private:
	int gomokuHelp_BackImg1;
	int gomokuHelp_BackImg2;
	int gomokuHelp_MenuNumber;
	int gomokuHelp_SelectWaitTIme;
	int g_OldKey;
	int g_NowKey;
	int g_KeyFlg;
	int gomoku_HelpSE1; // ヘルプ画面で画面を変えるときに流す
	int gomoku_HelpSE2; // ヘルプ画面を閉じるときに流す
	int gomokuHelp_ScrollWaitTIme;
public:
	gomoku_HelpScene();
	~gomoku_HelpScene();
	AbstractScene* Update() override;
	void Draw() const override;
};

