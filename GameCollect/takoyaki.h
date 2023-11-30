#pragma once
#include "AbstractScene.h"

class Takoyaki :
    public AbstractScene
{

private:
    int Select;             //選択数 
    int Cards_img[56];      //カード情報格納配列
    int CursolImg;          //カーソル画像
    int cardimg;            //カード
    int select_X;           //カードごとのカーソル位置を保持
    int BackCard_Img;
    bool cardFlipped[2][10];       //カードの裏返し
    bool AButtonPressed;
   
    //手札の情報を保持する配列
    int handCard[2][10];
public:
    //コンストラクタ
    Takoyaki();

    //デストラクタ
    ~Takoyaki();

    //描画以外の更新を実行
    AbstractScene* Update();

    //描画に関することを実装
    void Draw() const;
};





