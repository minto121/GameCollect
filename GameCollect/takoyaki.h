#pragma once
#include "AbstractScene.h"

class Card :
    public AbstractScene
{
  
private:
   
    int cardimg1;
    int Cards_img[42];  //�J�[�h
    int CursolImg; //�J�[�\���摜
    int select_X;
    
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