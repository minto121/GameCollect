#pragma once
#include "AbstractScene.h"

class LastCard : public AbstractScene
{
private:
    int Card[2][2]= { {1,1}, {1,1} };


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

