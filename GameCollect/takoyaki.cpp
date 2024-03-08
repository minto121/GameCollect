#include "DxLib.h"
#include "takoyaki.h"
//#include "GameMain.h"
#include "PadInput.h"
#include "GameSelect.h"

#include <algorithm>
#include <random>


Takoyaki::Takoyaki()
{
	
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
	for (int i = 0; i < 9; ++i) {
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

bool isPlayer1Turn = true;

AbstractScene* Takoyaki::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) || CheckHitKey(KEY_INPUT_A)) {
		//DrawnCard();
	
		int drawnCard = GetRand(9); // 0〜9のランダムな値を取得
		if (!cardFlipped[isPlayer1Turn ? 0 : 1][drawnCard]) { // カードがまだ捲られていない場合のみ処理を行う
			cardFlipped[isPlayer1Turn ? 0 : 1][drawnCard] = true; // カードを裏返す
			handCard[isPlayer1Turn ? 0 : 1][drawnCard] = GetRand(13) + 1;

			// 絵札（10～13）が出た場合、相手のターンに切り替える
			if (handCard[isPlayer1Turn ? 0 : 1][drawnCard] >= 11 && handCard[isPlayer1Turn ? 0 : 1][drawnCard] <= 13) {
				isPlayer1Turn = !isPlayer1Turn; // ターンを切り替える
				printf("Player's turn ended\n");
			}

			// キーが押されたら少し待つ
			Sleep(1000); // ミリ秒単位で指定（0.5秒）
		}
	}

	// 手札の描画
	Draw();


	//プレイヤー1の手札がすべて裏返ったか
	bool player1Win = true;
	for (int i = 0; i < 9; ++i) {
		if (!cardFlipped[0][i]) {
			player1Win = false;
			break;
		}
	}

	//プレイヤー2の手札がすべて裏返ったか
	bool player2Win = true;
	for (int i = 0; i < 9; ++i) {
		if (!cardFlipped[1][i]) {
			player2Win = false;
			break;
		}
	}
	if (player1Win || player2Win) {
		
	}

	if (player1Win || player2Win) {

		Sleep(1000);

		ClearDrawScreen();
		if (player1Win && player2Win) {
			DrawString(100, 100, "Draw!", GetColor(255, 255, 255));
		}
		else if (player1Win) {
			DrawString(100, 100, "Player 2 wins!", GetColor(255, 255, 255));
		}
		else {
			DrawString(100, 100, "Player 1 wins!", GetColor(255, 255, 255));
		}
		ScreenFlip();
		WaitKey();
		
	}
	ScreenFlip();
	return this;
}

void Takoyaki::Draw() const
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
			DrawGraph(70 + i * 120, 450, cardFlipped[1][i] ? Cards_img[cardIndex] : BackCard_Img, TRUE);
		}
		else {
			DrawGraph(70 + i * 120, 450, BackCard_Img, TRUE); // カードが無効な場合、バックカードを描画
		}
	}

	if (drawnCard >= 0 && drawnCard < 56) {
		DrawGraph(640, 250, Cards_img[drawnCard], TRUE);
	}


	

	ScreenFlip();
}


