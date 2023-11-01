#pragma once
#include <vector>
#include <cstdlib>
#include <ctime>
#include "AbstractScene.h"

class Takoyaki :
    public AbstractScene
{

private:
    int Select;     //選択数 
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
class Card {
public:
    int handle; //カードのハンドル
    int value; //カードの数値(1～10)

    Card(int handle, int value) :handle(handle), value(value) {}
};
class Deck {
private:
    std::vector<Card> cards; // 山札

public:
    Deck(std::vector<int>& cardHandles) {
        for (int i = 0; i < 52; ++i) {
            cards.push_back(Card(cardHandles[i], i % 13 + 1));
        }
        // シード値を設定してランダムな結果を得る
        srand(static_cast<unsigned int>(time(NULL)));
    }

    Card DrawRandomCard() {
        int randomIndex = rand() % cards.size(); // ランダムなインデックスを生成
        Card drawnCard = cards[randomIndex];    // ランダムなカードを取得
        cards.erase(cards.begin() + randomIndex); // 山札から取り出したカードを削除
        return drawnCard;
    }
};



