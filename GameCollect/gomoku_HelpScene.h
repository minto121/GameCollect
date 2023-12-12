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
	int gomoku_HelpSE1; // ƒwƒ‹ƒv‰æ–Ê‚Å‰æ–Ê‚ð•Ï‚¦‚é‚Æ‚«‚É—¬‚·
	int gomoku_HelpSE2; // ƒwƒ‹ƒv‰æ–Ê‚ð•Â‚¶‚é‚Æ‚«‚É—¬‚·
	int gomokuHelp_ScrollWaitTIme;
public:
	gomoku_HelpScene();
	~gomoku_HelpScene();
	AbstractScene* Update() override;
	void Draw() const override;
};

