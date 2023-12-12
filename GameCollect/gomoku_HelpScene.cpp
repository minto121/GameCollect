#include "gomoku_HelpScene.h"

gomoku_HelpScene::gomoku_HelpScene()
{
	gomokuHelp_BackImg1 = LoadGraph("../images/Gomoku/BackGround_Help.png");
	gomokuHelp_BackImg2 = LoadGraph("../images/Gomoku/BackGround_Help2.png");
	gomoku_HelpSE1 = LoadSoundMem("sound/SE/gomoku_scroll.wav");
	gomokuHelp_MenuNumber = 0;
	gomokuHelp_SelectWaitTIme = 60;
	g_KeyFlg = 0;
	g_NowKey = 0;
	g_OldKey = 0;
	gomokuHelp_ScrollWaitTIme = 0;
}

gomoku_HelpScene::~gomoku_HelpScene()
{
}

AbstractScene* gomoku_HelpScene::Update()
{
	g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;

	ChangeVolumeSoundMem(75, gomoku_HelpSE1);

	if (gomokuHelp_MenuNumber != 2) {
		gomokuHelp_ScrollWaitTIme++;
	}

	if (g_KeyFlg & PAD_INPUT_RIGHT && gomokuHelp_MenuNumber == 0 && gomokuHelp_ScrollWaitTIme > 15) {
		PlaySoundMem(gomoku_HelpSE1, DX_PLAYTYPE_BACK);
		gomokuHelp_ScrollWaitTIme = 0;
		gomokuHelp_MenuNumber = 1;
	}
	if (g_KeyFlg & PAD_INPUT_LEFT && gomokuHelp_MenuNumber == 1 && gomokuHelp_ScrollWaitTIme > 15) {
		PlaySoundMem(gomoku_HelpSE1, DX_PLAYTYPE_BACK);
		gomokuHelp_ScrollWaitTIme = 0;
		gomokuHelp_MenuNumber = 0;
	}
	if (g_KeyFlg & PAD_INPUT_8) {
		return new gomokuTitle;
	}
	return this;
}

void gomoku_HelpScene::Draw() const
{
	if (gomokuHelp_MenuNumber == 0) {
		DrawGraph(0, 0, gomokuHelp_BackImg1, FALSE);
	}
	if (gomokuHelp_MenuNumber == 1) {
		DrawGraph(0, 0, gomokuHelp_BackImg2, FALSE);
	}
	SetFontSize(24);
	DrawFormatString(10, 10, 0xffffff, "Startボタンでタイトル画面に戻る");
	SetFontSize(64);
	DrawFormatString(575, 620, 0xffffff, "1");
	DrawFormatString(650, 620, 0xffffff, "|");
	DrawFormatString(725, 620, 0xffffff, "2");
	DrawBox(540 + (gomokuHelp_MenuNumber * 150), 595, 640 + (gomokuHelp_MenuNumber * 150), 695, 0xff0000, FALSE);
}
