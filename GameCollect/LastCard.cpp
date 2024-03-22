#include "LastCard.h"
#include "DxLib.h"
#include "PadInput.h"

//#define SCREEN_HEIGHT 720	//��ʃT�C�Y (�c)
//#define SCREEN_WIDTH 1280	//��ʃT�C�Y (��)

LastCard::LastCard()
{
    input_margin;
    now_SelectX;
    now_SelectY;

    turn_margin;
    max_turn_margin;

   BackGroundImg=LoadGraph("images/LastCard/BackGround01.png");

    //Card;

    CardImg;

    LoadDivGraph("images/LastCard/LastCard.png", 65, 13, 5, 128, 256, CardImg);

    LoadDivGraph("images/LastCard/WildCardColor.png", 4, 4, 1, 128, 256, WildCardColorImg);

    // �f�b�L�ɃJ�[�h��ǉ�����
    for (int i = 0; i < 2; ++i) {
        for (int color = 0; color < NUM_COLORS; ++color) {
            for (int value = 0; value < CARDS_PER_COLOR; ++value) {
                int cardID = color * CARDS_PER_COLOR + value; // �J�[�h�̈�ӂ�ID
                deck.push_back(cardID);
            }
        }
    }
    for (int i = 0; i < 4; ++i) {
        deck.push_back(52);     //���C���h�J�[�h
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
    //�X�e�B�b�N����
    if (input_margin < max_input_margin) {
        input_margin++;
    }
    else {
        // �X�e�B�b�N��X���W���擾
        int stick_x = PAD_INPUT::GetLStick().ThumbX;
        int stick_y = PAD_INPUT::GetLStick().ThumbY;

        if (std::abs(stick_x) > stick_sensitivity && now_SelectY == 0) {
            //playsoundmem
            // �X�e�B�b�N���E�Ɉړ������ꍇ
            if (stick_x > 0) {
                // ���j���[�I��������E�Ɉړ�
                now_SelectX = (now_SelectX + 1);
                if (now_SelectX >= playerHands[0].size()) {
                    now_SelectX = now_SelectX - (playerHands[0].size());
                }
            }
            // �X�e�B�b�N�����Ɉړ������ꍇ
            else if (stick_x < 0) {
                // ���j���[�I����������Ɉړ�
                now_SelectX = (now_SelectX - 1);
                if (now_SelectX < 0) {
                    now_SelectX = now_SelectX + (playerHands[0].size());
                }
            }
            input_margin = 0;
        }

        if (playerHands[0].size() == 2) {
            if (std::abs(stick_y) > stick_sensitivity) {
                //playsoundmem
                // �X�e�B�b�N���E�Ɉړ������ꍇ
                if (stick_y > 0) {
                    // ���j���[�I��������E�Ɉړ�
                    now_SelectY = (now_SelectY + 1);
                    if (now_SelectY > 1) {
                        now_SelectY = 0;
                    }
                }
                // �X�e�B�b�N�����Ɉړ������ꍇ
                else if (stick_y < 0) {
                    // ���j���[�I����������Ɉړ�
                    now_SelectY = (now_SelectY - 1);
                    if (now_SelectY < 0) {
                        now_SelectY = 1;
                    }
                }
                input_margin = 0;
            }
        }
    }
    //�^�[������
    switch (Turn)
    {
    //�v���C���[�s��
    case 1: 

        if (WildCardFlg == 1) {
            Wildcard();
        }
        else {

            //�h���[���K�v�����ׂ�
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

            //�J�[�h����ɏo��
            if (player_checkdraw == 1) {

                if (now_SelectY == 1 && LastFlg == 0) {
                    if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true)) {
                        LastFlg = 1;
                        now_SelectY = 0;
                    }
                }
                else if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true) && now_SelectY == 0) {
                    if (CardCheck(playerHands[0][now_SelectX]) == TRUE) {
                        field.push_back(playerHands[0][now_SelectX]);

                        if (WildCardColor != -1) {
                            WildCardColor = -1;
                        }

                        CardFlgCheck(playerHands[0][now_SelectX]);

                        playerHands[0].erase(playerHands[0].begin() + now_SelectX);

                        if (playerHands[0].size()<=0) {
                            WinFlg = 1;
                            for (int i = 1; i < 4; ++i) {
                                if (playerHands[i].size() <= 0) {
                                    rank++;
                                }
                            }
                        }

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

                    //���X�g�J�[�h�錾���Ă��Ȃ��ꍇ�h���[
                    if (playerHands[0].size() == 1 && LastFlg == 0) {
                        for (int i = 0; i < 3; i++) {
                            CardDraw(0);
                        }
                    }
                    else if (LastFlg == 1) {
                        LastFlg = 0;
                    }

                    player_checkdraw = 0;
                }
            }

            //�J�[�h���h���[
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
    //�G�s��
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

    if (deck.size() <= 0) {
        deck = field;
        // �f�b�L���V���b�t������
        std::shuffle(deck.begin(), deck.end(), std::default_random_engine(std::random_device()()));
    }

    


    if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true) && WinFlg == 1)
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
        
        // �v���C���[���Ƃ�Y���W
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
        //int posX = startX ; // �v���C���[���Ƃ�X���W
        //int posY = startY + i * 250;

        for (size_t j = 0; j < playerHands[i].size(); ++j) {
            int cardID = playerHands[i][j]; // �J�[�h��ID

            // �J�[�h�����݂���ꍇ�̂ݕ`�悷��
            if (cardID >= 0 && cardID < 65) {
                int column = cardID % 13; // �J�[�h�摜�̗�
                int row = cardID / 13; // �J�[�h�摜�̍s
                int cardImg = CardImg[row * 13 + column]; // �J�[�h�̉摜

                // �J�[�h��`�悷��
                //DrawGraph(posX, posY, cardImg, TRUE);

                if (i == 0 && j == now_SelectX) {
                    //DrawBox(posX, posY, posX + cardWidth, posY + cardHeight, 0xff0000, false);
                    DrawGraph(posX, posY-40, cardImg, TRUE);
                }
                else {
                    // �J�[�h��`�悷��
                    DrawGraph(posX, posY, cardImg, TRUE);
                }

                // ���̃J�[�h�̕`��ʒu�𒲐�����
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
    
    SetFontSize(30);
    if (playerHands[0].size() == 2 && LastFlg == 0 && Turn == 0) {
        DrawFormatString(500, 500, GetColor(0, 0, 255), "LASTCARD");
    }
    
    if (now_SelectY == 1) {
        DrawBox(500, 500, 630, 530, 0xff0000, false);
    }
    
    if (WinFlg == 1) {
        DrawGraph(0, 0, BackGroundImg, TRUE);
        DrawFormatString(500, 300, GetColor(0, 0, 255), "���Ȃ��̏��ʂ�%d�ł��B",rank);
        DrawFormatString(500, 500, GetColor(0, 0, 255), "Please press the A button");
    }

}

void LastCard::InitPlayerHands()
{
    // �����̎�D���N���A
    playerHands.clear();


    // �f�b�L���V���b�t������
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(std::random_device()()));


    // 4�l�̃v���C���[��z��
    const int numPlayers = 4;

    // �e�v���C���[�̎�D��������
    playerHands.resize(numPlayers);

    const int cardsPerPlayer = 5; // �e�v���C���[�ɔz��J�[�h�̐�

    // �f�b�L����v���C���[�ɃJ�[�h��z��
    for (int i = 0; i < numPlayers * cardsPerPlayer; ++i) {
        if (deck.size() > 0) {
            int card = deck.back(); // �f�b�L����J�[�h���擾
            deck.pop_back(); // �f�b�L����J�[�h���폜

            int playerIndex = i % numPlayers; // �v���C���[�̃C���f�b�N�X
            playerHands[playerIndex].push_back(card); // �v���C���[�ɃJ�[�h��ǉ�
        }
        else {
            // �f�b�L�ɃJ�[�h���Ȃ��ꍇ�̏����i�Ⴆ�΁A�G���[�����Ȃǁj
            // �����ł̓V���v���Ƀ��O���o�͂��܂�
            //std::cout << "�f�b�L�ɃJ�[�h������܂���I" << std::endl;
            break;
        }
        // �f�b�L�̒��g���o�͂���i�f�o�b�O�p�j
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

        //�F�̔��f
        if (Select_CardColor == Field_CardColor) {
            return TRUE;
        }
        //�����̔��f
        if (Select_CardNumber == Field_CardNumber) {
            return TRUE;
        }
        //���C���h�J�[�h�̔��f
        if (Select_CardColor == 4) {
            //WildCardFlg = 1;
            return TRUE;
        }
        //���C���h�J�[�h�őI�񂾐F�̔��f
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
    int card = deck.back(); // �f�b�L����J�[�h���擾
    deck.pop_back(); // �f�b�L����J�[�h���폜
    
    playerHands[num].push_back(card);//��D�ɃJ�[�h��ǉ�
}

void LastCard::CardFlgCheck(int select_card)
{
    int Select_CardColor = select_card / (CARDS_PER_COLOR);
    int Select_CardNumber = select_card % CARDS_PER_COLOR;

    int Field_CardColor = field.back() / (CARDS_PER_COLOR);
    int Field_CardNumber = field.back() % CARDS_PER_COLOR;

    //���C���h�J�[�h�̔��f
    if (Select_CardColor == 4) {
        WildCardFlg = 1;
    }
    
    //�X�L�b�v�J�[�h�̔��f
    if (Select_CardNumber == 11) {
        SkipFlg = 1;
    }
    
    //���o�[�X�J�[�h�̔��f
    if (Select_CardNumber == 12) {
        ReverseFlg = !ReverseFlg;
    }

    //�h���[2�J�[�h�̔��f
    if (Select_CardNumber == 9) {
        Draw2Flg = 1;
    }

    //�h���[3�J�[�h�̔��f
    if (Select_CardNumber == 10) {
        Draw3Flg = 1;
    }

}

void LastCard::Wildcard()
{
    if (Turn == 1) {
        //��
        if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_Y) && (PAD_INPUT::OnButton(XINPUT_BUTTON_Y) == true)) {
            WildCardColor = 0;
            WildCardFlg = 0;
            Turn++;
        }
        //�I�����W
        if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_B) && (PAD_INPUT::OnButton(XINPUT_BUTTON_B) == true)) {
            WildCardColor = 1;
            WildCardFlg = 0;
            Turn++;
        }
        //��
        if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true)) {
            WildCardColor = 2;
            WildCardFlg = 0;
            Turn++;
        }
        //���F
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

