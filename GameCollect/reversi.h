#pragma once
#include "AbstractScene.h"

class Revesi :
    public AbstractScene

{
private:



public:
    //�R���X�g���N�^
    Revesi();

    //�f�X�g���N�^
    ~Revesi();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};


