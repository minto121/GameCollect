#pragma once
#include "AbstractScene.h"

class Takoyaki :
    public AbstractScene
{
  
private:
    int Select;     //選択数 
    int cardimg1;
    int Cards_img[42];  //カード
    int CursolImg; //カーソル画像
    int select_X;//カードごとのカーソル位置を保持
    
public:
    //コンストラクタ
    Takoyaki();

    //デストラクタ
    ~Takoyaki();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};