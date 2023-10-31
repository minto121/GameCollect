#pragma once
#include "AbstractScene.h"

class Card :
    public AbstractScene
{
  
private:
   
    int cardimg1;
    int Cards_img[42];  //カード
    int CursolImg; //カーソル画像
    int select_X;
    
public:
    //コンストラクタ
    Card();

    //デストラクタ
    ~Card();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};