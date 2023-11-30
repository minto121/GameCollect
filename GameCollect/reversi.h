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


    //POINT CursorPoint;	//カーソルの座標用
    bool XOnce;	//Lスティック入力重複防止用（横）
    bool YOnce;	//Lスティック入力重複防止用（縦）

    //struct {
    //    int typ[8][8];
    //    int x[8][8];
    //    int y[8][8];
    //}Boa;



public:
    //コンストラクタ
    Reversi();

    //デストラクタ
    ~Reversi();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
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


