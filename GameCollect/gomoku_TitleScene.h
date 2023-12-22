#pragma once
#include "AbstractScene.h"
#include"DxLib.h"
#include"gomokuScene.h"
#include"gomoku_HelpScene.h"
class gomokuTitle : public AbstractScene
{
private:
	int gomokuTitle_Back; // タイトル画面の背景画像
	int gomokuMenuY; // メニューカーソルのY座標
	int gomokuTitle_MenuNumber; // タイトル画面のメニューの番号(0:メイン 1:ヘルプ 2:バック)
	int g_OldKey;
	int g_NowKey;
	int g_KeyFlg;
	int gomoku_transitionTime; // 画面遷移のクールタイム
	int gomoku_inputWaitTime; // 入力した時のクールタイム
	int gomoku_TitleSE1; // モードセレクト時に流す
	int gomoku_TitleSE2; // モードを決定した時に流す
public:
	gomokuTitle();
	~gomokuTitle();
	AbstractScene* Update() override;
	void Draw() const override;
};

