#include "LastCard.h"
#include "DxLib.h"
#include "PadInput.h"

//#define SCREEN_HEIGHT 720	//��ʃT�C�Y (�c)
//#define SCREEN_WIDTH 1280	//��ʃT�C�Y (��)

LastCard::LastCard()
{
    input_margin;
    now_Select;

    turn_margin;
    max_turn_margin;

    //Card;

    CardImg;

    LoadDivGraph("images/LastCard/LastCard.png", 65, 13, 5, 128, 256, CardImg);

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

    //�^�[������
    switch (Turn)
    {
    case 1: 
        if (input_margin < max_input_margin) {
            input_margin++;
        }
        else {
            // �X�e�B�b�N��X���W���擾
            int stick_x = PAD_INPUT::GetLStick().ThumbX;

            if (std::abs(stick_x) > stick_sensitivity) {
                //playsoundmem
                // �X�e�B�b�N���E�Ɉړ������ꍇ
                if (stick_x > 0) {
                    // ���j���[�I��������E�Ɉړ�
                    now_Select = (now_Select + 1);
                    if (now_Select >= playerHands[0].size()) {
                        now_Select = now_Select - (playerHands[0].size());
                    }
                }
                // �X�e�B�b�N�����Ɉړ������ꍇ
                else if (stick_x < 0) {
                    // ���j���[�I����������Ɉړ�
                    now_Select = (now_Select - 1);
                    if (now_Select < 0) {
                        now_Select = now_Select + (playerHands[0].size());
                    }
                }
                input_margin = 0;
            }
        }
        if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true)) {

            if (CardCheck(playerHands[0][now_Select]) == TRUE) {
                field.push_back(playerHands[0][now_Select]);

                playerHands[0].erase(playerHands[0].begin() + now_Select);
            }

            /* field.push_back(playerHands[0][now_Select]);

             playerHands[0].erase(playerHands[0].begin() + now_Select);*/

            Turn++;
        }
        break;
    case 2:
    case 3:
    case 4:
        if (turn_margin < max_turn_margin) {
            turn_margin++;
        }
        else {
            EnemyAction();
            Turn++;
            turn_margin = 0;
        }
        break;
    default:
        Turn = 1;
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
	//DrawGraph(35, 49, CardImg[2], FALSE);



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
                DrawGraph(posX, posY, cardImg, TRUE);

                if (i == 0 && j == now_Select) {
                    DrawBox(posX, posY, posX + cardWidth, posY + cardHeight, 0xff0000, false);
                }

                // ���̃J�[�h�̕`��ʒu�𒲐�����
                posX += cardWidth + cardGap;
            }
        }
    }

    DrawGraph(500, 200, CardImg[field.back()], TRUE);

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
        return TRUE;
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
    }
}

