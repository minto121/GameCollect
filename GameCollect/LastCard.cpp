#include "LastCard.h"
#include "DxLib.h"
#include "PadInput.h"

//#define SCREEN_HEIGHT 720	//画面サイズ (縦)
//#define SCREEN_WIDTH 1280	//画面サイズ (横)

LastCard::LastCard()
{
    input_margin;
    now_Select;

    Card;

    CardImg;

    LoadDivGraph("images/LastCard/LastCard.png", 65, 13, 5, 128, 256, CardImg);

    // デッキに一意なIDを持つカードを追加する
    for (int i = 0; i < 2; ++i) {
        for (int color = 0; color < NUM_COLORS; ++color) {
            for (int value = 0; value < CARDS_PER_COLOR; ++value) {
                int cardID = color * CARDS_PER_COLOR + value; // カードの一意なID
                deck.push_back(cardID);
            }
        }
    }
    for (int i = 0; i < 4; ++i) {
        deck.push_back(52);
    }

    InitPlayerHands();

    field.push_back(deck.back());

    startX;
    startY;
    cardHeight;
    cardWidth;
    cardGap;

    a;
}

LastCard::~LastCard()
{
}

AbstractScene* LastCard::Update()
{

    if (input_margin < max_input_margin) {
        input_margin++;
    }
    else {
        // スティックのX座標を取得
        int stick_x = PAD_INPUT::GetLStick().ThumbX;

        if (std::abs(stick_x) > stick_sensitivity) {
            //playsoundmem
            // スティックが右に移動した場合
            if (stick_x > 0) {
                // メニュー選択肢を一つ右に移動
                now_Select = (now_Select + 1);
                if (now_Select > playerHands[0].size()) {
                    now_Select = now_Select - playerHands[0].size() - 1;
                }
            }
            // スティックが左に移動した場合
            else if (stick_x < 0) {
                // メニュー選択肢を一つ左に移動
                now_Select = (now_Select - 1);
            }
            input_margin = 0;
        }
    }
    if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true)) {
        field.push_back(playerHands[1].back());
        playerHands[0].pop_back();
    }

	if (CheckHitKey(KEY_INPUT_O))
	{
		return nullptr;
	}
	return this;
}

void LastCard::Draw() const
{
	//DrawGraph(35, 49, CardImg[2], FALSE);



    for (size_t i = 0; i < playerHands.size(); ++i) {
        int posX = 0;
        int posY = 0;
        
        // プレイヤーごとのY座標
        if (i == 0) {
            posY = 500;
            posX = 400;
        }
        else {
            if (i == 2) {
                posY = 20;
            }
            else {
                posY = 50;
            }
            posX = (i - 1) * 400;
        }
        //int posX = startX ; // プレイヤーごとのX座標
        //int posY = startY + i * 250;

        for (size_t j = 0; j < playerHands[i].size(); ++j) {
            int cardID = playerHands[i][j]; // カードのID

            // カードが存在する場合のみ描画する
            if (cardID >= 0 && cardID < 65) {
                int column = cardID % 13; // カード画像の列
                int row = cardID / 13; // カード画像の行
                int cardImg = CardImg[row * 13 + column]; // カードの画像

                // カードを描画する
                DrawGraph(posX, posY, cardImg, TRUE);

                if (i == 0 && j == now_Select) {
                    DrawBox(posX, posY, posX + cardWidth, posY + cardHeight, 0xff0000, false);
                }

                // 次のカードの描画位置を調整する
                posX += cardWidth + cardGap;
            }
        }
    }

    DrawGraph(200, 200, CardImg[field.back()], TRUE);

}

void LastCard::InitPlayerHands()
{
    // 既存の手札をクリア
    playerHands.clear();


    // デッキをシャッフルする


    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(std::random_device()()));


    // 4人のプレイヤーを想定
    const int numPlayers = 4;

    // 各プレイヤーの手札を初期化
    playerHands.resize(numPlayers);

    const int cardsPerPlayer = 5; // 各プレイヤーに配るカードの数

    // デッキからプレイヤーにカードを配る
    for (int i = 0; i < numPlayers * cardsPerPlayer; ++i) {
        if (deck.size() > 0) {
            int card = deck.back(); // デッキからカードを取得
            deck.pop_back(); // デッキからカードを削除

            int playerIndex = i % numPlayers; // プレイヤーのインデックス
            playerHands[playerIndex].push_back(card); // プレイヤーにカードを追加
        }
        else {
            // デッキにカードがない場合の処理（例えば、エラー処理など）
            // ここではシンプルにログを出力します
            //std::cout << "デッキにカードが足りません！" << std::endl;
            break;
        }
        // デッキの中身を出力する（デバッグ用）
        for (int i = 0; i < deck.size(); ++i) {
            printf("%d ", deck[i]);
        }
        printf("\n");
    }
}

