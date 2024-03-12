#include "DxLib.h"
#include "Title.h"
#include "PadInput.h"
#include"GameSelect.h"
#include<iostream>
#define SCREEN_WIDTH 1280

Title::Title()
{

	//フォントの追加
	MenuFont = CreateFontToHandle("HG創英角ﾎﾟｯﾌﾟ体", 64, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 3);
	now_menu = static_cast<int>(TITLE_MENU::GAME_START);
	input_margin = 0;

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
	// 操作間隔時間
	const int max_input_margin = 15;
	// スティックの感度
	const int stick_sensitivity = 20000;

	if (input_margin < max_input_margin) {
		input_margin++;
	}
	else {
		// スティックのY座標を取得
		int stick_y = PAD_INPUT::GetLStick().ThumbY;

		if (std::abs(stick_y) > stick_sensitivity) {
			//playsoundmem
			// スティックが上に移動した場合
			if (stick_y > 0) {
				// メニュー選択肢を一つ前に移動
				now_menu = (now_menu - 1 + static_cast<int>(TITLE_MENU::TITLE_SIZE)) % static_cast<int>(TITLE_MENU::TITLE_SIZE);
			}
			// スティックが下に移動した場合
			else if (stick_y < 0) {
				// メニュー選択肢を一つ次に移動
				now_menu = (now_menu + 1) % static_cast<int>(TITLE_MENU::TITLE_SIZE);
			}
			input_margin = 0;
		}
	}
	if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true))
	{
		input_margin = 0;
		TITLE_MENU current_select = static_cast<TITLE_MENU>(now_menu);
		switch (current_select)
		{
		case TITLE_MENU::GAME_START:
			return new GameSelect();
			break;
		case TITLE_MENU::GAME_END:
			return nullptr;
			break;
		default:
			printfDx("未実装な機能です。\n");
			break;
		}
	}

	return this;
}

void Title::Draw()const
{
	//タイトルの描画
	/*DrawGraph(0, 0, TitleImg, FALSE);*/

	for (int i = 0; i < static_cast<int>(TITLE_MENU::TITLE_SIZE); i++)
	{
		// 文字列の最小Y座標
		const int base_y = 200;

		// 文字列のY座標間隔
		const int margin_y = 100;

		// 文字色
		int color = 0xFFFFFF;
		// 文字外枠色
		int border_color = 0x000000;

		// カーソルが合っている場合、文字色と文字外枠色を反転させる
		if (now_menu == i) {
			color = ~color;
			border_color = ~border_color;
		}
		DrawStringToHandle(SCREEN_WIDTH / 2 - 100, i * margin_y + base_y, menu_items[i], color, MenuFont, border_color);
	}
	DrawStringToHandle(150, 100, "ゲーム大全", 0xffffff, MenuFont);

	////カーソルの描画
	//int select_y = 230 + Select * 80;
	//DrawGraph(650, select_y, CursorImg, TRUE);
}