#include "LastCard.h"
#include "DxLib.h"
#include "PadInput.h"

//#define SCREEN_HEIGHT 720	//画面サイズ (縦)
//#define SCREEN_WIDTH 1280	//画面サイズ (横)

LastCard::LastCard()
{
    input_margin;
    now_Select;

    turn_margin;
    max_turn_margin;

   BackGroundImg=LoadGraph("images/LastCard/BackGround01.png");

    //Card;

    CardImg;

    LoadDivGraph("images/LastCard/LastCard.png", 65, 13, 5, 128, 256, CardImg);

    LoadDivGraph("images/LastCard/WildCardColor.png", 4, 4, 1, 128, 256, WildCardColorImg);

    // デッキにカードを追加する
    for (int i = 0; i < 2; ++i) {
        for (int color = 0; color < NUM_COLORS; ++color) {
            for (int value = 0; value < CARDS_PER_COLOR; ++value) {
                int cardID = color * CARDS_PER_COLOR + value; // カードの一意なID
                deck.push_back(cardID);
            }
        }
    }
    for (int i = 0; i < 4; ++i) {
        deck.push_back(52);     //ワイルドカード
    }

    InitPlayerHands();

    field.push_back(deck.back());

    Turn;

    player_checkdraw;

    startX;
    startY;
    cardHeight;
    cardWidth;
    cardGap;


    WildCardFlg;
    WildCardColor;


    a;
}

LastCard::~LastCard()
{
}

AbstractScene* LastCard::Update()
{
    //スティック操作
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
                if (now_Select >= playerHands[0].size()) {
                    now_Select = now_Select - (playerHands[0].size());
                }
            }
            // スティックが左に移動した場合
            else if (stick_x < 0) {
                // メニュー選択肢を一つ左に移動
                now_Select = (now_Select - 1);
                if (now_Select < 0) {
                    now_Select = now_Select + (playerHands[0].size());
                }
            }
            input_margin = 0;
        }
    }

    //ターン制御
    switch (Turn)
    {
    //プレイヤー行動
    case 1: 

        if (WildCardFlg == 1) {
            Wildcard();
        }
        else {

            //ドローが必要か調べる
            if (player_checkdraw == 0) {
                for (int i = 0; i < playerHands[0].size(); i++) {
                    if (CardCheck(playerHands[0][i]) == TRUE) {
                        player_checkdraw = 1;
                    }
                }
                if (player_checkdraw == 0) {
                    player_checkdraw = 2;
                }
            }

            //カードを場に出す
            if (player_checkdraw == 1) {
                if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true)) {
                    if (CardCheck(playerHands[0][now_Select]) == TRUE) {
                        field.push_back(playerHands[0][now_Select]);

                        if (WildCardColor != -1) {
                            WildCardColor = -1;
                        }

                        CardFlgCheck(playerHands[0][now_Select]);

                        playerHands[0].erase(playerHands[0].begin() + now_Select);
                        if (OnFlgCheck()==true) {
                            if (SkipFlg == 1) {
                                if (ReverseFlg == false) {
                                    Turn = Turn + 2;
                                }
                                else {
                                    Turn = Turn - 2;
                                }

                                SkipFlg = 0;
                            }

                            if (Draw2Flg == 1 || Draw3Flg == 1) {
                                Drawcard();
                                if (ReverseFlg == false) {
                                    Turn++;
                                }
                                else {
                                    Turn--;
                                }
                            }

                        }else {
                            if (ReverseFlg == false) {
                                Turn++;
                            }
                            else {
                                Turn--;
                            }
                        }
                    }


                    player_checkdraw = 0;
                }
            }

            //カードをドロー
            if (player_checkdraw == 2) {
                if (Draw2Flg == 1 || Draw3Flg == 1) {
                    int num;
                    num = (Draw2Count * 2) + (Draw3Count * 3);

                    for (int i = 0; i < num; i++) {
                        CardDraw(0);
                    }
                    Draw2Count = 0;
                    Draw3Count = 0;
                    Draw2Flg = 0;
                    Draw3Flg = 0;

                }else{
                    CardDraw(0);
                }

                if (ReverseFlg == false) {
                    Turn++;
                }
                else {
                    Turn--;
                }

                player_checkdraw = 0;
            }
        }
        break;
    //敵行動
    case 2:
    case 3:
    case 4:
        if (turn_margin < max_turn_margin) {
            turn_margin++;
        }
        else {
            EnemyAction();
            if (WildCardFlg == 1) {
                Wildcard();
            }

            if (OnFlgCheck() == true) {
                if (SkipFlg == 1) {
                    if (ReverseFlg == false) {
                        Turn = Turn + 2;
                    }
                    else {
                        Turn = Turn - 2;
                    }

                    SkipFlg = 0;
                }

                if (Draw2Flg == 1 || Draw3Flg == 1) {
                    Drawcard();
                    if (ReverseFlg == false) {
                        Turn++;
                    }
                    else {
                        Turn--;
                    }
                }


            }
            else {
                if (ReverseFlg == false) {
                    Turn++;
                }
                else {
                    Turn--;
                }
            }
            
            turn_margin = 0;
        }
        break;

    default:
        if (ReverseFlg == false) {
            Turn = Turn - 4;
        }
        else {
            Turn = Turn + 4;
        }
        break;
    }




	if (CheckHitKey(KEY_INPUT_O))
	{
		return nullptr;
	}
	return this;
}

void LastCard::Draw() const
{
	//DrawGraph(0, 0, CardImg[2], FALSE);

    DrawGraph(0, 0, BackGroundImg, TRUE);

    //DrawGraph(0, 0, WildCardColorImg[2], TRUE);

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

    if (WildCardColor!=-1) {
        DrawGraph(500, 200, WildCardColorImg[WildCardColor], TRUE);
    }
    else {
        DrawGraph(500, 200, CardImg[field.back()], TRUE);
    }
    
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

bool LastCard::CardCheck(int select_card)
{
    int Select_CardColor = select_card / (CARDS_PER_COLOR);
    int Select_CardNumber = select_card % CARDS_PER_COLOR;

    int Field_CardColor = field.back() / (CARDS_PER_COLOR);
    int Field_CardNumber = field.back() % CARDS_PER_COLOR;
    
    
    if (Draw2Flg == 0 && Draw3Flg == 0) {

        //色の判断
        if (Select_CardColor == Field_CardColor) {
            return TRUE;
        }
        //数字の判断
        if (Select_CardNumber == Field_CardNumber) {
            return TRUE;
        }
        //ワイルドカードの判断
        if (Select_CardColor == 4) {
            //WildCardFlg = 1;
            return TRUE;
        }
        //ワイルドカードで選んだ色の判断
        if (Select_CardColor == WildCardColor) {
            //WildCardColor = -1;
            return TRUE;
        }
    }
    else {
        if (Select_CardNumber == 10 || Draw2Flg == 1) {
            return TRUE;
        }

        if (Select_CardNumber == 9 && Draw3Flg == 0) {
            return TRUE;
        }
    }

    return false;
}

void LastCard::EnemyAction()
{
    int enemycard = -1;
    int i;
    int num;

    for ( i = 0; i < playerHands[Turn-1].size(); i++) {
        if (CardCheck(playerHands[Turn - 1][i]) == TRUE) {
            enemycard = playerHands[Turn - 1][i];
            num = i;
        }
    }

    if (enemycard != -1) {
        field.push_back(enemycard);
        playerHands[Turn - 1].erase(playerHands[Turn - 1].begin() + num);
        if (WildCardColor != -1) {
            WildCardColor = -1;
        }
        CardFlgCheck(enemycard);
    }
    else {
        if (Draw2Flg == 1 || Draw3Flg == 1) {
            int num;
            num = (Draw2Count * 2) + (Draw3Count * 3);

            for (int i = 0; i < num; i++) {
                CardDraw(Turn - 1);
            }
            Draw2Count = 0;
            Draw3Count = 0;
            Draw2Flg = 0;
            Draw3Flg = 0;
        }
        else {
            CardDraw(Turn - 1);
        }
        
    }
}

void LastCard::CardDraw(int num)
{
    int card = deck.back(); // デッキからカードを取得
    deck.pop_back(); // デッキからカードを削除
    
    playerHands[num].push_back(card);//手札にカードを追加
}

void LastCard::CardFlgCheck(int select_card)
{
    int Select_CardColor = select_card / (CARDS_PER_COLOR);
    int Select_CardNumber = select_card % CARDS_PER_COLOR;

    int Field_CardColor = field.back() / (CARDS_PER_COLOR);
    int Field_CardNumber = field.back() % CARDS_PER_COLOR;

    //ワイルドカードの判断
    if (Select_CardColor == 4) {
        WildCardFlg = 1;
    }
    
    //スキップカードの判断
    if (Select_CardNumber == 11) {
        SkipFlg = 1;
    }
    
    //リバースカードの判断
    if (Select_CardNumber == 12) {
        ReverseFlg = !ReverseFlg;
    }

    //ドロー2カードの判断
    if (Select_CardNumber == 9) {
        Draw2Flg = 1;
    }

    //ドロー3カードの判断
    if (Select_CardNumber == 10) {
        Draw3Flg = 1;
    }

}

void LastCard::Wildcard()
{
    if (Turn == 1) {
        //赤
        if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_Y) && (PAD_INPUT::OnButton(XINPUT_BUTTON_Y) == true)) {
            WildCardColor = 0;
            WildCardFlg = 0;
            Turn++;
        }
        //オレンジ
        if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_B) && (PAD_INPUT::OnButton(XINPUT_BUTTON_B) == true)) {
            WildCardColor = 1;
            WildCardFlg = 0;
            Turn++;
        }
        //紫
        if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true)) {
            WildCardColor = 2;
            WildCardFlg = 0;
            Turn++;
        }
        //水色
        if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_X) && (PAD_INPUT::OnButton(XINPUT_BUTTON_X) == true)) {
            WildCardColor = 3;
            WildCardFlg = 0;
            Turn++;
        }
    }
    else {
        WildCardColor = rand()%4;
        WildCardFlg = 0;
    }

}

bool LastCard::OnFlgCheck()
{
    if (WildCardFlg == 1) {
        return true;
    }

    if (SkipFlg == 1) {
        return true;
    }

    if (Draw2Flg == 1) {
        return true;
    }

    if (Draw3Flg == 1) {
        return true;
    }


    return false;
}

void LastCard::Drawcard()
{
    if (Draw3Flg == 1) {
        Draw3Count++;
    }else if (Draw2Flg == 1) {
        Draw2Count++;
    }
}

