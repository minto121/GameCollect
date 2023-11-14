#pragma once
#include "AbstractScene.h"

class LastCard : public AbstractScene
{
private:
    int Card[5][13] = { 
        {2,2,2,2,2,2,2,2,2,2,2,2,2}, 
        {2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2},
        {4,0,0,0,0,0,0,0,0,0,0,0,0}
    };

    int CardImg[65];


public:
    //コンストラクタ
    LastCard();

    //デストラクタ
    ~LastCard();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};

