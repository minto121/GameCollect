#pragma once
#include "AbstractScene.h"

class LastCard : public AbstractScene
{
private:
    int Card[5][13] = { 
        {2,2,2,2,2,2,2,2,2,2,2,2,2}, 
        {2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2},
        {4,0,0,0,0,0,0,0,0,0,0,0,0}
    };

    int CardImg[65];


public:
    //�R���X�g���N�^
    LastCard();

    //�f�X�g���N�^
    ~LastCard();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};

