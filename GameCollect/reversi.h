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
    
    //カーソル
    struct{
        int X = 0;
        int Y = 0;
    }Cur;

    //フラグ
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

    //POINT CursorPoint;	//カーソルの座標用
    bool XOnce;	//Lスティック入力重複防止用（横）
    bool YOnce;	//Lスティック入力重複防止用（縦）

    bool PTurn;

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
   void TurnOver();
   void SelectTurn();
   void FirstTurnScreen();


   int Bac;
   int Bla;
   int Whi;

};


