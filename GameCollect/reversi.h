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
    
    //カーソル
    struct{
        int X = 0;
        int Y = 0;
    }Cur;

    //フラグ
    struct {
        bool Xr = 0;
        bool Xl = 0;
        bool Yu = 0;
        bool Yd = 0;
        bool button = 0;
    }Fla;

    int Tur;
    int W_Storn_Img;


    //POINT CursorPoint;	//カーソルの座標用
    bool XOnce;	//Lスティック入力重複防止用（横）
    bool YOnce;	//Lスティック入力重複防止用（縦）



public:
    //コンストラクタ
    Reversi();

    //デストラクタ
    ~Reversi();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;

    void Cursor();

   void turn();
 /*  void Board();*/
   void init_board(int board[SIZ][SIZ]);

   int Bac;
   int Bla;
   int Whi;

};


