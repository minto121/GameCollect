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
		int drawnCard = GetRand(13); // 0〜9のランダムな値を取得
		if (!cardFlipped[isPlayer1Turn ? 0 : 1][drawnCard]) { // カードがまだ捲られていない場合のみ処理を行う
			cardFlipped[isPlayer1Turn ? 0 : 1][drawnCard] = true; // カードを裏返す
			handCard[isPlayer1Turn ? 0 : 1][drawnCard] = GetRand(13) + 1;

			// 絵札（10～13）が出た場合、相手のターンに切り替える
			if (handCard[isPlayer1Turn ? 0 : 1][drawnCard] >= 11 && handCard[isPlayer1Turn ? 0 : 1][drawnCard] <= 13) {
				isPlayer1Turn = !isPlayer1Turn; // ターンを切り替える
				printf("Player's turn ended\n");
			}

			// キーが押されたら少し待つ
			Sleep(500); // ミリ秒単位で指定（0.5秒）
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
		//勝利メッセージ表示
		//DrawString(SCREEN_WIDTH)
	}

	if (player1Win || player2Win) {
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
		//CheckWinner();
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


void Takoyaki::DrawnCard()
{
	int drawnCard;

	do {
		drawnCard = GetRand(13); // 0〜12のランダムな値を取得
	} while (cardFlipped[0][drawnCard] || cardFlipped[1][drawnCard] ||
		std::find(std::begin(handCard[0]), std::end(handCard[0]), drawnCard) != std::end(handCard[0]) ||
		std::find(std::begin(handCard[1]), std::end(handCard[1]), drawnCard) != std::end(handCard[1]) ||
		std::find(std::begin(drawnCardHistory), std::end(drawnCardHistory), drawnCard) != std::end(drawnCardHistory));

	drawnCardHistory.push_back(drawnCard); // 引いたカードを履歴に追加

	if (!isPlayer1Turn) {
		cardFlipped[0][drawnCard] = true; // カードを裏返す

		// 未めくられている手札の位置を探す
		auto it = std::find(std::begin(cardFlipped[0]), std::end(cardFlipped[0]), false);

		if (it != std::end(cardFlipped[0])) {
			// 未使用のランダムな位置に山札の番号を設定
			*it = true; // カードをめくる
			int index = std::distance(std::begin(cardFlipped[0]), it);
			handCard[0][index] = drawnCard;

			// 絵札（11〜13）が出た場合、プレイヤー2のターンに切り替える
			if (drawnCard >= 10 && drawnCard <= 12) {
				isPlayer1Turn = true; // プレイヤー2のターンに切り替える
				printf("Player 2's turn started\n");
			}
			else {
				// 数字の場合、対応する手札をめくる
				int handIndex = drawnCard - 1; // カードの数字と手札のインデックスは1ずれる
				
				cardFlipped[0][handIndex] = true;
				printf("Player 1 flipped card %d at index %d\n", drawnCard, handIndex);
			}
		}
	}
	else {
		// プレイヤー2のターンの場合、対応する手札をめくる
		int handIndex = drawnCard - 1; // カードの数字と手札のインデックスは1ずれる
		cardFlipped[1][handIndex] = true;
		printf("Player 2 flipped card %d at index %d\n", drawnCard, handIndex);

		// 絵札（11〜13）が出た場合、プレイヤー1のターンに切り替える
		if (drawnCard >= 10 && drawnCard <= 12) {
			isPlayer1Turn = !isPlayer1Turn; // プレイヤー1とプレイヤー2のターンを切り替える
		}
	}

	Draw(); // ターンが切り替わったときに手札を描画
	ScreenFlip();
	Sleep(1000); // 1秒待機
}