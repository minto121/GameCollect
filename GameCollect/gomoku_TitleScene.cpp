#include "gomoku_TitleScene.h"
#include "GameSelect.h"

gomokuTitle::gomokuTitle()
{
	gomokuTitle_Back = LoadGraph("images/gomoku/BackGround02.png");
    gomoku_TitleSE1 = LoadSoundMem("sound/SE/gomoku_SelectSE.wav");
    gomoku_TitleSE2 = LoadSoundMem("sound/SE/gomoku_EnterSE.wav");
    gomokuTitle_MenuNumber = 0;
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

    ChangeVolumeSoundMem(100, gomoku_TitleSE1);
    ChangeVolumeSoundMem(100, gomoku_TitleSE2);

    gomokuMenuY = gomokuTitle_MenuNumber * 100;
    
    if (g_KeyFlg & PAD_INPUT_UP && gomokuTitle_MenuNumber == 1 && gomoku_inputWaitTime > 5|| g_KeyFlg & PAD_INPUT_DOWN && gomokuTitle_MenuNumber == 2 && gomoku_inputWaitTime > 5) {
        PlaySoundMem(gomoku_TitleSE1, DX_PLAYTYPE_BACK);
        gomoku_inputWaitTime = 0;
        gomokuTitle_MenuNumber = 0;
    }
    if (g_KeyFlg & PAD_INPUT_UP && gomokuTitle_MenuNumber == 2 && gomoku_inputWaitTime > 5 || g_KeyFlg & PAD_INPUT_DOWN && gomokuTitle_MenuNumber == 0 && gomoku_inputWaitTime > 5) {
        PlaySoundMem(gomoku_TitleSE1, DX_PLAYTYPE_BACK);
        gomoku_inputWaitTime = 0;
       gomokuTitle_MenuNumber = 1;
    }
    if (g_KeyFlg & PAD_INPUT_UP && gomokuTitle_MenuNumber == 0 && gomoku_inputWaitTime > 5 || g_KeyFlg & PAD_INPUT_DOWN && gomokuTitle_MenuNumber == 1 && gomoku_inputWaitTime > 5) {
        PlaySoundMem(gomoku_TitleSE1, DX_PLAYTYPE_BACK);
        gomoku_inputWaitTime = 0;
        gomokuTitle_MenuNumber = 2;
    }
    if (g_KeyFlg & PAD_INPUT_1 && gomokuTitle_MenuNumber == 0 && gomoku_transitionTime > 15) {
        PlaySoundMem(gomoku_TitleSE2, DX_PLAYTYPE_BACK);
        return new gomokuScene;
    }
    if (g_KeyFlg & PAD_INPUT_1 && gomokuTitle_MenuNumber == 1 && gomoku_transitionTime > 15) {
        PlaySoundMem(gomoku_TitleSE2, DX_PLAYTYPE_BACK);
        return new gomoku_HelpScene;
    }
    if (g_KeyFlg & PAD_INPUT_1 && gomokuTitle_MenuNumber == 2 && gomoku_transitionTime > 15) {
        PlaySoundMem(gomoku_TitleSE2, DX_PLAYTYPE_BACK);
        return new GameSelect;
    }
        return this;
}

void gomokuTitle::Draw() const
{
    DrawGraph(0, 0, gomokuTitle_Back, FALSE);
    SetFontSize(100);
    /*DrawFormatString(10, 10, 0xffffff, "%d", gomokuTitle_MenuNumber);*/
    DrawFormatString(900, 350, 0xffffff, "START");
    DrawFormatString(900, 450, 0xffffff, "HELP");
    DrawFormatString(900, 550, 0xffffff, "BACK");
    DrawFormatString(250, 100, 0xffffff, "ŒÜ–Ú•À‚×");
    DrawTriangle(850, 400 + gomokuMenuY, 800, 350 + gomokuMenuY, 800, 450 + gomokuMenuY, 0xffffff, TRUE);
}
