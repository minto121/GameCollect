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
        int posX = startX + i * 200; // �v���C���[���Ƃ�X���W
        int posY = startY;

        // ��D�̃J�[�h��`�悷��
        for (size_t j = 0; j < playerHands[i].size(); ++j) {
            int cardID = playerHands[i][j]; // �J�[�h��ID�i��: �Ԃ�2�j
            int cardImg = CardImg[cardID]; // �J�[�h�̉摜

            // �J�[�h��`�悷��
            DrawGraph(posX, posY, cardImg, TRUE);
            DrawFormatString(35, 49 + 30 * i, 0xfff, "%d", cardID, TRUE);

            // ���̃J�[�h�̕`��ʒu�𒲐�����
            posY += cardHeight + 10; // 10�̓J�[�h�Ԃ̊Ԋu
        }
    }

}

void LastCard::InitPlayerHands()
{
    // �����̎�D���N���A
    playerHands.clear();

    // �J�[�h��z�z����O�Ƀf�b�L���V���b�t��
    std::vector<int> deck;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 13; ++j) {
            deck.push_back(Card[i][j]);
        }
    }

    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(std::random_device()()));

    // 4�l�̃v���C���[��z��
    const int numPlayers = 4;

    // �e�v���C���[�̎�D��������
    playerHands.resize(numPlayers);

    // �J�[�h���v���C���[�ɔz�z
    for (int i = 0; i < deck.size(); ++i) {
        playerHands[i % numPlayers].push_back(deck[i]);
    }
}

