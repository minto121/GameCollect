#pragma once
#include "AbstractScene.h"

class Reversi :
    public AbstractScene

{
private:
    int R_Img;
    

public:
    //コンストラクタ
    Reversi();

    //デストラクタ
    ~Reversi();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};


