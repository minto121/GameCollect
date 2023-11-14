#pragma once
#include "AbstractScene.h"

#define SIZ 10

enum class Order {
  First,
  Second,
};


class Reversi :
    public AbstractScene

{
private:

    struct {
        int Typ[8][8];
        int X[8][8];
        int Y[8][8];
    }Sto;



    bool K_Flg;
    int R_Img;
    int bor;
    int B_Storn_Img;    
    
    //�J�[�\��
    struct{
        int X = 0;
        int Y = 0;
    }Cur;

    //�t���O
    struct {
        bool Xr = 0;
        bool Xl = 0;
        bool Yu = 0;
        bool Yd = 0;
        bool button = 0;
    }Fla;

    int Tur;
    int W_Storn_Img;


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

    void Cursor();

   void turn();
 /*  void Board();*/
   void init_board(int board[SIZ][SIZ]);

   int Bac;
   int Bla;
   int Whi;

};


