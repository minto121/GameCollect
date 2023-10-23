#pragma once
#include "AbstractScene.h"

class Revesi :
    public AbstractScene

{
private:



public:
    //コンストラクタ
    Revesi();

    //デストラクタ
    ~Revesi();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};


