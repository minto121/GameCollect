#pragma once
#include "AbstractScene.h"

#include <vector>
#include <algorithm>  // for std::shuffle
#include <random>     // for std::default_random_engine

//#define SCREEN_HEIGHT 720	//画面サイズ (縦)
//#define SCREEN_WIDTH 1280	//画面サイズ (横)

class LastCard : public AbstractScene
{
private:
    // 操作間隔時間
    const int max_input_margin = 15;
    // スティックの感度
    const int stick_sensitivity = 20000;

    int input_margin = 0;  //操作時間間隔
    int now_SelectX = 0; //現在選択してるメニュー
    int now_SelectY = 0; //現在選択してるメニュー

    int BackGroundImg;

    int CardImg[65];

    int WildCardColorImg[4];

    std::vector<std::vector<int>> playerHands;
    std::vector<int> deck;
    std::vector<int> field;

    const int startX = 50; // 開始X座標
    const int startY = 50; // 開始Y座標
    const int cardWidth = 50; // カードの幅
    const int cardHeight = 80; // カードの高さ
    const int cardGap = 10; // カード間の間隔

    const int NUM_COLORS = 4;
    const int CARDS_PER_COLOR = 13;

    int Turn = 1; //ターン制御

    //ターン時間間隔
    int turn_margin = 0;    
    int max_turn_margin = 200;  

    int player_checkdraw = 0;  //1:必要ない　2:必要


    int WildCardFlg = 0;    //ワイルドカードフラグ
    int WildCardColor = -1; //0:赤　1:オレンジ　2:紫　3：水色

    int Draw2Flg = 0;   //ドロー2フラグ
    int Draw3Flg = 0;   //ドロー3フラグ

    int SkipFlg = 0;    //スキップフラグ

    bool ReverseFlg = false; //リバースフラグ false:時計回り true:反時計回り

    int Draw2Count = 0; //ドロー2カウント
    int Draw3Count = 0; //ドロー3カウント

    int LastFlg = 0;    //ラストカード宣言フラグ

    int WinFlg = 0;

    int rank = 1;

    int a;

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

    //出せるカードのチェック
    bool CardCheck(int select_card);

    //敵行動
    void EnemyAction();

    //カードドロー
    void CardDraw(int num);

    //特殊カードのフラグ起動
    void CardFlgCheck(int select_card);

    //ワイルドカードの処理
    void Wildcard();

    //特殊カードのフラグチェック
    bool OnFlgCheck();

    //ドローカード処理
    void Drawcard();

};
