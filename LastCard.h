#pragma once
#include "AbstractScene.h"

#include <vector>
#include <algorithm>  // for std::shuffle
#include <random>     // for std::default_random_engine


class LastCard : public AbstractScene
{
private:
    int Card[5][13] = {
        // 赤のカード
        { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },  // 赤
        // オレンジのカード
        { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },  // オレンジ
        // 紫のカード
        { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },  // 紫
        // 青のカード
        { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },  // 青
        // ワイルドカード
        { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }   // ワイルド
    };


    int CardImg[65];

    std::vector<std::vector<int>> playerHands;
    std::vector<int> deck;

    const int startX = 50; // 開始X座標
    const int startY = 50; // 開始Y座標
    const int cardWidth = 50; // カードの幅
    const int cardHeight = 80; // カードの高さ
    const int cardGap = 10; // カード間の間隔



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
