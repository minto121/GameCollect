#pragma once
#include "AbstractScene.h"
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>


class Takoyaki :
    public AbstractScene
{

private:
    int Select;             //選択数 
    int Cards_img[56];      //カード情報格納配列
    int CursolImg;          //カーソル画像
    int cardimg;            //カード
    int select_X;           //カードごとのカーソル位置を保持
    int select_Y;
    int BackCard_Img;
    std::vector<int> drawCards;
    bool cardFlipped[2][10];//カードの裏返し
    bool AButtonPressed;
    bool isPlayer1Turn;     //自分のターンかどうか
    int DrawCard() {
        srand(static_cast<unsigned int>(time(NULL)));
    }
    std::string GetRandamCardString() {
        int randomIndex = rand() % 56;//0から55の間でランダムに選ぶ
        int cardNumber = Cards_img[randomIndex];

        std::stringstream ss;
        ss << cardNumber;
        std::string cardString = ss.str();

        return cardString;
    }
    //手札の情報を保持する配列
    int handCard[2][10];
public:
    //コンストラクタ
    Takoyaki() {
        isPlayer1Turn = true;
    }

    //デストラクタ
    ~Takoyaki();

    //描画以外の更新を実行
    AbstractScene* Update();

    //描画に関することを実装
    void Draw() const;

    void PerformTurn() {
        int cardDrawn = DrawCard();
        if (cardDrawn > 10) {
            isPlayer1Turn = false;
        }
        else {
            int cardDrawn = DrawCard();
            if (cardDrawn > 10) {
                isPlayer1Turn = true;
            }
        }
    }
    void DrawRandomCardInfo() {
        std::string cardInfo = GetRandamCardString();

        DrawString(100, 100, cardInfo.c_str(), GetColor(255, 255, 255));
    }
};





