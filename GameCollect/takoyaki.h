#pragma once
#include "AbstractScene.h"

class Card :
    public AbstractScene

{
private:
    int cards;  //�J�[�h
    


public:
    //�R���X�g���N�^
    Card();

    //�f�X�g���N�^
    ~Card();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};