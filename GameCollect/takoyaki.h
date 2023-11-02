#pragma once
#include "AbstractScene.h"

class Takoyaki :
    public AbstractScene
{

private:
    int Select;     //�I�� 
    int Cards_img[42];  //�J�[�h
    int CursolImg; //�J�[�\���摜
    int select_X;//�J�[�h���Ƃ̃J�[�\���ʒu��ێ�
    int BackCard_Img;
    bool cardFlipped;//�J�[�h�̗��Ԃ�
    int cardimg;
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





