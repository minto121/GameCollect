#include "DxLib.h"
#include "takoyaki.h"
//#include "GameMain.h"
#include "PadInput.h"
#include "GameSelect.h"


Takoyaki::Takoyaki()
{
	Select = 0;
	Cards_img[56];

	// カード画像の初期化
	for (int i = 0; i < 56; ++i) {
		Cards_img[i] = -1;  // デフォルト値で初期化
	}

	// カード画像の初期化
	cardimg = LoadDivGraph("../images/Takoyaki/PlayingCards.png", 56, 14, 4, 128, 256, Cards_img);  // カード画像読み込み
	CursolImg = LoadGraph("../images/Takoyaki/cursor.png");										//カーソル画像読み込み
	select_X = 100;
	select_Y = 120;
	BackCard_Img = Cards_img[0];

	AButtonPressed = false;
	//手札の初期化
	for (int i = 0; i < 10; ++i) {
		handCard[0][i] = 0;
		handCard[1][i] = 0;
		cardFlipped[0][i] = false;
		cardFlipped[1][i] = false;
	}


	//最初に手札を描画
	Draw();
	ScreenFlip();
}

Takoyaki::~Takoyaki() {

}

AbstractScene* Takoyaki::Update()
{

	//カーソル　左
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		Select--;
		select_X -= 120;
	}
	//カーソル右
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		Select++;
		select_X += 120;
	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		if (select_X == select_X) {
			AButtonPressed = true; // Aボタンが押されたことを記録
			if (select_X >= 70 && select_X < 1180) { // カードが描画されている範囲内か確認
				if (Select >= 0 && Select < 10) {
					if (!cardFlipped[0][Select]) {
						handCard[0][Select] = GetRand(8) + 1; // 1〜9のランダムな値をセット
						cardFlipped[0][Select] = true; // カードを裏返す
					}
				}
			}
		}
	}
	else {
		AButtonPressed = false; // Aボタンが押されていないことを記録
	}

	//手札の描画
	Draw();
	ScreenFlip();
	return this;
}

void Takoyaki::Draw()const
{
	ClearDrawScreen();

	// カード画像描画
	for (int i = 0; i < 10; ++i) {
		int cardIndex = handCard[0][i];
		if (cardIndex >= 0 && cardIndex < 56) {
			DrawGraph(70 + i * 120, 50, cardFlipped[0][i] ? Cards_img[cardIndex] : BackCard_Img, TRUE);
		}
		else {
			// カードが無効な場合、バックカードを描画
			DrawGraph(70 + i * 120, 50, BackCard_Img, TRUE);
		}
	}

	// 2P側の手札のカード画像描画
		for (int i = 0; i < 10; ++i) {
			int cardIndex = handCard[1][i];
			if (cardIndex >= 0 && cardIndex < 56) {
				DrawGraph(70 + i * 120, 300, cardFlipped[1][i] ? Cards_img[cardIndex] : BackCard_Img, TRUE);
			}
			else {
				DrawGraph(70 + i * 120, 300, BackCard_Img, TRUE); // カードが無効な場合、バックカードを描画
			}
		}
	//カーソルの描画
	DrawGraph(select_X, 250, CursolImg, TRUE);
	ScreenFlip();

	//DrawGraph(650, select_y, CursorImg, TRUE);
}