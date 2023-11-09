#include "DxLib.h"
#include "takoyaki.h"
//#include "GameMain.h"
#include "PadInput.h"
#include "GameSelect.h"


Takoyaki::Takoyaki()
{
	Select = 0;
	Cards_img[56];
	cardimg = LoadDivGraph("../images/Takoyaki/PlayingCards.png",56,14,4,128,256,Cards_img);//カード画像読み込み
	CursolImg = LoadGraph("../images/Takoyaki/cursor.png");//カーソル画像読み込み
	select_X = 100;
	BackCard_Img = LoadGraph("../image/Takoyaki/card_back.png");
}

Takoyaki::~Takoyaki() {

}

AbstractScene* Takoyaki::Update()
{

	/*if (PAD_INPUT::OnPressed(XINPUT_BUTTON_DPAD_LEFT))
	{
		Select--;
		select_X -= 5;
	}

	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_DPAD_RIGHT)) {
		Select++;
		select_X += 5;
	}*/
	//十字キー↑入力
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		Select--;
		select_X -= 120;
	}
	//十字キー↓入力
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		Select++;
		select_X += 120;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		if (select_X == 100) {
			cardFlipped = true; // 特定の位置でAボタンを押した場合、カードを裏返す
			ClearDrawScreen(); // 画面をクリア
		}
	}
	return this;
}

void Takoyaki::Draw()const
{

	//タイトルの描画
	//DrawGraph(0, 0, TitleImg, FALSE);
	DrawString(350, 50, "main", 0xffffff, TRUE);

	//カード画像描画
	if (cardFlipped) {
		DrawGraph(70, 50, Cards_img[1], TRUE);
	}
	{
		
		if (cardFlipped) {
			DrawGraph(70, 50, Cards_img[0], TRUE);
		}
		else {
			DrawGraph(70, 50, BackCard_Img, TRUE); // カードが裏返っていない場合は裏面を描画
		}
		
	}
	DrawGraph(70, 50, Cards_img[0], TRUE);
	DrawGraph(190, 50, Cards_img[2], TRUE);
	DrawGraph(190, 50, Cards_img[3], TRUE);
	DrawGraph(190, 50, Cards_img[4], TRUE);
	DrawGraph(190, 50, Cards_img[5], TRUE);


	//カーソルの描画
	DrawGraph(select_X, 250, CursolImg, TRUE);


	//DrawGraph(650, select_y, CursorImg, TRUE);
}






