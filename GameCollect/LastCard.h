#pragma once
#include "AbstractScene.h"

#include <vector>
#include <algorithm>  // for std::shuffle
#include <random>     // for std::default_random_engine


class LastCard : public AbstractScene
{
private:
    int Card[5][13] = {
       //                                            �X  ��
       //                                            �L  �o
       //                                            �b  �[
       // 1   2   3   4   5   6   7   8   9  +2  +3  �v  �X
        { 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 }, //��
        { 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 }, //�I�����W
        { 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 }, //��
        { 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 }, //��
        { 4 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 }  //���C���h
    };


    int CardImg[65];

    std::vector<std::vector<int>> playerHands;

    const int startX = 50; // �J�nX���W
    const int startY = 50; // �J�nY���W
    const int cardWidth = 50; // �J�[�h�̕�
    const int cardHeight = 80; // �J�[�h�̍���


public:
    //�R���X�g���N�^
    LastCard();

    //�f�X�g���N�^
    ~LastCard();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

    // �v���C���[�̎�D������������֐�
    void InitPlayerHands();
};

