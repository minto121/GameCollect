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
	cardimg = LoadDivGraph("../images/Takoyaki/PlayingCards.png", 56, 14, 4, 128, 256, Cards_img);  // カード画像読み込
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

bool isPlayer1Trun = true;
AbstractScene* Takoyaki::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		if (isPlayer1Turn) {
			int drawnCard = GetRand(13); // 0〜9のランダムな値を取得
			if (!cardFlipped[0][drawnCard]) { // カードがまだ捲られていない場合のみ処理を行う
				cardFlipped[0][drawnCard] = true; // カードを裏返す
				handCard[0][drawnCard] = GetRand(13) + 1;

				// 絵札（10～13）が出た場合、相手のターンに切り替える
				if (handCard[0][drawnCard] >= 10 && handCard[0][drawnCard] <= 13) {
					isPlayer1Turn = false; // プレイヤー1のターンを終了
				}
			}
		}
		else {
			int drawnCard = GetRand(13); // 0〜9のランダムな値を取得
			if (!cardFlipped[1][drawnCard]) { // カードがまだ捲られていない場合のみ処理を行う
				cardFlipped[1][drawnCard] = true; // カードを裏返す
				handCard[1][drawnCard] = GetRand(13) + 1;

				// 絵札（10～13）が出た場合、プレイヤー1のターンに切り替える
				if (handCard[1][drawnCard] >= 10 && handCard[1][drawnCard] <= 13) {
					isPlayer1Turn = true; // プレイヤー1のターンに切り替える
				}
			}
		}
	}


	// 手札の描画
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
	
	ScreenFlip();

}