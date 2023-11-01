#pragma once
#include <vector>
#include <cstdlib>
#include <ctime>
#include "AbstractScene.h"

class Takoyaki :
    public AbstractScene
{

private:
    int Select;     //�I�� 
    int Cards_img[42];  //�J�[�h
    int CursolImg; //�J�[�\���摜
    int select_X;//�J�[�h���Ƃ̃J�[�\���ʒu��ێ�

public:
    //�R���X�g���N�^
    Takoyaki();

    //�f�X�g���N�^
    ~Takoyaki();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};
class Card {
public:
    int handle; //�J�[�h�̃n���h��
    int value; //�J�[�h�̐��l(1�`10)

    Card(int handle, int value) :handle(handle), value(value) {}
};
class Deck {
private:
    std::vector<Card> cards; // �R�D

public:
    Deck(std::vector<int>& cardHandles) {
        for (int i = 0; i < 52; ++i) {
            cards.push_back(Card(cardHandles[i], i % 13 + 1));
        }
        // �V�[�h�l��ݒ肵�ă����_���Ȍ��ʂ𓾂�
        srand(static_cast<unsigned int>(time(NULL)));
    }

    Card DrawRandomCard() {
        int randomIndex = rand() % cards.size(); // �����_���ȃC���f�b�N�X�𐶐�
        Card drawnCard = cards[randomIndex];    // �����_���ȃJ�[�h���擾
        cards.erase(cards.begin() + randomIndex); // �R�D������o�����J�[�h���폜
        return drawnCard;
    }
};



