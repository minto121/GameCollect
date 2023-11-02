#include "DxLib.h"
#include "Title.h"
#include "Porker.h"
#include "PadInput.h"
#include "GameSelect.h"

//タイトルメニュー
enum class TITLE_MENU
{
	GAME_START = 0,
	GAME_RANKING,
	GAME_HELP,
	GAME_END
};

Title::Title()
{

	//フォントの追加
	MenuFont = CreateFontToHandle("HG創英角ﾎﾟｯﾌﾟ体", 64, 8, DX_FONTTYPE_ANTIALIASING);

	////タイトル画像の読み込み
	//if ((TitleImg = LoadGraph("Resource/Images/mori.png")) == -1)
	//{
	//	throw "Resource/Images/mori.png";
	//}
	//// カーソル画像の読み込み
	//if ((CursorImg = LoadGraph("Resource/Images/Apple_Red.png")) == -1)
	//{
	//	throw "Resource/Images/apple.png";
	//}
	////BGMの読み込み
	//if ((TitleBGM = LoadSoundMem("Resource/sounds/BGM/yonhonnorecorder.wav")) == -1)
	//{
	//	throw "Resource/sounds/BGM/yonhonnorecorder.wav";
	//}
	////BGMの音量変更
	//ChangeVolumeSoundMem(140, TitleBGM);

	////SEの読み込み
	//if ((MenuSE = LoadSoundMem("Resource/sounds/SE/select01.wav")) == -1) //選択SE
	//{
	//	throw "Resource/sounds/SE/select01.wav";
	//}
	////SEの音量変更
	//ChangeVolumeSoundMem(110, MenuSE);

	////BGMの再生
	//if (CheckSoundMem(TitleBGM) == 0)
	//{
	//	PlaySoundMem(TitleBGM, DX_PLAYTYPE_LOOP);
	//}
}

Title::~Title()
{
	
}

AbstractScene* Title::Update()
{

	/*if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))*/
	if(CheckHitKey(KEY_INPUT_P))
	{
		//switch (static_cast<TITLE_MENU>(Select))
		//{
		//	//ゲーム画面へ
		//case TITLE_MENU::GAME_START:
		//	return new GameSelect();
		//	break;
		//default:
		//	break;
		//}
		return new Porker();
	}

	


	return this;
}

void Title::Draw()const
{
	//タイトルの描画
	DrawGraph(0, 0, TitleImg, FALSE);
	DrawStringToHandle(150, 100, "ゲーム大全", 0xffffff, MenuFont);

	//メニューの描画
	DrawStringToHandle(70, 240, "すたーと", 0xffffff, MenuFont);
	DrawStringToHandle(70, 320, "らんきんぐ", 0xffffff, MenuFont);
	DrawStringToHandle(70, 400, "へるぷ", 0xffffff, MenuFont);
	DrawStringToHandle(70, 480, "えんど", 0xffffff, MenuFont);

	//カーソルの描画
	int select_y = 230 + Select * 80;
	DrawGraph(650, select_y, CursorImg, TRUE);
}