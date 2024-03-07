#pragma once
#include "AbstractScene.h"
#include <vector>
class Takoyaki :
    public AbstractScene
{
    std::vector<int> drawnCardHistory;
private:
    int Cards_img[56];
    int cardimg;
    int select_X;
    int select_Y;
    int BackCard_Img;
    bool AButtonPressed;

    bool isPlayer1Turn;
    bool cardFlipped[2][10];
   
    int drawnCard;
    int drawnNumber;
   
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

    void DrawnCard();

    void WinnerChecker();

    void Printf();

};





