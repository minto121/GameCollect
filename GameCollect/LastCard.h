#pragma once
#include "AbstractScene.h"

class LastCard : public AbstractScene
{
private:
    int Card[2][2]= { {1,1}, {1,1} };


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

