#include "gomoku_TitleScene.h"
#include "GameSelect.h"

gomokuTitle::gomokuTitle()
{
	gomokuTitle_Back = LoadGraph("../images/Gomoku/BackGround02.png");
    gomokuMenuNumber = 0;
    gomokuMenuY = 0;
    g_OldKey = 0;
    g_NowKey = 0;
    g_KeyFlg = 0;
    gomoku_transitionTime = 0;
    gomoku_inputWaitTime = 0;
}

gomokuTitle::~gomokuTitle()
{
}

AbstractScene* gomokuTitle::Update()
{
    g_OldKey = g_NowKey;
    g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    g_KeyFlg = g_NowKey & ~g_OldKey;

    gomoku_transitionTime++;
    gomoku_inputWaitTime++;

    gomokuMenuY = gomokuMenuNumber * 100;
    
    if (g_KeyFlg & PAD_INPUT_UP && gomokuMenuNumber == 1 && gomoku_inputWaitTime > 5|| g_KeyFlg & PAD_INPUT_DOWN && gomokuMenuNumber == 2 && gomoku_inputWaitTime > 5) {
        gomoku_inputWaitTime = 0;
        gomokuMenuNumber = 0;
    }
    if (g_KeyFlg & PAD_INPUT_UP && gomokuMenuNumber == 2 && gomoku_inputWaitTime > 5 || g_KeyFlg & PAD_INPUT_DOWN && gomokuMenuNumber == 0 && gomoku_inputWaitTime > 5) {
        gomoku_inputWaitTime = 0;
       gomokuMenuNumber = 1;
    }
    if (g_KeyFlg & PAD_INPUT_UP && gomokuMenuNumber == 0 && gomoku_inputWaitTime > 5 || g_KeyFlg & PAD_INPUT_DOWN && gomokuMenuNumber == 1 && gomoku_inputWaitTime > 5) {
        gomoku_inputWaitTime = 0;
        gomokuMenuNumber = 2;
    }
    if (g_KeyFlg & PAD_INPUT_1 && gomokuMenuNumber == 0 && gomoku_transitionTime > 15) {
        return new gomokuScene;
    }
    if (g_KeyFlg & PAD_INPUT_1 && gomokuMenuNumber == 2 && gomoku_transitionTime > 15) {
        return new GameSelect;
    }
        return this;
}

void gomokuTitle::Draw() const
{
    DrawGraph(0, 0, gomokuTitle_Back, FALSE);
    SetFontSize(100);
    /*DrawFormatString(10, 10, 0xffffff, "%d", gomokuMenuNumber);*/
    DrawFormatString(900, 350, 0xffffff, "START");
    DrawFormatString(900, 450, 0xffffff, "HELP");
    DrawFormatString(900, 550, 0xffffff, "BACK");
    DrawFormatString(0, 0, 0xffffff, "ŒÜ–Ú•À‚×");
    DrawTriangle(850, 400 + gomokuMenuY, 800, 350 + gomokuMenuY, 800, 450 + gomokuMenuY, 0xffffff, TRUE);
}
