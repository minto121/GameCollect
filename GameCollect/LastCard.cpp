#include "LastCard.h"
#include "DxLib.h"
#include "PadInput.h"

LastCard::LastCard()
{
	Card;

	CardImg;

	LoadDivGraph("images/LastCard/LastCard.png", 65, 13, 5, 128, 256, CardImg);

    InitPlayerHands();

    startX;
    startY;
    cardHeight;
    cardWidth;
}

LastCard::~LastCard()
{
}

AbstractScene* LastCard::Update()
{
	if (CheckHitKey(KEY_INPUT_O))
	{
		return nullptr;
	}
	return this;
}

void LastCard::Draw() const
{
	DrawGraph(35, 49, CardImg[2], FALSE);

    for (size_t i = 0; i < playerHands.size(); ++i) {
        int posX = startX + i * 200; // プレイヤーごとのX座標
        int posY = startY;

        // 手札のカードを描画する
        for (size_t j = 0; j < playerHands[i].size(); ++j) {
            int cardID = playerHands[i][j]; // カードのID（例: 赤の2）
            int cardImg = CardImg[cardID]; // カードの画像

            // カードを描画する
            DrawGraph(posX, posY, cardImg, TRUE);
            DrawFormatString(35, 49 + 30 * i, 0xfff, "%d", cardID, TRUE);

            // 次のカードの描画位置を調整する
            posY += cardHeight + 10; // 10はカード間の間隔
        }
    }

}

void LastCard::InitPlayerHands()
{
    // 既存の手札をクリア
    playerHands.clear();

    // カードを配布する前にデッキをシャッフル
    std::vector<int> deck;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 13; ++j) {
            deck.push_back(Card[i][j]);
        }
    }

    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(std::random_device()()));

    // 4人のプレイヤーを想定
    const int numPlayers = 4;

    // 各プレイヤーの手札を初期化
    playerHands.resize(numPlayers);

    // カードをプレイヤーに配布
    for (int i = 0; i < deck.size(); ++i) {
        playerHands[i % numPlayers].push_back(deck[i]);
    }
}

