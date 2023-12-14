#pragma once
#include "AbstractScene.h"
#include"DxLib.h"
#include"gomoku_TitleScene.h"
class gomoku_HelpScene : public AbstractScene
{
private:
	int gomokuHelp_BackImg1; // ヘルプ画面の背景画像1
	int gomokuHelp_BackImg2; // ヘルプ画面の背景画像2
	int gomokuHelp_MenuNumber; // ヘルプ画面のページ番号
	int gomokuHelp_SelectWaitTIme; // ヘルプ画面を選択した時のクールタイム
	int g_OldKey;
	int g_NowKey;
	int g_KeyFlg;
	int gomoku_HelpSE1; // ヘルプ画面で画面を変えるときに流す
	int gomoku_HelpSE2; // ヘルプ画面を閉じるときに流す
	int gomokuHelp_ScrollWaitTIme; // ヘルプ画面のページをスクロールした時のクールタイム
public:
	gomoku_HelpScene();
	~gomoku_HelpScene();
	AbstractScene* Update() override;
	void Draw() const override;
};

