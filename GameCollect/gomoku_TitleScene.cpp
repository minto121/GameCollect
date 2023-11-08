#include "gomoku_TitleScene.h"

gomokuTitle::gomokuTitle()
{
	gomokuTitle_Back = LoadGraph("../images/Gomoku/BackGround02.png");
}

gomokuTitle::~gomokuTitle()
{
}

AbstractScene* gomokuTitle::Update()
{
    g_OldKey = g_NowKey;
    g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    g_KeyFlg = g_NowKey & ~g_OldKey;

    gomokuMenuY = gomokuMenuNumber * 100;
    
    if (g_KeyFlg & PAD_INPUT_UP && gomokuMenuY > 0 || g_KeyFlg & PAD_INPUT_DOWN && gomokuMenuY > 0) {
        gomokuMenuNumber = 0;
    }
    if (g_KeyFlg & PAD_INPUT_UP && gomokuMenuY < 1 || g_KeyFlg & PAD_INPUT_DOWN && gomokuMenuY < 1) {
       gomokuMenuNumber = 1;
    }
    if (g_KeyFlg & PAD_INPUT_1 && gomokuMenuNumber == 0) {
        return new gomokuScene;
    }
	return this;
}

void gomokuTitle::Draw() const
{
    DrawGraph(0, 0, gomokuTitle_Back, FALSE);
    SetFontSize(100);
    DrawFormatString(900, 450, 0xffffff, "START");
    DrawFormatString(900, 550, 0xffffff, "HELP");
    DrawFormatString(0, 0, 0xffffff, "ŒÜ–Ú•À‚×");
    DrawTriangle(850, 500 + gomokuMenuY, 800, 450 + gomokuMenuY, 800, 550 + gomokuMenuY, 0xffffff, TRUE);
}
