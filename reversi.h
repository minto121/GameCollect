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

    int R_Img;
    int bor;
    int cou;
    int B_Storn_Img;
    int BackImg;
    int PauseFlashTime;

    struct {
        int Typ[8][8];
        int X[8][8];
        int Y[8][8];
    }Sto;
    
    //�J�[�\��
    struct{
        int X = 0;
        int Y = 0;
    }Cur;

    //�t���O
    bool K_Flg;
    bool C_Flg;
    bool PauseFlg;
    bool PauseFlashFlg;

    struct {
        bool Xr = 0;
        bool Xl = 0;
        bool Yu = 0;
        bool Yd = 0;
        bool button = 0;
    }Fla;
    
    struct {
        struct {
            int l;
            int m;
            int r;
        }x;

        struct {
            int u;
            int m;
            int d;
        }y;
    }e;

    int Tur;

    //POINT CursorPoint;	//�J�[�\���̍��W�p
    bool XOnce;	//L�X�e�B�b�N���͏d���h�~�p�i���j
    bool YOnce;	//L�X�e�B�b�N���͏d���h�~�p�i�c�j

    bool PTurn;

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
   void TurnOver();
   void SelectTurn();
   void FirstTurnScreen();


   int Bac;
   int Bla;
   int Whi;

};


