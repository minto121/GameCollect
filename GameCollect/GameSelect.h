#pragma once
#include "AbstractScene.h"
class GameSelect :
    public AbstractScene
{
    int Select;
    bool Once;

public:
    //�R���X�g���N�^
    GameSelect();

    //�f�X�g���N�^
    ~GameSelect();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};

