#pragma once
#include "AbstractScene.h"

class Takoyaki :
    public AbstractScene
{

private:
    int Select;             //�I�� 
    int Cards_img[56];      //�J�[�h���i�[�z��
    int CursolImg;          //�J�[�\���摜
    int cardimg;            //�J�[�h
    int select_X;           //�J�[�h���Ƃ̃J�[�\���ʒu��ێ�
    int BackCard_Img;
    bool cardFlipped[2][10];       //�J�[�h�̗��Ԃ�
   
    //��D�̏���ێ�����z��
    int handCard[2][10];
public:
    //�R���X�g���N�^
    Takoyaki();

    //�f�X�g���N�^
    ~Takoyaki();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update();

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const;
};





