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
        int posX = startX + i * 250; // �v���C���[���Ƃ�X���W
        int posY = startY;

        for (size_t j = 0; j < playerHands[i].size(); ++j) {
            int cardID = playerHands[i][j]; // �J�[�h��ID

            // �J�[�h�����݂���ꍇ�̂ݕ`�悷��
            if (cardID >= 0 && cardID < 65) {
                int column = cardID % 13; // �J�[�h�摜�̗�
                int row = cardID / 13; // �J�[�h�摜�̍s
                int cardImg = CardImg[row * 13 + column]; // �J�[�h�̉摜

                // �J�[�h��`�悷��
                DrawGraph(posX, posY, cardImg, TRUE);

                // ���̃J�[�h�̕`��ʒu�𒲐�����
                posY += cardHeight + cardGap;
            }
        }
    }

}

void LastCard::InitPlayerHands()
{
    // �����̎�D���N���A
    playerHands.clear();

    std::vector<int> deck;
    const int NUM_COLORS = 4;
    const int CARDS_PER_COLOR = 13;

    // �f�b�L�Ɉ�ӂ�ID�����J�[�h��ǉ�����
    for (int color = 0; color < NUM_COLORS; ++color) {
        for (int value = 0; value < CARDS_PER_COLOR; ++value) {
            int cardID = color * CARDS_PER_COLOR + value; // �J�[�h�̈�ӂ�ID
            deck.push_back(cardID);
        }
    }

    // �f�b�L���V���b�t������
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(std::random_device()()));

    // 4�l�̃v���C���[��z��
    const int numPlayers = 4;

    // �e�v���C���[�̎�D��������
    playerHands.resize(numPlayers);

    const int cardsPerPlayer = 5; // �e�v���C���[�ɔz��J�[�h�̐�

    // �J�[�h���v���C���[�ɔz�z
    for (int i = 0; i < numPlayers * cardsPerPlayer; ++i) {
        int playerIndex = i % numPlayers;
        if (playerHands[playerIndex].size() < cardsPerPlayer) {
            playerHands[playerIndex].push_back(deck[i]);
        }
    }
}

