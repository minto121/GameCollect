#pragma once
#include "AbstractScene.h"

class Card :
    public AbstractScene

{
private:
    int cards;  //カード
    


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