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


    POINT CursorPoint;	//カーソルの座標用
    bool XOnce;	//Lスティック入力重複防止用（横）
    bool YOnce;	//Lスティック入力重複防止用（縦）

    struct {
        int typ[8][8];
        int x[8][8];
        int y[8][8];
    }Boa;



public:
    //コンストラクタ
    Reversi();

    //デストラクタ
    ~Reversi();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;

   void disp();
   void board();

   char Board[10][10]{
   { -1 , -1, -1, -1, -1, -1, -1, -1, -1, -1},
   { -1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -1},
   { -1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -1},
   { -1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -1},
   { -1 , 0 , 0 , 0 , 1 , 2 , 0 , 0 , 0 , -1},
   { -1 , 0 , 0 , 0 , 2 , 1 , 0 , 0 , 0 , -1},
   { -1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -1},
   { -1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -1},
   { -1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , -1},
   { -1 , -1, -1, -1, -1, -1, -1, -1, -1, -1}
   };

};


