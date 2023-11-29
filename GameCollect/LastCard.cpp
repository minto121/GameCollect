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
    cardGap;
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
        int posX = startX + i * 250; // プレイヤーごとのX座標
        int posY = startY;

        for (size_t j = 0; j < playerHands[i].size(); ++j) {
            int cardID = playerHands[i][j]; // カードのID

            // カードが存在する場合のみ描画する
            if (cardID >= 0 && cardID < 65) {
                int column = cardID % 13; // カード画像の列
                int row = cardID / 13; // カード画像の行
                int cardImg = CardImg[row * 13 + column]; // カードの画像

                // カードを描画する
                DrawGraph(posX, posY, cardImg, TRUE);

                // 次のカードの描画位置を調整する
                posY += cardHeight + cardGap;
            }
        }
    }

}

void LastCard::InitPlayerHands()
{
    // 既存の手札をクリア
    playerHands.clear();

    std::vector<int> deck;
    const int NUM_COLORS = 4;
    const int CARDS_PER_COLOR = 13;

    // デッキに一意なIDを持つカードを追加する
    for (int color = 0; color < NUM_COLORS; ++color) {
        for (int value = 0; value < CARDS_PER_COLOR; ++value) {
            int cardID = color * CARDS_PER_COLOR + value; // カードの一意なID
            deck.push_back(cardID);
        }
    }

    // デッキをシャッフルする
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(std::random_device()()));

    // 4人のプレイヤーを想定
    const int numPlayers = 4;

    // 各プレイヤーの手札を初期化
    playerHands.resize(numPlayers);

    const int cardsPerPlayer = 5; // 各プレイヤーに配るカードの数

    // カードをプレイヤーに配布
    for (int i = 0; i < numPlayers * cardsPerPlayer; ++i) {
        int playerIndex = i % numPlayers;
        if (playerHands[playerIndex].size() < cardsPerPlayer) {
            playerHands[playerIndex].push_back(deck[i]);
        }
    }
}

