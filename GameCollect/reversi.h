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
    int W_Storn_Img;


    //POINT CursorPoint;	//�J�[�\���̍��W�p
    bool XOnce;	//L�X�e�B�b�N���͏d���h�~�p�i���j
    bool YOnce;	//L�X�e�B�b�N���͏d���h�~�p�i�c�j

    //struct {
    //    int typ[8][8];
    //    int x[8][8];
    //    int y[8][8];
    //}Boa;



public:
    //�R���X�g���N�^
    Reversi();

    //�f�X�g���N�^
    ~Reversi();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

   void turn();
 /*  void Board();*/
   void init_board(int board[SIZ][SIZ]);
  /* void print_board(int board[SIZ][SIZ]);*/

   //const char Board[10][10]{
   //{ -1 , -1, -1, -1, -1, -1, -1, -1, -1, -1},
   //{ -1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -1},
   //{ -1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -1},
   //{ -1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -1},
   //{ -1 , 0 , 0 , 0 , 1 , 2 , 0 , 0 , 0 , -1},
   //{ -1 , 0 , 0 , 0 , 2 , 1 , 0 , 0 , 0 , -1},
   //{ -1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -1},
   //{ -1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -1},
   //{ -1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -1},
   //{ -1 , -1, -1, -1, -1, -1, -1, -1, -1, -1}
   //};

   int Bac;
   int Bla;
   int Whi;

};


