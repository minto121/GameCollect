#include "gomoku_HelpScene.h"

gomoku_HelpScene::gomoku_HelpScene()
{
	gomoku_PadImg = LoadGraph("../images/Gomoku/gamepad.png");
	gomokuHelp_BackImg = LoadGraph("../images/Gomoku/BackGround02.png");
	g_KeyFlg = 0;
	g_NowKey = 0;
	g_OldKey = 0;
}

gomoku_HelpScene::~gomoku_HelpScene()
{
}

AbstractScene* gomoku_HelpScene::Update()
{
	g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;
	if (g_KeyFlg & PAD_INPUT_8) {
		return new gomokuTitle;
	}
	return this;
}

void gomoku_HelpScene::Draw() const
{
	DrawGraph(0, 0, gomokuHelp_BackImg, FALSE);
	DrawGraph(380, 200, gomoku_PadImg, FALSE);
	DrawFormatString(10, 10, 0xffffff, "Startボタンでタイトル画面に戻る");
}
