#pragma once
#include "AbstractScene.h"

enum class Order {
  First,
  Second,
};

class Reversi :
    public AbstractScene

{
private:

    bool K_Flg;
    int R_Img;
    int B_Rock_Img;
    int W_Rock_Img;


    //POINT CursorPoint;	//�J�[�\���̍��W�p
    bool XOnce;	//L�X�e�B�b�N���͏d���h�~�p�i���j
    bool YOnce;	//L�X�e�B�b�N���͏d���h�~�p�i�c�j


public:
    //�R���X�g���N�^
    Reversi();

    //�f�X�g���N�^
    ~Reversi();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

   void disp();
   void board();
};


