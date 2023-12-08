#pragma once
#include "AbstractScene.h"
#include"DxLib.h"
#include"gomokuScene.h"
#include"gomoku_HelpScene.h"
class gomokuTitle : public AbstractScene
{
private:
	int gomokuTitle_Back;
	int gomokuTitle_Img;
	int gomokuMenuY;
	int gomokuTitle_MenuNumber;
	int g_OldKey;
	int g_NowKey;
	int g_KeyFlg;
	int gomoku_transitionTime;
	int gomoku_inputWaitTime;
public:
	gomokuTitle();
	~gomokuTitle();
	AbstractScene* Update() override;
	void Draw() const override;
};

