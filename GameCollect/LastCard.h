#pragma once
#include "AbstractScene.h"

#include <vector>
#include <algorithm>  // for std::shuffle
#include <random>     // for std::default_random_engine


class LastCard : public AbstractScene
{
private:
    int Card[5][13] = {
       //                                            ス  リ
       //                                            キ  バ
       //                                            ッ  ー
       // 1   2   3   4   5   6   7   8   9  +2  +3  プ  ス
        { 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 }, //赤
        { 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 }, //オレンジ
        { 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 }, //紫
        { 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 }, //青
        { 4 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 }  //ワイルド
    };


    int CardImg[65];

    std::vector<std::vector<int>> playerHands;


public:
    //コンストラクタ
    LastCard();

    //デストラクタ
    ~LastCard();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;

    // プレイヤーの手札を初期化する関数
    void InitPlayerHands();
};

